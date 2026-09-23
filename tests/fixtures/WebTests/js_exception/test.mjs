export default async function (t) {
  await t.until(() => t.exited() !== null);
  t.expect(t.exited() === 1, `exit code ${t.exited()}`);
  t.expect(t.output().includes("JavaScript threw an exception"), t.output());
  t.expect(t.output().includes("null"), t.output());
  t.expect(!t.output().includes("never printed"), t.output());
}
