# Flow-Wing LSP Architecture Analysis

## Current Flow (What We Do Today)

```
User types at position
    ↓
1. getTokensForContext(document, pos)  ← Compiler --emit=tokens (with repair)
    ↓
2. checkForObjectSuggestions(tokens)   ← TOKEN PARSING HEURISTICS
    → Returns: word="a", isDot=true/false, isValueCompletion
    ↓
3. getSemPathForDocument(document, { partialId: word })
    → Tries: repaired content, makeCodeCompleteForLsp(content)
    → Compiler --emit=sem (needs valid code!)
    ↓
4. getCompletionItems(treePath, suggestion)
    → If SEM: getCompletionItemsFromSem(parsed, word, isDot)
    → If AST: traverseJson() - complex AST walk
```

## Fundamental Problems

### 1. Token Heuristics Instead of Tree-Based Context

We use `checkForObjectSuggestions(tokens)` to guess context by parsing tokens backwards:
- "Last token is `:` and before is identifier" → `{a: }` value completion
- "Last token is `.` and before is identifier" → `b.` member completion

**Problem**: Tokens don't tell us the *semantic* context. We don't know:
- What type does the object literal expect? (from `var c: A = {`)
- What is the expected type for field `a`? (int, from type A)
- Are we inside a nested object?

**What we should do**: Find the node at cursor position in `sem.tree`, then derive context from the tree structure.

### 2. SEM Requires Compilable Code

For incomplete code like `var c: A = {a:`:
- Compiler fails → no SEM
- We "repair" with `makeCodeCompleteForLsp` → `{a: 0}` 
- Repair is ad-hoc (colon → add 0, comma → add 0 or }, etc.)

**Problem**: Repair is fragile. The compiler may support error recovery or partial parsing that we're not using. Does the compiler emit AST for incomplete code? If so, we could use that.

### 3. We Don't Use `sem.tree` for Completion Context

The SEM has:
- `sem.tree` – full syntax tree with ranges
- `sem.symbols` – symbol table
- `sem.types` – type information

**Current**: We use `symbols` and `types` with a `word` from token heuristics. We never find "the node at cursor" and ask "what completions make sense here?"

**Should do**: 
```
findNodeAtPosition(sem.tree, pos)
  → Node is MemberExpression? Resolve object type, suggest members
  → Node is ObjectLiteralExpression, after colon? Get expected type from variable declaration, suggest values of that type
  → Node is IdentifierExpression? Suggest symbols in scope
```

### 4. AST Fallback Is Complex and Fragile

When SEM fails, we fall back to AST. The AST traversal (`traverseJson`, `ProgramContext`, `CompletionItemGenerationFactory`) is a large, intricate system that:
- Walks the tree looking for `IdentifierToken` at position
- Uses `ScopeCompletionItemsStrategy`, `AllCompletionItemsStrategy`
- May not handle object literals, member access, or nested contexts well

**Problem**: Two competing completion systems (SEM-based vs AST-based) with different logic. When SEM fails, we get inconsistent behavior.

### 5. `tryRepairContentForSem` Is Wrong for Object Context

For `{a: }`, we pass `partialId="a"`. `tryRepairContentForSem` replaces partial identifiers with defined symbols (e.g. `funNa` → `funName`). 

**Problem**: Here `a` is a *field name*, not a partial identifier. We shouldn't be "repairing" it. The repair logic is designed for identifier completion, not object literal value completion.

## What a Professional LSP Would Do

### Ideal Flow

```
1. Parse document (compiler with error recovery if available)
   → Get sem / ast / tokens

2. Find node at cursor in the tree
   → sem.tree or ast.tree, using range information

3. Derive completion context from node
   → Node type + parent chain → expected type, scope, etc.

4. Query completion source
   → SEM: use types, symbols, resolve expected type
   → Filter by expected type for type-aware completion
```

### Verified: Compiler Behavior

| Input | AST | SEM |
|-------|-----|-----|
| `var c: A = {a:` (incomplete) | ✅ Emitted (has ErrorExpressionSyntax for missing value) | ❌ Not emitted (parse error) |
| `var c: A = {a: 0}` (complete) | ✅ | ✅ |

**The AST contains the structure we need** – ObjectExpressionSyntax, ObjectMemberSyntax, ColonExpressionSyntax, etc. We should use the AST to find "we're completing the value of field `a`" and derive the expected type from the variable's type (A) and its field (a: int).

## Recommended Direction

1. **Inspect compiler output** for incomplete code:
   - Run `FlowWing --emit=ast` and `--emit=sem` on `var c: A = {a:` (with and without repair)
   - See what we actually get

2. **Use tree position as the source of truth**:
   - Implement `getCompletionContextFromTree(sem, pos)` that finds the node and returns `{ expectedType?, isMemberAccess?, scope? }`
   - Replace token heuristics with this

3. **Simplify the pipeline**:
   - One path: get tree (sem or ast) → find node → get context → get completions
   - Remove the token-first approach for completion

4. **Type-aware completion**:
   - For `{a: ` where `a: int`, suggest `x` (int), `0`, `1`, etc.
   - For `c.b.`, suggest members of type of `c.b`
   - Use `sem.types` and the expected type from context
