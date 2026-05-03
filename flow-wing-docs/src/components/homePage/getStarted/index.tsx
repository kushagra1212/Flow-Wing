import Heading from "@theme/Heading";
import styles from "./styles.module.css";
import Link from "@docusaurus/Link";
import clsx from "clsx";

export default function GetStartedSection() {
  return (
    <section className={styles.getStartedSection}>
      <div className="container">
        <Heading as="h2" className={styles.sectionTitle}>
          Get Started
        </Heading>
        <p className={styles.sectionDescription}>
          Ready to start? Check out our documentation to dive into Flow-Wing and
          explore its features.
        </p>
      </div>
      <div className={styles.startLearningButtonContainer}>
        <Link
          className={styles.startLearningButton}
          to="/docs/category/introduction"
        >
          Start Learning
        </Link>
      </div>
    </section>
  );
}
