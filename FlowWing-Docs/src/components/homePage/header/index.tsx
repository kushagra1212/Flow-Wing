import useDocusaurusContext from "@docusaurus/useDocusaurusContext";
import clsx from "clsx";
import styles from "./styles.module.css";
import Heading from "@theme/Heading";
import Link from "@docusaurus/Link";
import { useState } from "react";

export default function HomepageHeader() {
  const [isLoaded, setIsLoaded] = useState(false);
  const { siteConfig } = useDocusaurusContext();

  return (
    <header className={styles.heroBanner}>
      <img
        src="img/flowwing-icon.svg"
        alt="Logo"
        className={`${styles.animatedLogo} ${isLoaded ? styles.visible : ""}`}
        onLoad={() => {
          console.log("loaded");
          setIsLoaded(true);
        }}
        fetchPriority="high"
      />{" "}
      <Heading as="h1" className={clsx("hero__title", styles.heroTitle)}>
        {siteConfig.title}
      </Heading>
      <p className={clsx("hero__subtitle", styles.heroSubtitle)}>
        {siteConfig.tagline}
      </p>
      <div className={styles.buttons}>
        <Link
          className="button button--secondary button--lg"
          to="/docs/category/introduction"
        >
          Read Docs
        </Link>
      </div>
    </header>
  );
}
