interface Token {
  columnNumber: number;
  lineNumber: number;
  value: string;
}

// Primitive types
type Int32Keyword = Token;
type DeciKeyword = Token;
type Deci32Keyword = Token;
type StrKeyword = Token;
type BoolKeyword = Token;
type NthgKeyword = Token;

// Identifiers
type IdentifierToken = Token;
type NumberToken = Token;
type EndOfFileToken = Token;

// Keywords
type VarKeyword = Token;
type ConstKeyword = Token;
type FunctionKeyword = Token;
type DeclKeyword = Token;
type Askeyword = Token;
type ClassKeyword = Token;

// Expression
interface LiteralExpression {
  NumberToken?: NumberToken;
  IdentifierToken?: IdentifierToken;
}

type PrimitiveTypeExpression =
  | { Int32Keyword: Int32Keyword }
  | { DeciKeyword: DeciKeyword }
  | { Deci32Keyword: Deci32Keyword }
  | { StrKeyword: StrKeyword }
  | { BoolKeyword: BoolKeyword }
  | { NthgKeyword: NthgKeyword };

type ArrayTypeExpression = [
  PrimitiveTypeExpression | { ObjectTypeExpression: ObjectTypeExpression[] },
  ...{ LiteralExpression?: LiteralExpression[] }[]
];

type ObjectTypeExpression = [{ LiteralExpression?: LiteralExpression[] }];

type ClassStatement = [
  { ClassKeyword: ClassKeyword },
  { IdentifierToken: IdentifierToken },
  any
];

type TypeExpression =
  | { PrimitiveTypeExpression: PrimitiveTypeExpression[] }
  | { ArrayTypeExpression: ArrayTypeExpression[] }
  | { ObjectTypeExpression: ObjectTypeExpression[] };

type VariableDeclaration = any;

type FunctionDeclaration = [
  {
    FunctionKeyword: FunctionKeyword;
  },
  { IdentifierToken: IdentifierToken },
  ...{ VariableDeclaration: VariableDeclaration[] }[],
  any
];

type CallExpression = [
  { IdentifierToken: IdentifierToken },
  ...{ VariableDeclaration: VariableDeclaration[] }[]
];

interface GlobalStatement {
  VariableDeclaration?: VariableDeclaration[];
  FunctionDeclarationSyntax?: FunctionDeclaration[];
}

interface CompilationUnit {
  GlobalStatement?: GlobalStatement[];
  EndOfFileToken?: EndOfFileToken;
}

interface RootObject {
  CompilationUnit: CompilationUnit[];
}

type BracketedExpression = [
  { LiteralExpression?: LiteralExpression[] },
  TypeExpression
];

type CustomTypeStatement = [
  { LiteralExpression?: LiteralExpression[] },
  ...{ BracketedExpression: BracketedExpression[] }[]
];

export {
  RootObject,
  CompilationUnit,
  GlobalStatement,
  VariableDeclaration,
  TypeExpression,
  PrimitiveTypeExpression,
  ArrayTypeExpression,
  ObjectTypeExpression,
  ClassStatement,
  IdentifierToken,
  NumberToken,
  EndOfFileToken,
  VarKeyword,
  ConstKeyword,
  LiteralExpression,
  BracketedExpression,
  CallExpression,
  CustomTypeStatement,
  FunctionDeclaration,
  Int32Keyword,
  DeciKeyword,
  Deci32Keyword,
  StrKeyword,
  BoolKeyword,
  DeclKeyword,
  Askeyword,
  Token,
};
