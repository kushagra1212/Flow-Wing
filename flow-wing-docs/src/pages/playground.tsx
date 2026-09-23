import Layout from "@theme/Layout";
import Link from "@docusaurus/Link";
import BrowserOnly from "@docusaurus/BrowserOnly";
import styles from "./playground.module.css";

export default function PlaygroundPage() {
  return (
    <Layout
      title="Playground"
      description="Write Flow-Wing, see every stage of the compiler, and run it in your browser."
    >
      <main className={styles.page}>
        <header className={styles.header}>
          <h1>Playground</h1>
          <p>
            Write Flow-Wing and watch the compiler work on it: the tokens, the
            syntax tree and the semantic tree update as you type, right in your
            browser. Run the program to see the LLVM IR, the WebAssembly, and
            the output. <Link to="/docs/Advanced/How Compilation Works">How compilation works →</Link>
          </p>
        </header>
        {/* The playground uses Web Workers and the address bar: nothing to
            render on the server that builds the site. */}
        <BrowserOnly fallback={<div className={styles.loading}>Loading the playground…</div>}>
          {() => {
            const Playground = require("../components/playground/Playground").default;
            return <Playground />;
          }}
        </BrowserOnly>
      </main>
    </Layout>
  );
}
