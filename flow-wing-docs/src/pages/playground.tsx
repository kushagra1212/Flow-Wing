import Layout from "@theme/Layout";
import Playground from "../components/playground/Playground";

export default function PlaygroundPage() {
  return (
    <Layout
      title="Playground"
      description="Write Flow-Wing and run it in your browser."
    >
      <main>
        <Playground />
      </main>
    </Layout>
  );
}
