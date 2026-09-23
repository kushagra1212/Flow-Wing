// jsdom has no fetch: the page gets a small one, before the program starts.
export async function setup(t) {
  t.window.fetch = async (url) => {
    await new Promise((resolve) => setTimeout(resolve, 10));
    if (url === "/data.txt") return { ok: true, status: 200, text: async () => "line one\nline two — é" };
    return { ok: false, status: 404, text: async () => "not found" };
  };
}

export default async function (t) {
  t.click("#load");
  await t.until(() => t.exited() !== null);
  t.expectText("#data", "line one\nline two — é");
  t.expectText("#error", "HTTP 404 for /missing.txt");
}
