import {
  CompletionItem,
  CompletionItemKind,
  MarkupContent,
} from "vscode-languageserver";
import { CompletionItemGenerationStrategy } from "./CompletionItemGenerationStrategy";
import { CustomTypeExpressionStrategy } from "../../strategies/CustomTypeExpressionStrategy";
import { CustomTypeStatement } from "../../types";
import { LiteralExpressionStrategy } from "../../strategies/LiteralExpressionStrategy";
import {
  createRange,
  getArrayType,
  getMarkSyntaxHighlightMarkdown,
  isPrimitiveType,
} from "../../utils";
import { CompletionItemService } from "../../services/completionItemService";
import { ScopeCompletionItemsStrategy } from "../../strategies/CompletionItemStrategy/ScopeCompletionItemsStrategy";
import { BracketedExpressionCompletionItemGenerationStrategy } from "./BracketedExpressionCompletionItemGenerationStrategy";
import { typesCompletionItems } from "../../store/completionItems/keywords/types";
import { ClassCompletionItem } from "../../ds/stack";

export class CustomTypeCompletionItemGenerationStrategy extends CompletionItemGenerationStrategy {
  public generateCompletionItems(): CompletionItem[] {
    this.result.name = new CustomTypeExpressionStrategy().getExpressionAsString(
      this.syntaxObj["CustomTypeStatement"]
    );

    this.result.completionItem = this.createCompletionItem(
      this.syntaxObj["CustomTypeStatement"] as CustomTypeStatement
    );

    this.programCtx.stack
      ?.peek()
      ?.customTypes?.set(this.result.name, this.result.completionItem);

    if (this.result.completionItem.label !== "unknown") {
      this.populateVariableExpressionCompletionItem(
        this.result.completionItem.label,
        this.result.completionItem.label
      );
    }

    if (this.programCtx.isInsideAModuleButNotInsideFunction()) {
      (this.result.completionItem.documentation as MarkupContent).value += (
        this.programCtx.rootProgram.modules.get(
          this.programCtx.getCurrentParsingModuleName()
        ).moduleCompletionItem.documentation as MarkupContent
      ).value;
    }

    this.setClassMembersIfNeeded("customTypes", this.result);
    this.setModuleMembersIfNeeded("customTypes", this.result);

    return [];
  }

  private populateVariableExpressionCompletionItem = (
    variableName: string,
    typeName: string
  ): void => {
    if (isPrimitiveType(typeName)) {
      const ci = typesCompletionItems.find((item) => item.label === typeName);
      this.programCtx.stack?.peek().variableExpressions.set(variableName, [ci]);
      if (this.programCtx.isInsideAModuleButNotInsideFunction()) {
        this.programCtx.rootProgram.modules
          .get(this.programCtx.getCurrentParsingModuleName())
          .variableExpressions.set(variableName, [ci]);
      }
      return;
    }

    const customTypesCompletionItem = new CompletionItemService(
      new ScopeCompletionItemsStrategy()
    ).getCompletionItems({
      programCtx: this.programCtx,
      identifier: typeName,
      expressionName: "customTypes",
    })?.[0];

    if (variableName.split(".")?.length) {
      this.programCtx.stack
        ?.peek()
        .variableExpressions.set(variableName, [customTypesCompletionItem]);

      if (this.programCtx.isInsideAModuleButNotInsideFunction()) {
        this.programCtx.rootProgram.modules
          .get(this.programCtx.getCurrentParsingModuleName())
          .variableExpressions.set(variableName, [customTypesCompletionItem]);
      }
    }
    const handleItem = (
      innerVariableName: string,
      item: any,
      variableExpression: ClassCompletionItem["variableExpressions"]
    ) => {
      if (!variableExpression.get(innerVariableName)) {
        variableExpression.set(innerVariableName, []);
      }
      variableExpression.get(innerVariableName).push(item);

      const array = getArrayType(item.data.typeName);

      if (array.isArray) {
        this.populateVariableExpressionCompletionItem(
          innerVariableName + item.label + array.dim,
          array.ofType
        );
      } else {
        this.populateVariableExpressionCompletionItem(
          innerVariableName + item.label,
          item.data.typeName
        );
      }
    };
    if (customTypesCompletionItem && customTypesCompletionItem.data?.items) {
      const innerVariableName = variableName + ".";
      for (const item of customTypesCompletionItem.data.items) {
        handleItem(
          innerVariableName,
          item,
          this.programCtx.stack?.peek().variableExpressions
        );

        if (this.programCtx.isInsideAModuleButNotInsideFunction()) {
          handleItem(
            innerVariableName,
            item,
            this.programCtx.rootProgram.modules.get(
              this.programCtx.getCurrentParsingModuleName()
            ).variableExpressions
          );
        }
      }
    }
  };
  public createCompletionItem(
    customTypeStatement: CustomTypeStatement
  ): CompletionItem {
    let customTypeStatementString = "type ";
    let custumTypeIdef = null;
    let index = 0;

    if (customTypeStatement?.[index]?.["ExposeKeyword"]) {
      customTypeStatementString +=
        customTypeStatement[index++]["ExposeKeyword"].value + " ";
    }

    if (customTypeStatement?.[index]?.["LiteralExpression"]) {
      custumTypeIdef =
        customTypeStatement[index]["LiteralExpression"][0]["IdentifierToken"];
      let typeName = new LiteralExpressionStrategy().getExpressionAsString(
        customTypeStatement[index++]["LiteralExpression"][0]
      );

      typeName = typeName.substring(0, typeName.lastIndexOf("."));
      customTypeStatementString += typeName + " = {\n";
    }
    const data = [];
    for (let i = index; i < customTypeStatement.length; i++) {
      customTypeStatementString += "\t";
      if (customTypeStatement[i]["BracketedExpression"]) {
        data.push({
          ...new BracketedExpressionCompletionItemGenerationStrategy().createCompletionItem(
            customTypeStatement[i]["BracketedExpression"]
          ),
          kind: CompletionItemKind.Variable,
        });
        customTypeStatementString +=
          data[data.length - 1].detail +
          (i == customTypeStatement.length - 1 ? "\n" : ",\n");
      }
    }
    customTypeStatementString += "}\n";

    const typeName = new CustomTypeExpressionStrategy().getExpressionAsString(
      customTypeStatement
    );

    return {
      label: typeName,
      kind: CompletionItemKind.TypeParameter,
      data: {
        items: data,
        ...createRange(custumTypeIdef),
      },
      detail: "Custom Type",
      documentation: {
        kind: "markdown",
        value: getMarkSyntaxHighlightMarkdown(customTypeStatementString),
      },
    };
  }
}
