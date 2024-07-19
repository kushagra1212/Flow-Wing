import { _Connection, CompletionItem } from "vscode-languageserver";

export function onCompletionResolve(connection: _Connection) {
  connection.onCompletionResolve((item: CompletionItem): CompletionItem => {
    return item;
  });
}
