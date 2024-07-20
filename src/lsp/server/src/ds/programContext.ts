import { declareGlobals } from "../completionItemProvider";
import { RootObject } from "../types";
import { keywordsCompletionItems } from "../store";
import { inBuiltFunctionsCompletionItems } from "../store/completionItems/functions/inbuilt";
import { ProgramStructure, Stack } from "./stack";

export class ProgramContext {
  stack: Stack<ProgramStructure>;
  private _currentParsingClassName: string | null;
  private _isInsideFunction: boolean;
  rootProgram: ProgramStructure;
  private _syntaxTree: RootObject;

  constructor(syntaxTree: RootObject) {
    this._syntaxTree = syntaxTree;
    this.stack = new Stack<ProgramStructure>();
    this.pushEmptyProgramStructure();

    this.rootProgram = this.stack.peek();
    this._currentParsingClassName = null;
    this._isInsideFunction = false;

    this.populateBuiltInFunctions();
    this.populateBuiltInKeywords();

    declareGlobals(this.rootProgram, this._syntaxTree, {
      skip: ["ClassStatement"],
    });
  }

  public pushEmptyProgramStructure(): void {
    this.stack.push({
      variableDeclarations: new Map(),
      customTypes: new Map(),
      classes: new Map(),
      functions: new Map(),
      callExpression: new Map(),
      variableExpressions: new Map(),
      others: new Map(),
    });
  }

  set currentParsingClassName(className: string) {
    this._currentParsingClassName = className;
  }

  get currentParsingClassName(): string | null {
    return this._currentParsingClassName;
  }

  get syntaxTree(): RootObject {
    return this._syntaxTree;
  }

  public removeCurrentClass(): void {
    this.currentParsingClassName = null;
  }

  set isInsideFunction(value: boolean) {
    this._isInsideFunction = value;
  }

  get isInsideFunction(): boolean {
    return this._isInsideFunction;
  }

  public isInsideClass(): boolean {
    return this.currentParsingClassName !== null;
  }

  public isInsideAClassButNotInsideCassMemberFunction(): boolean {
    return this.isInsideClass() && !this.isInsideFunction;
  }

  private populateBuiltInFunctions = (): void => {
    for (const buildInFunc of inBuiltFunctionsCompletionItems) {
      this.rootProgram.functions.set(buildInFunc.label, buildInFunc);
    }
  };
  private populateBuiltInKeywords = (): void => {
    for (const keyword of keywordsCompletionItems) {
      this.rootProgram.others.set(keyword.label, keyword);
    }
  };
}
