interface Value {
  columnNumber: number;
  lineNumber: number;
  value: string;
}

// Primitive types
type Int32Keyword = Value;
type DeciKeyword = Value;
type Deci32Keyword = Value;
type StrKeyword = Value;
type BoolKeyword = Value;
type NthgKeyword = Value;

// Identifiers
type IdentifierToken = Value;
type NumberToken = Value;
type EndOfFileToken = Value;

// Keywords
type VarKeyword = Value;
type ConstKeyword = Value;
type FunctionKeyword = Value;
type DeclKeyword = Value;
type Askeyword = Value;
type ClassKeyword = Value;

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
  CustomTypeStatement,
  FunctionDeclaration,
  Int32Keyword,
  DeciKeyword,
  Deci32Keyword,
  StrKeyword,
  BoolKeyword,
  DeclKeyword,
  Askeyword,
  Value,
};
