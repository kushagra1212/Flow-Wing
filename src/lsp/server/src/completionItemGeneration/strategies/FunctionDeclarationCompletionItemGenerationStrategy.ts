import {
  CompletionItem,
  CompletionItemKind,
  ParameterInformation,
} from "vscode-languageserver";
import { CompletionItemGenerationStrategy } from "./CompletionItemGenerationStrategy";
import { FunctionDeclaration } from "../../types";
import { VariableDeclarationCompletionItemGenerationStrategy } from "./VariableDeclarationCompletionItemGenerationStrategy";
import { ExpressionStrategyFactory } from "../../strategies/ExpressionStrategyFactory";
import { FunctionDeclarationExpressionStrategy } from "../../strategies/FunctionDeclarationExpressionStrategy";
import { getMarkSyntaxHighlightMarkdown } from "../../utils";

export class FunctionDeclarationCompletionItemGenerationStrategy extends CompletionItemGenerationStrategy {
  public generateCompletionItems(): CompletionItem[] {
    this.result.name =
      new FunctionDeclarationExpressionStrategy().getExpressionAsString(
        this.syntaxObj["FunctionDeclarationSyntax"]
      );

    this.programCtx.setCurrentParsingFunctionName(this.result.name);

    return [];
  }

  public createCompletionItem(
    functionDeclaration: FunctionDeclaration
  ): CompletionItem {
    let functionDeclarationStr = "";
    let index = 0;

    if (functionDeclaration[index]["FunctionKeyword"])
      functionDeclarationStr +=
        functionDeclaration[index++]["FunctionKeyword"].value + " ";
    else functionDeclarationStr += "fun ";

    if (functionDeclaration[index]["IdentifierToken"])
      functionDeclarationStr +=
        functionDeclaration[index++]["IdentifierToken"].value;

    functionDeclarationStr += "(";
    let hasCommaAtEnd = false;

    const functionParameters: ParameterInformation[] = [];
    const functionParametersTypes: string[] = [];
    while (functionDeclaration[index]["VariableDeclaration"]) {
      const functionParameter =
        new VariableDeclarationCompletionItemGenerationStrategy().createCompletionItem(
          functionDeclaration[index++]["VariableDeclaration"]
        );
      //   this.programCtx.stack
      //     .peek()
      //     .variableDeclarations.set(functionParameter.label, functionParameter);
      functionDeclarationStr += functionParameter.detail + ", ";
      functionParameters.push({
        label: functionParameter.label,
        documentation: functionParameter.documentation,
      });
      functionParametersTypes.push(functionParameter.data.typeName);
      hasCommaAtEnd = true;
    }

    if (hasCommaAtEnd)
      functionDeclarationStr = functionDeclarationStr.slice(
        0,
        functionDeclarationStr.length - 2
      );

    functionDeclarationStr += ") -> ";
    while (index < functionDeclaration.length) {
      if (functionDeclaration[index]["Askeyword"])
        functionDeclarationStr +=
          functionDeclaration[index]["Askeyword"].value + " ";

      if (functionDeclaration[index]["DeclKeyword"])
        functionDeclarationStr +=
          functionDeclaration[index]["DeclKeyword"].value + " ";
      if (functionDeclaration[index]) {
        const strategy = ExpressionStrategyFactory.createStrategy(
          functionDeclaration[index]
        );
        if (strategy)
          functionDeclarationStr += strategy.getExpressionAsString(
            functionDeclaration[index]
          );
      }
      index++;
    }

    const functionName =
      new FunctionDeclarationExpressionStrategy().getExpressionAsString(
        functionDeclaration
      );

    functionDeclarationStr = this.programCtx?.isInsideClass()
      ? `${(functionDeclarationStr =
          this.programCtx.getCurrentParsingClassName())}:${functionDeclarationStr.replace(
          "fun",
          ""
        )}`
      : functionDeclarationStr;

    return {
      label: functionName,
      kind: CompletionItemKind.Function,
      data: {
        signatures: [
          {
            label: functionDeclarationStr,
            parameters: functionParameters,
          },
        ],
        functionParametersTypes: functionParametersTypes,
      },
      detail: functionDeclarationStr,
      documentation: {
        kind: "markdown",
        value: getMarkSyntaxHighlightMarkdown(functionDeclarationStr),
      },
    };
  }
}
