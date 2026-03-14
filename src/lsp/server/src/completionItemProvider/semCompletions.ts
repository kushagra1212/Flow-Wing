/**
 * Re-exports sem completion and format check from semService.
 * Kept for backward compatibility with completionItemProvider.
 */

import {
  getCompletionItemsFromSem as getSemCompletions,
  isSemFormat,
} from "../services/semService";

export function getCompletionItemsFromSem(
  semJson: Parameters<typeof getSemCompletions>[0],
  suggestion: { word?: string; data?: { isDot?: boolean; isValueCompletion?: boolean } },
  uri: string
): ReturnType<typeof getSemCompletions> {
  return getSemCompletions(
    semJson,
    suggestion?.word ?? "",
    suggestion?.data?.isDot ?? false,
    uri,
    suggestion?.data?.isValueCompletion ?? false
  );
}

export { isSemFormat };
