export default async function (t) {
  t.type("#name", "Ada — é");
  await t.until(() => t.$("#greeting").textContent === "Hello, Ada — é!");
  t.key("#name", "a");
  t.key("#name", "Enter");
  await t.until(() => t.$("#name").value === "");
  t.$("#agree").click();
  await t.until(() => t.$("#state").textContent === "yes");
  t.$("#agree").click();
  await t.until(() => t.$("#state").textContent === "no");
}
