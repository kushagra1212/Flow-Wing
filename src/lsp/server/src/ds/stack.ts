import { CompletionItem } from "vscode-languageserver";

export class Stack<T> {
  private stack: T[];

  constructor() {
    this.stack = [];
  }

  push(element: T): void {
    this.stack.push(element);
  }

  pop(): T | undefined {
    if (this.isEmpty()) {
      throw new Error("Stack is empty");
    }
    return this.stack.pop();
  }

  isEmpty(): boolean {
    return this.stack.length === 0;
  }

  peek(): T | undefined {
    if (this.isEmpty()) {
      throw new Error("Stack is empty");
    }
    return this.stack[this.stack.length - 1];
  }
}

type VariableName = string;
type TypeName = string;
type ClassName = string;
type FunctionName = string;

export type ClassCompletionItem = {
  variableDeclarations: Map<VariableName, CompletionItem>;
  customTypes: Map<TypeName, CompletionItem>;
  functions: Map<FunctionName, CompletionItem>;
  callExpression: Map<FunctionName, CompletionItem>;
  variableExpressions: Map<VariableName, Array<CompletionItem>>;
  classCompletionItem: CompletionItem;
};
export type ModuleCompletionItem = {
  variableDeclarations: Map<VariableName, CompletionItem>;
  customTypes: Map<TypeName, CompletionItem>;
  functions: Map<FunctionName, CompletionItem>;
  classes: Map<ClassName, ClassCompletionItem>;
  moduleCompletionItem: CompletionItem;
  variableExpressions: Map<VariableName, Array<CompletionItem>>;
};
export interface ProgramStructure {
  variableDeclarations: Map<VariableName, CompletionItem>;
  customTypes: Map<TypeName, CompletionItem>;
  classes: Map<ClassName, ClassCompletionItem>;
  modules: Map<ClassName, ModuleCompletionItem>;
  functions: Map<FunctionName, CompletionItem>;
  callExpression: Map<FunctionName, CompletionItem>;
  variableExpressions: Map<VariableName, Array<CompletionItem>>;
  others: Map<string, CompletionItem>;
}

export const defaultProgramStructure: ProgramStructure = {
  variableDeclarations: new Map(),
  customTypes: new Map(),
  classes: new Map(),
  modules: new Map(),
  functions: new Map(),
  callExpression: new Map(),
  variableExpressions: new Map(),
  others: new Map(),
};
