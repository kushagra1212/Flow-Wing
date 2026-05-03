import clsx from "clsx";
import Link from "@docusaurus/Link";
import Heading from "@theme/Heading";

import styles from "./index.module.css";
import Layout from "../components/layout";
import HomepageHeader from "../components/homePage/header";
import AboutSection from "../components/homePage/about";
import GetStartedSection from "../components/homePage/getStarted";

export default function Home(): JSX.Element {
  return (
    <Layout>
      <HomepageHeader />
      <main>
        <AboutSection />
        <GetStartedSection />
      </main>
    </Layout>
  );
}
