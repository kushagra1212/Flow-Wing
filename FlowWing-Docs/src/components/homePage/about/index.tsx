import Heading from "@theme/Heading";
import styles from "./styles.module.css";

export default function AboutSection() {
  return (
    <section className={styles.aboutSection}>
      <div className="container">
        <Heading as="h2" className={styles.sectionTitle}>
          About Flow-Wing
        </Heading>
        <p className={styles.sectionDescription}>
          Flow-Wing is a Simple programming language 
        </p>
      </div>
    </section>
  );
}
