import { defineUserConfig } from 'vuepress'
import { defaultTheme } from '@vuepress/theme-default'
import { viteBundler } from '@vuepress/bundler-vite'
import { searchPlugin } from '@vuepress/plugin-search'

export default defineUserConfig({
  lang: 'zh-CN',
  title: 'Croupier C++ SDK',
  description: '高性能 C++ SDK，用于 Croupier 游戏函数注册与虚拟对象管理',
  head: [
    ['meta', { name: 'viewport', content: 'width=device-width,initial-scale=1' }],
    ['meta', { name: 'keywords', content: 'croupier,cpp,sdk,gRPC,游戏开发,虚拟对象' }],
    ['meta', { name: 'theme-color', content: '#3eaf7c' }],
    ['meta', { property: 'og:type', content: 'website' }],
    ['meta', { property: 'og:locale', content: 'zh-CN' }],
    ['meta', { property: 'og:title', content: 'Croupier C++ SDK' }],
    ['meta', { property: 'og:site_name', content: 'Croupier C++ SDK' }],
  ],
  base: '/croupier-sdk-cpp/',
  bundler: viteBundler({
    viteOptions: {
      build: {
        chunkSizeWarningLimit: 1200,
      },
    },
  }),
  theme: defaultTheme({
    repo: 'cuihairu/croupier-sdk-cpp',
    repoLabel: 'GitHub',
    editLinkText: '在 GitHub 上编辑此页',
    lastUpdated: true,
    lastUpdatedText: '最后更新',
    contributors: false,
    logo: '/logo.png',

    navbar: [
      {
        text: '指南',
        link: '/guide/',
      },
      {
        text: 'API 参考',
        link: '/api/',
      },
      {
        text: '示例',
        link: '/examples/',
      },
      {
        text: '配置',
        link: '/configuration/',
      },
      {
        text: '其他 SDK',
        children: [
          {
            text: 'Go SDK',
            link: 'https://cuihairu.github.io/croupier-sdk-go/',
          },
          {
            text: 'Java SDK',
            link: 'https://cuihairu.github.io/croupier-sdk-java/',
          },
          {
            text: 'JavaScript SDK',
            link: 'https://cuihairu.github.io/croupier-sdk-js/',
          },
          {
            text: 'Python SDK',
            link: 'https://cuihairu.github.io/croupier-sdk-python/',
          },
        ],
      },
    ],

    sidebar: {
      '/guide/': [
        {
          text: '入门指南',
          collapsable: false,
          children: [
            '/guide/README.md',
            '/guide/installation.md',
            '/guide/quick-start.md',
            '/guide/building.md',
          ],
        },
        {
          text: '核心概念',
          children: [
            '/guide/architecture.md',
            '/guide/virtual-objects.md',
            '/guide/functions.md',
          ],
        },
        {
          text: '高级主题',
          children: [
            '/guide/plugins.md',
            '/guide/deployment.md',
            '/guide/testing.md',
          ],
        },
      ],

      '/api/': [
        {
          text: 'API 参考',
          collapsable: false,
          children: [
            '/api/README.md',
            '/api/client.md',
            '/api/config.md',
            '/api/functions.md',
            '/api/virtual-objects.md',
          ],
        },
      ],

      '/examples/': [
        {
          text: '使用示例',
          collapsable: false,
          children: [
            '/examples/README.md',
            '/examples/basic-function.md',
            '/examples/virtual-object.md',
            '/examples/plugin.md',
            '/examples/comprehensive.md',
          ],
        },
      ],

      '/configuration/': [
        {
          text: '配置指南',
          collapsable: false,
          children: [
            '/configuration/README.md',
            '/configuration/client-config.md',
            '/configuration/environments.md',
            '/configuration/security.md',
          ],
        },
      ],

      '/': [
        {
          text: '概览',
          collapsible: false,
          children: [
            '/README.md',
          ],
        },
        {
          text: '指南',
          collapsible: false,
          children: [
            '/guide/README.md',
            '/guide/installation.md',
            '/guide/quick-start.md',
            '/guide/building.md',
          ],
        },
        {
          text: 'API 参考',
          collapsible: false,
          children: [
            '/api/README.md',
            '/api/client.md',
          ],
        },
        {
          text: '示例',
          collapsible: false,
          children: [
            '/examples/README.md',
          ],
        },
        {
          text: '配置',
          collapsible: false,
          children: [
            '/configuration/README.md',
          ],
        },
      ],
    },

    themePlugins: {
      git: true,
      gitContributors: false,
      prismHighlighter: true,
      nprogress: true,
      backToTop: true,
    },
  }),

  plugins: [
    searchPlugin({
      locales: {
        '/': {
          placeholder: '搜索文档',
          hotKeys: ['k', '/'],
        },
      },
      hotSearchOnlyFocus: true,
      maxSuggestions: 10,
    }),
  ],

  onInitialized: (app) => {
    console.log(`VuePress app initialized at: ${app.options.base}`)
  },
})
