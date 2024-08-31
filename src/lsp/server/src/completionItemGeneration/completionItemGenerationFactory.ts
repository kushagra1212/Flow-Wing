import { CompletionItem } from "vscode-languageserver";
import { CompletionItemGenerationStrategy } from "./strategies/CompletionItemGenerationStrategy";
import { ProgramContext } from "../ds/programContext";
import { VariableDeclarationCompletionItemGenerationStrategy } from "./strategies/VariableDeclarationCompletionItemGenerationStrategy";
import { CallExpressionCompletionItemGenerationStrategy } from "./strategies/CallExpressionCompletionItemGenerationStrategy";
import { CustomTypeCompletionItemGenerationStrategy } from "./strategies/CustomTypeCompletionItemGenerationStrategy";
import { BracketedExpressionCompletionItemGenerationStrategy } from "./strategies/BracketedExpressionCompletionItemGenerationStrategy";
import { FunctionDeclarationCompletionItemGenerationStrategy } from "./strategies/FunctionDeclarationCompletionItemGenerationStrategy";
import { ClassStatementCompletionItemGenerationStrategy } from "./strategies/ClassStatementCompletionItemGenerationStrategy";
import { ModuleStatementCompletionItemGenerationStrategy } from "./strategies/ModuleStatementCompletionItemGenerationStrategy";

export class CompletionItemGenerationFactory {
  static create(
    programContext: ProgramContext,
    syntaxObj: any
  ): CompletionItemGenerationStrategy {
    if (syntaxObj["VariableDeclaration"]) {
      return new VariableDeclarationCompletionItemGenerationStrategy(
        programContext,
        syntaxObj
      );
    } else if (syntaxObj["CallExpression"]) {
      return new CallExpressionCompletionItemGenerationStrategy(
        programContext,
        syntaxObj
      );
    } else if (syntaxObj["CustomTypeStatement"]) {
      return new CustomTypeCompletionItemGenerationStrategy(
        programContext,
        syntaxObj
      );
    } else if (syntaxObj["BracketedExpression"]) {
      return new BracketedExpressionCompletionItemGenerationStrategy(
        programContext,
        syntaxObj
      );
    } else if (syntaxObj["FunctionDeclarationSyntax"]) {
      return new FunctionDeclarationCompletionItemGenerationStrategy(
        programContext,
        syntaxObj
      );
    } else if (syntaxObj["ClassStatement"]) {
      return new ClassStatementCompletionItemGenerationStrategy(
        programContext,
        syntaxObj
      );
    } else if (syntaxObj["ModuleStatement"]) {
      return new ModuleStatementCompletionItemGenerationStrategy(
        programContext,
        syntaxObj
      );
    }

    return null;
  }
}
