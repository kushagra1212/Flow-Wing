import {
  _Connection,
  SignatureHelp,
  SignatureHelpParams,
  TextDocuments,
} from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { getTokensForContext } from "../services/suggestionService";
import { getCompletionItems } from "../completionItemProvider";
import { checkForFunctionSignatures } from "../utils";
import {
  getSemPathForDocument,
  getAstPathForDocument,
} from "../services/documentService";
import {
  getSignatureHelpFromSem,
  isSemFormat,
} from "../services/semService";
import { fileUtils } from "../utils/fileUtils";

export async function onSignatureHelp(
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) {
  connection.onSignatureHelp(
    async (params: SignatureHelpParams): Promise<SignatureHelp | undefined> => {
      const document = documents.get(params.textDocument.uri);
      if (!document) return;

      const pos = params.position;
      const tokens = await getTokensForContext(document, pos);
      const suggestion = checkForFunctionSignatures(tokens);

      if (!suggestion.hasFunctionSignature) return;

      // Prefer sem-based signature help (accurate param types from compiler)
      const semPath = await getSemPathForDocument(document, {
        position: pos,
        partialId: suggestion.word || undefined,
      });
      const treePath =
        semPath ??
        (await getAstPathForDocument(document, {
          position: pos,
          partialId: suggestion.word || undefined,
        }));

      if (treePath) {
        try {
          const content = await fileUtils.readFile(treePath);
          const parsed = JSON.parse(content);
          if (isSemFormat(parsed)) {
            const sigHelp = getSignatureHelpFromSem(
              parsed,
              pos,
              suggestion.data.argumentNumber,
              suggestion.word
            );

            if (sigHelp) {
              // Safety: only show if the function name exactly matches or we are in a known active call
              const result = await getCompletionItems(
                treePath,
                suggestion,
                params.textDocument.uri
              );
              const res = result.find((item) => item.label === suggestion.word);
              if (!res) return;

              return sigHelp;
            }
          }
        } catch {
          /* fall through */
        }
      }

      return undefined;
    }
  );
}
