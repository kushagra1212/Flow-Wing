import { makeCodeCompleteForLsp } from "./out/utils/index.js";

const testCases = [
  "test({b:,a:5})",
  "test({b:})",
  "test({b:,})",
  "test({b:,a:",
  "test({b:,a: "
];

for (const tc of testCases) {
  console.log(`Input:  "${tc}"`);
  console.log(`Output: "${makeCodeCompleteForLsp(tc)}"`);
  console.log("----");
}
