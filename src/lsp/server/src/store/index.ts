import { CompletionItem } from "vscode-languageserver";
import { constantDeclareCompletionItems } from "./keywords/const";
import { typesCompletionItems } from "./keywords/types";
import { variableDeclareCompletionItems } from "./keywords/var";
import { conditionalCompletionItems } from "./keywords/conditional";
import { otherCompletionItems } from "./keywords/other";
import { inBuiltFunctionsCompletionItems } from "./functions/inbuilt";
import { punctuationCompletionItems } from "./puntuation";

export const keywordsCompletionItems: CompletionItem[] = [
  ...typesCompletionItems,
  ...variableDeclareCompletionItems,
  ...constantDeclareCompletionItems,
  ...conditionalCompletionItems,
  ...otherCompletionItems,
  ...inBuiltFunctionsCompletionItems,
  // ...punctuationCompletionItems,
];
