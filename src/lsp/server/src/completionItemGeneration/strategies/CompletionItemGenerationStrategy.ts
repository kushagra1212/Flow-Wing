import { CompletionItem } from "vscode-languageserver";
import { ProgramContext } from "../../ds/programContext";
import { ProgramStructure } from "../../ds/stack";

export abstract class CompletionItemGenerationStrategy {
  public result: { name: string; completionItem: CompletionItem } = {
    name: "",
    completionItem: null,
  };

  constructor(
    public programCtx: ProgramContext = null,
    public syntaxObj: any = null
  ) {}

  public abstract generateCompletionItems(): CompletionItem[];
  public abstract createCompletionItem(expr: any): CompletionItem;

  public setClassMembersIfNeeded(
    expressionName: keyof ProgramStructure,
    value: { name: string; completionItem: CompletionItem }
  ) {
    if (this.programCtx.isInsideAClassButNotInsideCassMemberFunction()) {
      this.programCtx.rootProgram?.classes
        .get(this.programCtx.getCurrentParsingClassName())
        ?.[expressionName]?.set(value.name, value.completionItem);
    }
  }

  public setMoudleMembersIfNeeded(
    expressionName: keyof ProgramStructure,
    value: { name: string; completionItem: CompletionItem }
  ) {
    if (this.programCtx.isInsideAModuleButNotInsideFunction()) {
      this.programCtx.rootProgram?.modules
        .get(this.programCtx.getCurrentParsingModuleName())
        ?.[expressionName]?.set(value.name, value.completionItem);
    }
  }
}
