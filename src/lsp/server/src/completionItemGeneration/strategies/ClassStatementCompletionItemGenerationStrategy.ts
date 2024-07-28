import {
  CompletionItem,
  CompletionItemKind,
  MarkupContent,
} from "vscode-languageserver";
import { CompletionItemGenerationFactory } from "../completionItemGenerationFactory";
import { CompletionItemGenerationStrategy } from "./CompletionItemGenerationStrategy";
import { ClassExpressionStrategy } from "../../strategies/ClassExpressionStrategy";
import { ClassStatement } from "../../types";
import { declareGlobals } from "../../completionItemProvider";
import { createRange, getMarkSyntaxHighlightMarkdown } from "../../utils";

export class ClassStatementCompletionItemGenerationStrategy extends CompletionItemGenerationStrategy {
  public generateCompletionItems(): CompletionItem[] {
    this.result.name = new ClassExpressionStrategy().getExpressionAsString(
      this.syntaxObj["ClassStatement"]
    );

    this.result.completionItem = this.createCompletionItem(
      this.syntaxObj["ClassStatement"] as ClassStatement
    );

    this.programCtx.setCurrentParsingClassName(this.result.name);

    this.programCtx.rootProgram.classes.set(
      this.programCtx.getCurrentParsingClassName(),
      {
        classCompletionItem: this.result.completionItem,
        callExpression: new Map(),
        customTypes: new Map(),
        variableDeclarations: new Map(),
        functions: new Map(),
        variableExpressions: new Map(),
      }
    );

    declareGlobals(
      this.programCtx.rootProgram.classes.get(
        this.programCtx.getCurrentParsingClassName()
      ),
      this.syntaxObj["ClassStatement"],
      {
        skip: ["ClassStatement", "VariableDeclarations"],
      }
    );

    this.programCtx.rootProgram.classes
      .get(this.programCtx.getCurrentParsingClassName())
      .functions.forEach((value, key) => {
        value.documentation = {
          kind: (value.documentation as MarkupContent).kind,
          value: getMarkSyntaxHighlightMarkdown(
            value.detail +
              `\nclass ${this.programCtx.getCurrentParsingClassName()}`
          ),
        };
      });

    if (
      this.syntaxObj["ClassStatement"]?.length >= 4 &&
      this.syntaxObj["ClassStatement"][2]["ExtendsKeyword"] &&
      this.syntaxObj["ClassStatement"][3]["IdentifierToken"]
    ) {
      const parentClassName =
        this.syntaxObj["ClassStatement"][3]["IdentifierToken"]?.value;

      if (this.programCtx.rootProgram.classes.has(parentClassName)) {
        const parentClass =
          this.programCtx.rootProgram.classes.get(parentClassName);
        parentClass.functions.forEach((value, key) => {
          this.programCtx.rootProgram.classes
            .get(this.programCtx.getCurrentParsingClassName())
            ?.functions?.set(key, value);
        });
        parentClass.variableDeclarations.forEach((value, key) => {
          this.programCtx.rootProgram.classes
            .get(this.programCtx.getCurrentParsingClassName())
            ?.variableDeclarations?.set(key, value);
        });
        parentClass.variableExpressions.forEach((value, key) => {
          this.programCtx.rootProgram.classes
            .get(this.programCtx.getCurrentParsingClassName())
            ?.variableExpressions?.set(key, value);
        });
      }
    }

    return [];
  }

  public createCompletionItem(
    classDeclaration: ClassStatement
  ): CompletionItem {
    let classDeclarationStr = "";
    let index = 0;
    let classIdefToken = null;

    if (classDeclaration[index]["ExposeKeyword"])
      classDeclarationStr +=
        classDeclaration[index++]["ExposeKeyword"].value + " ";

    if (classDeclaration[index]["ClassKeyword"])
      classDeclarationStr +=
        classDeclaration[index++]["ClassKeyword"].value + " ";

    if (classDeclaration[index]["IdentifierToken"]) {
      classIdefToken = classDeclaration[index]["IdentifierToken"];
      classDeclarationStr += classDeclaration[index++]["IdentifierToken"].value;
    }

    const className = new ClassExpressionStrategy().getExpressionAsString(
      classDeclaration
    );

    return {
      label: className,
      kind: CompletionItemKind.Class,
      data: {
        ...createRange(classIdefToken),
      },
      detail: classDeclarationStr,
      documentation: {
        kind: "markdown",
        value: getMarkSyntaxHighlightMarkdown(classDeclarationStr),
      },
    };
  }
}
