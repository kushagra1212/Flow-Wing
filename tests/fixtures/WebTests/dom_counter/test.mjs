export default async function (t) {
  t.expectText("#count", "0");
  t.click("#add");
  t.click("#add");
  t.click("#add");
  await t.until(() => t.$("#count").textContent === "3");
  t.click("#reset");
  await t.until(() => t.$("#count").textContent === "0");
  t.click("#add");
  await t.until(() => t.$("#count").textContent === "1");
}
