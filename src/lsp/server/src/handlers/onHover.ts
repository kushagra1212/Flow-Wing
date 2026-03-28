import { _Connection, HoverParams, TextDocuments } from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import {
  getDocumentationForCompletionItem,
  getTokensForContext,
} from "../services/suggestionService";
import { checkForHover, getFullPathAtPosition, getIdentifierAtPosition } from "../utils";
import {
  getSemPathForDocument,
  getAstPathForDocument,
} from "../services/documentService";
import { getHoverFromSem, isSemFormat } from "../services/semService";
import { logger } from "../services/loggerService";
import { fileUtils } from "../utils/fileUtils";

export const onHover = async (
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) => {
  connection.onHover(async (params: HoverParams) => {
    const document = documents.get(params.textDocument.uri);
    if (!document) return { contents: null };

    const pos = params.position;
    const partialId = getIdentifierAtPosition(document.getText(), pos);
    logger.debug("hover", "pos", pos, "partialId", partialId);

    // Prefer sem-based hover (uses tree position for accurate symbol lookup)
    const semPath = await getSemPathForDocument(document, {
      position: pos,
      partialId: partialId || undefined,
    });
    const treePath =
      semPath ??
      (await getAstPathForDocument(document, {
        position: pos,
        partialId: partialId || undefined,
      }));

    if (treePath) {
      try {
        const content = await fileUtils.readFile(treePath);
        const parsed = JSON.parse(content);
        if (isSemFormat(parsed)) {
          const fullPath = getFullPathAtPosition(document.getText(), pos);
          logger.debug("hover", "fullPath", fullPath);
          const hover = getHoverFromSem(
            parsed,
            pos,
            partialId || undefined,
            fullPath || undefined,
            document.getText()
          );
          if (hover) {
            logger.debug("hover", "resolved from sem");
            return { contents: hover };
          }
        }
      } catch {
        /* fall through to legacy */
      }
    }

    // Fallback: token-based suggestion + completion lookup
    logger.debug("hover", "fallback to token-based");
    const tokens = await getTokensForContext(document, pos);
    const suggestion = checkForHover(tokens);

    if (!suggestion?.hasHoverResult) {
      return { contents: null };
    }

    const documentation = await getDocumentationForCompletionItem(
      params.textDocument.uri,
      suggestion,
      document.getText()
    );

    return { contents: documentation };
  });
};
