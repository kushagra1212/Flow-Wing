import {
  CompletionItem,
  CompletionItemKind,
  MarkupContent,
} from "vscode-languageserver";
import { ExpressionStrategyFactory } from "../../strategies/ExpressionStrategyFactory";
import { CompletionItemGenerationStrategy } from "./CompletionItemGenerationStrategy";
import { VariableDeclaration } from "../../types";
import { VariableDeclarationExpressionStrategy } from "../../strategies/VariableDeclarationExpressionStrategy";
import { createRange, getMarkSyntaxHighlightMarkdown } from "../../utils";

export class VariableDeclarationCompletionItemGenerationStrategy extends CompletionItemGenerationStrategy {
  public generateCompletionItems(): CompletionItem[] {
    const strategy = ExpressionStrategyFactory.createStrategy(this.syntaxObj);
    this.result.name = strategy.getExpressionAsString(
      this.syntaxObj["VariableDeclaration"]
    );

    this.result.completionItem = this.createCompletionItem(
      this.syntaxObj["VariableDeclaration"]
    );

    if (this.programCtx.isInsideAClassButNotInsideCassMemberFunction()) {
      (this.result.completionItem.documentation as MarkupContent).value += (
        this.programCtx.rootProgram.classes.get(
          this.programCtx.getCurrentParsingClassName()
        ).classCompletionItem.documentation as MarkupContent
      ).value;

      if (
        !this.programCtx.rootProgram.variableExpressions.get(
          this.programCtx.getCurrentParsingClassName() + "."
        )
      ) {
        this.programCtx.rootProgram.variableExpressions.set(
          this.programCtx.getCurrentParsingClassName() + ".",
          []
        );
      }
      this.programCtx.rootProgram.variableExpressions
        .get(this.programCtx.getCurrentParsingClassName() + ".")
        .push(this.result.completionItem);
    }
    if (this.programCtx.isInsideAModuleButNotInsideFunction()) {
      (this.result.completionItem.documentation as MarkupContent).value += (
        this.programCtx.rootProgram.modules.get(
          this.programCtx.getCurrentParsingModuleName()
        ).moduleCompletionItem.documentation as MarkupContent
      ).value;

      // if (
      //   !this.programCtx.rootProgram.variableExpressions.get(
      //     this.programCtx.getCurrentParsingModuleName() + "::"
      //   )
      // ) {
      //   this.programCtx.rootProgram.variableExpressions.set(
      //     this.programCtx.getCurrentParsingModuleName() + "::",
      //     []
      //   );
      // }
      // this.programCtx.rootProgram.variableExpressions
      //   .get(this.programCtx.getCurrentParsingModuleName() + "::")
      //   .push(this.result.completionItem);
    }

    this.programCtx.stack
      ?.peek()
      ?.variableDeclarations?.set(this.result.name, this.result.completionItem);

    this.setClassMembersIfNeeded("variableDeclarations", this.result);
    this.setMoudleMembersIfNeeded("variableDeclarations", this.result);
    return [];
  }

  public createCompletionItem(
    variableDeclaration: VariableDeclaration
  ): CompletionItem {
    let variableDeclarationStr = "";
    let index = 0;
    let idefToken = null;

    const variableName =
      new VariableDeclarationExpressionStrategy().getExpressionAsString(
        variableDeclaration
      );

    if (variableDeclaration[index]["ExposeKeyword"]) {
      variableDeclarationStr +=
        variableDeclaration[index++]["ExposeKeyword"].value + " ";
    }

    if (variableDeclaration[index]["VarKeyword"]) {
      variableDeclarationStr +=
        variableDeclaration[index++]["VarKeyword"].value + " ";
    } else if (variableDeclaration[index]["ConstKeyword"]) {
      variableDeclarationStr +=
        variableDeclaration[index++]["ConstKeyword"].value + " ";
    }

    if (variableDeclaration[index]["InOutKeyword"])
      variableDeclarationStr +=
        variableDeclaration[index++]["InOutKeyword"].value + " ";

    if (variableDeclaration[index]["IdentifierToken"]) {
      idefToken = variableDeclaration[index]["IdentifierToken"];

      variableDeclarationStr +=
        variableDeclaration[index++]["IdentifierToken"].value + ": ";
    }

    if (variableDeclaration[index]["Askeyword"])
      variableDeclarationStr +=
        variableDeclaration[index++]["Askeyword"].value + " ";

    let typeName = "";
    if (variableDeclaration[index]) {
      const strategy = ExpressionStrategyFactory.createStrategy(
        variableDeclaration[index]
      );
      typeName = strategy.getExpressionAsString(variableDeclaration[index]);

      variableDeclarationStr += typeName;
    } else variableDeclarationStr += "unknown";

    return {
      label: variableName,
      kind: CompletionItemKind.Variable,
      data: {
        typeName: typeName,
        ...createRange(idefToken),
      },
      detail: variableDeclarationStr,
      documentation: {
        kind: "markdown",
        value: getMarkSyntaxHighlightMarkdown(variableDeclarationStr),
      },
    };
  }
}
