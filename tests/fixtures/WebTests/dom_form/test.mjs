export default async function (t) {
  t.$("#email").value = "ada@example.com";
  const event = new t.window.Event("submit", { cancelable: true, bubbles: true });
  t.$("#signup").dispatchEvent(event);
  // Prevented synchronously, in the listener, not later by the handler.
  t.expect(event.defaultPrevented, "the submit's default was prevented at once");
  await t.until(() => t.$("#result").textContent === "signed up ada@example.com");
}
