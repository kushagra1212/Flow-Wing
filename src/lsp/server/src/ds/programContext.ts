import { declareGlobals } from "../completionItemProvider";
import { RootObject } from "../types";
import { keywordsCompletionItems } from "../store";
import { inBuiltFunctionsCompletionItems } from "../store/completionItems/functions/inbuilt";
import { ProgramStructure, Stack } from "./stack";

export class ProgramContext {
  stack: Stack<ProgramStructure>;
  rootProgram: ProgramStructure;
  currentFunctionName: string | null = null;
  currentClassName: string | null = null;
  currentModuleName: string | null = null;
  private isInsideBring: boolean = false;
  currentBringFilePath: string | null = null;
  bringStatementMap: Map<string, boolean> = new Map();
  private _syntaxTree: RootObject;

  constructor(syntaxTree: RootObject) {
    this._syntaxTree = syntaxTree;
    this.stack = new Stack<ProgramStructure>();
    this.pushEmptyProgramStructure();

    this.rootProgram = this.stack.peek();

    this.populateBuiltInFunctions();
    this.populateBuiltInKeywords();

    declareGlobals(this.rootProgram, this._syntaxTree, {
      skip: ["ClassStatement", "ModuleStatement"],
    });
  }

  public pushEmptyProgramStructure(): void {
    this.stack.push({
      variableDeclarations: new Map(),
      customTypes: new Map(),
      modules: new Map(),
      classes: new Map(),
      functions: new Map(),
      callExpression: new Map(),
      variableExpressions: new Map(),
      others: new Map(),
    });
  }

  public setCurrentParsingClassName(className: string): void {
    this.currentClassName = className;
  }

  public setCurrentParsingModuleName(moduleName: string): void {
    this.currentModuleName = moduleName;
  }

  public getCurrentParsingClassName(): string | null {
    return this.currentClassName;
  }

  public getCurrentParsingModuleName(): string | null {
    return this.currentModuleName;
  }

  public setCurrentParsingFunctionName(functionName: string): void {
    this.currentFunctionName = functionName;
  }

  public getCurrentParsingFunctionName(): string | null {
    return this.currentFunctionName;
  }

  get syntaxTree(): RootObject {
    return this._syntaxTree;
  }

  public isInsideClass(): boolean {
    return this.currentClassName !== null;
  }

  public isInsideModule(): boolean {
    return this.currentModuleName !== null;
  }

  public isInsideFunction(): boolean {
    return this.currentFunctionName !== null;
  }

  public doesClassExist(className: string): boolean {
    return this.rootProgram.classes.has(className);
  }
  public doesModuleExist(moduleName: string): boolean {
    return this.rootProgram.modules.has(moduleName);
  }

  public isInsideAClassButNotInsideClassMemberFunction(): boolean {
    return this.isInsideClass() && !this.isInsideFunction();
  }
  public isInsideAModuleButNotInsideFunction(): boolean {
    return this.isInsideModule() && !this.isInsideFunction();
  }

  public setInsideBring(val: boolean): void {
    this.isInsideBring = val;
  }

  public onExitBring(): void {
    this.isInsideBring = false;
    this.bringStatementMap = new Map();
    this.currentBringFilePath = null;
  }

  public getIsInsideBring(): boolean {
    return this.isInsideBring;
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
