import Heading from "@theme/Heading";
import Link from "@docusaurus/Link";
import styles from "./styles.module.css";

export default function AboutSection() {
  return (
    <section className={styles.aboutSection}>
      <div className="container">
        <Heading as="h2" className={styles.sectionTitle}>
          About Flow-Wing
        </Heading>
        <p className={styles.lead}>
          <strong>Flow-Wing</strong> is a programming language for <code>.fg</code> source
          files. You get static typing, <code>bring</code> for code and modules, and a
          compiler that can produce a <strong>native app</strong> (AOT) or{" "}
          <strong>run your program in one step</strong> (JIT), depending on which tool you
          install. This site documents <strong>the language and how to use the compiler</strong>
          —not the C++ implementation.
        </p>
        <p className={styles.ctaLine}>
          New here? Open{" "}
          <Link to="/docs/category/introduction">Introduction</Link>, then follow{" "}
          <Link to="/docs/Getting%20Started/Installation">Getting Started → Installation</Link> and{" "}
          <Link to="/docs/Getting%20Started/Hello%20World%20Example">Hello World</Link>.
        </p>
        <h3 className={styles.subheading}>For contributors &amp; curious readers</h3>
        <p className={styles.details}>
          The open-source <strong>Flow-Wing</strong> repository builds the toolchain with
          LLVM, optional AOT/JIT products, a Boehm–GC-based runtime, and a root{" "}
          <code>makefile</code> for dependencies and targets. If you are hacking the
          compiler, see the repository README and <code>AGENTS.md</code>; everyone else can
          ignore those and stay in the docs.
        </p>
      </div>
    </section>
  );
}
