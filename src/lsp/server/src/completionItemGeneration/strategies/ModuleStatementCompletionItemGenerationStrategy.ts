import {
  CompletionItem,
  CompletionItemKind,
  MarkupContent,
} from "vscode-languageserver";
import { CompletionItemGenerationStrategy } from "./CompletionItemGenerationStrategy";
import { ModuleStatement } from "../../types";
import { declareGlobals } from "../../completionItemProvider";
import { createRange, getMarkSyntaxHighlightMarkdown } from "../../utils";
import { ModuleExpressionStrategy } from "../../strategies/ModuleExpressionStrategy";

export class ModuleStatementCompletionItemGenerationStrategy extends CompletionItemGenerationStrategy {
  public generateCompletionItems(): CompletionItem[] {
    this.result.name = new ModuleExpressionStrategy().getExpressionAsString(
      this.syntaxObj["ModuleStatement"]
    );

    this.result.completionItem = this.createCompletionItem(
      this.syntaxObj["ModuleStatement"] as ModuleStatement
    );
    this.programCtx.setCurrentParsingModuleName(this.result.name);

    this.programCtx.rootProgram.modules.set(
      this.programCtx.getCurrentParsingModuleName(),
      {
        classes: new Map(),
        customTypes: new Map(),
        variableDeclarations: new Map(),
        functions: new Map(),
        moduleCompletionItem: this.result.completionItem,
        variableExpressions: new Map(),
      }
    );

    declareGlobals(
      this.programCtx.rootProgram.modules.get(
        this.programCtx.getCurrentParsingModuleName()
      ),
      this.syntaxObj["ModuleStatement"],
      {
        skip: ["ClassStatement", "VariableDeclarations", "ModuleStatement"],
      }
    );

    this.programCtx.rootProgram.modules
      .get(this.programCtx.getCurrentParsingModuleName())
      .functions.forEach((value, key) => {
        value.documentation = {
          kind: (value.documentation as MarkupContent).kind,
          value: getMarkSyntaxHighlightMarkdown(
            value.detail +
              `\nmodule ${this.programCtx.getCurrentParsingModuleName()}`
          ),
        };
      });

    this.programCtx.rootProgram.modules
      .get(this.programCtx.getCurrentParsingModuleName())
      .functions.forEach((value, key) => {
        value.label =
          this.programCtx.getCurrentParsingModuleName() + "::" + value.label;
      });

    return [];
  }

  public createCompletionItem(moduleDec: ModuleStatement): CompletionItem {
    let moduleDeclStr = "";
    let index = 0;
    let moduleIdefToken = null;

    moduleDeclStr += "module ";

    if (moduleDec?.[index]?.["OpenBracketToken"])
      moduleDeclStr += moduleDec[index++]["OpenBracketToken"].value;

    if (moduleDec?.[index]?.["LiteralExpression"]?.[0]?.["IdentifierToken"]) {
      moduleIdefToken =
        moduleDec?.[index]?.["LiteralExpression"]?.[0]?.["IdentifierToken"];
      moduleDeclStr +=
        moduleDec?.[index++]?.["LiteralExpression"]?.[0]?.["IdentifierToken"]
          .value;
    }

    if (moduleDec?.[index]?.["CloseBracketToken"])
      moduleDeclStr += moduleDec[index++]["CloseBracketToken"].value + " ";

    const moduleName = new ModuleExpressionStrategy().getExpressionAsString(
      moduleDec
    );

    return {
      label: moduleName,
      kind: CompletionItemKind.Module,
      data: {
        ...createRange(moduleIdefToken),
      },
      detail: moduleDeclStr,
      documentation: {
        kind: "markdown",
        value: getMarkSyntaxHighlightMarkdown(moduleDeclStr),
      },
    };
  }
}
