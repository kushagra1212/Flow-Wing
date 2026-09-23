export default async function (t) {
  const add = async (label) => {
    t.$("#item").value = label;
    t.click("#add");
    await t.until(() => [...t.document.querySelectorAll("#list li")].some((li) => li.dataset.label === label));
  };
  await add("milk");
  await add("bread");
  await add("eggs");
  t.expectText("#total", "3 items");
  t.expect(t.$("#list li:nth-child(2) span").textContent === "bread", "second row is bread");
  // Remove the middle row with its own button.
  t.$("#list li:nth-child(2) button.remove").click();
  await t.until(() => t.document.querySelectorAll("#list li").length === 2);
  t.expectText("#total", "2 items");
  t.expect([...t.document.querySelectorAll("#list li span")].map((s) => s.textContent).join(",") === "milk,eggs", "milk and eggs remain");
}
