import { _Connection, CompletionItem } from "vscode-languageserver";
import { inBuiltFunctionsCompletionItems } from "../store";

export function onCompletionResolve(connection: _Connection) {
  connection.onCompletionResolve((item: CompletionItem): CompletionItem => {
    // Resolve full documentation for built-in functions
    const builtIn = inBuiltFunctionsCompletionItems.find(
      (b) => b.label === item.label
    );
    if (builtIn?.documentation) {
      return {
        ...item,
        documentation: builtIn.documentation,
        detail: builtIn.detail ?? item.detail,
      };
    }
    return item;
  });
}
