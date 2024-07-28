import { CompletionItem } from "vscode-languageserver";
import { constantDeclareCompletionItems } from "./completionItems/keywords/const";
import { typesCompletionItems } from "./completionItems/keywords/types";
import { variableDeclareCompletionItems } from "./completionItems/keywords/var";
import { conditionalCompletionItems } from "./completionItems/keywords/conditional";
import { otherCompletionItems } from "./completionItems/keywords/other";

export const keywordsCompletionItems: CompletionItem[] = [
  ...typesCompletionItems,
  ...variableDeclareCompletionItems,
  ...constantDeclareCompletionItems,
  ...conditionalCompletionItems,
  ...otherCompletionItems,
  // ...inBuiltFunctionsCompletionItems,
  // ...punctuationCompletionItems,
];
