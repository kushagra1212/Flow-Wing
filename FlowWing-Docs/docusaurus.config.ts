import { themes as prismThemes } from "prism-react-renderer";
import type { Config } from "@docusaurus/types";
import type * as Preset from "@docusaurus/preset-classic";
require("dotenv").config();
const config: Config = {
  title: "Flow-Wing",
  tagline: "A Programming Language",
  favicon: "img/favicon.ico",
  // Set the production url of your site here
  url: "https://flow-wing-docs.vercel.app",
  // Set the /<baseUrl>/ pathname under which your site is served
  // For GitHub pages deployment, it is often '/<projectName>/'
  baseUrl: "/",

  // GitHub pages deployment config.
  // If you aren't using GitHub pages, you don't need these.
  organizationName: "kushagra1212", // Usually your GitHub org/user name.
  projectName: "Flow-Wing", // Usually your repo name.

  onBrokenLinks: "throw",
  onBrokenMarkdownLinks: "warn",

  // Even if you don't use internationalization, you can use this field to set
  // useful metadata like html lang. For example, if your site is Chinese, you
  // may want to replace "en" with "zh-Hans".
  i18n: {
    defaultLocale: "en",
    locales: ["en"],
  },

  presets: [
    [
      "@docusaurus/preset-classic",
      {
        docs: {
          sidebarPath: "./sidebars.ts",
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.x
        },
        blog: {
          showReadingTime: true,
          feedOptions: {
            type: ["rss", "atom"],
            xslt: true,
          },
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          // editUrl:
          //   "https://github.com/facebook/docusaurus/tree/main/packages/create-docusaurus/templates/shared/",
          // Useful options to enforce blogging best practices
          onInlineTags: "warn",
          onInlineAuthors: "warn",
          onUntruncatedBlogPosts: "warn",
        },
        theme: {
          customCss: "./src/css/custom.css",
        },
      } satisfies Preset.Options,
    ],
  ],
  plugins: [
    // ... Your other plugins.
    [
      "docusaurus-plugin-search-local",
      {
        // ... Your options.
        // `hashed` is recommended as long-term-cache of index file is possible.
        hashed: true,
      },
    ],
  ],
  themeConfig: {
    // Replace with your project's social card
    image: "img/flowwing-icon.png",
    navbar: {
      title: "Flow-Wing",
      logo: {
        alt: "Flow-Wing Logo",
        src: "img/flowwing-icon.svg",
      },
      items: [
        {
          type: "docSidebar",
          sidebarId: "tutorialSidebar",
          position: "left",
          label: "Read Docs",
        },
        { to: "/blog", label: "Blog", position: "left" },
        {
          href: "https://github.com/kushagra1212/Flow-Wing",
          label: "GitHub",
          position: "right",
        },
        {
          type: "docsVersionDropdown",
          position: "right",
        },
      ],
    },
    colorMode: {
      defaultMode: "dark",
    },
    footer: {
      style: "dark",
      links: [
        {
          title: "Docs",
          items: [
            {
              label: "Flow-Wing Docs",
              to: "/docs/category/introduction",
            },
          ],
        },
        {
          title: "Community",
          items: [
            {
              label: "Stack Overflow",
              href: "https://stackoverflow.com/questions/tagged/Flowwing",
            },
            {
              label: "Twitter",
              href: "https://x.com/kushagrathore12",
            },
          ],
        },
        {
          title: "More",
          items: [
            {
              label: "Blog",
              to: "/blog",
            },
            {
              label: "GitHub",
              href: "https://github.com/kushagra1212/Flow-Wing",
            },
          ],
        },
      ],
      copyright: `Copyright © ${new Date().getFullYear()} Flow-Wing.`,
    },

    prism: {
      theme: prismThemes.vsDark,
      darkTheme: prismThemes.nightOwl,
      additionalLanguages: ["bash"],
    },
  } satisfies Preset.ThemeConfig,
};

export default config;
