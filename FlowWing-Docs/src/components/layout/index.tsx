import useDocusaurusContext from "@docusaurus/useDocusaurusContext";
import styles from "./index.module.css";
import ThemeLayout from "@theme/Layout";

const Layout = ({ children }) => {
  const { siteConfig } = useDocusaurusContext();

  return (
    <ThemeLayout
      title={`Welcome to ${siteConfig.title} - Flow-Wing Language`}
      description="Flow-Wing Programming Language"
    >
      <div className={styles.background}>{children}</div>
    </ThemeLayout>
  );
};

export default Layout;
