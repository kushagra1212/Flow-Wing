import { CompletionItem, CompletionItemKind } from "vscode-languageserver";
import { CompletionItemGenerationFactory } from "../completionItemGenerationFactory";
import { CompletionItemGenerationStrategy } from "./CompletionItemGenerationStrategy";
import { ClassExpressionStrategy } from "../../strategies/ClassExpressionStrategy";
import { ClassStatement } from "../../types";
import { declareGlobals } from "../../completionItemProvider";
import { getMarkSyntaxHighlightMarkdown } from "../../utils";

export class ClassStatementCompletionItemGenerationStrategy extends CompletionItemGenerationStrategy {
  public generateCompletionItems(): CompletionItem[] {
    this.result.name = new ClassExpressionStrategy().getExpressionAsString(
      this.syntaxObj["ClassStatement"]
    );
    this.result.completionItem = this.createCompletionItem(
      this.syntaxObj["ClassStatement"] as ClassStatement
    );
    this.programCtx.currentParsingClassName = this.result.name;

    this.programCtx.rootProgram.classes.set(this.result.name, {
      classCompletionItem: this.result.completionItem,
      callExpression: new Map(),
      customTypes: new Map(),
      variableDeclarations: new Map(),
      functions: new Map(),
      variableExpressions: new Map(),
    });

    declareGlobals(
      this.programCtx.stack?.peek(),
      this.syntaxObj["ClassStatement"],
      {
        skip: [],
      }
    );

    this.programCtx.stack?.peek()?.functions.forEach((value, key) => {
      this.programCtx.rootProgram.classes
        .get(this.programCtx.currentParsingClassName)
        ?.functions?.set(key, value);
    });

    return [];
  }

  public createCompletionItem(
    classDeclaration: ClassStatement
  ): CompletionItem {
    let classDeclarationStr = "";

    if (classDeclaration[0]["ClassKeyword"])
      classDeclarationStr += classDeclaration[0]["ClassKeyword"].value + " ";

    if (classDeclaration[1]["IdentifierToken"])
      classDeclarationStr += classDeclaration[1]["IdentifierToken"].value;

    const className = new ClassExpressionStrategy().getExpressionAsString(
      classDeclaration
    );

    return {
      label: className,
      kind: CompletionItemKind.Class,
      data: "class",
      detail: classDeclarationStr,
      documentation: {
        kind: "markdown",
        value: getMarkSyntaxHighlightMarkdown(classDeclarationStr),
      },
    };
  }
}
