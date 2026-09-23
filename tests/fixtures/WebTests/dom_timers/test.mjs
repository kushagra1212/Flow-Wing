export default async function (t) {
  await t.until(() => t.exited() !== null, 3000);
  t.expect(t.exited() === 0, `exit code ${t.exited()}`);
  t.expectText("#later", "done later ()");
  t.expectText("#ticks", "3");
  t.expectText("#never", "untouched");
}
