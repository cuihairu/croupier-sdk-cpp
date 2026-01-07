<template><div><h1 id="入门指南" tabindex="-1"><a class="header-anchor" href="#入门指南"><span>入门指南</span></a></h1>
<p>欢迎来到 Croupier C++ SDK！本指南将帮助你快速上手并掌握 SDK 的核心功能。</p>
<h2 id="系统要求" tabindex="-1"><a class="header-anchor" href="#系统要求"><span>系统要求</span></a></h2>
<h3 id="必需组件" tabindex="-1"><a class="header-anchor" href="#必需组件"><span>必需组件</span></a></h3>
<ul>
<li><strong>C++17</strong> 编译器
<ul>
<li>GCC 8+</li>
<li>Clang 10+</li>
<li>MSVC 2019+</li>
</ul>
</li>
<li><strong>CMake 3.20+</strong></li>
<li><strong>vcpkg</strong>（推荐，用于依赖管理）</li>
</ul>
<h3 id="支持的平台" tabindex="-1"><a class="header-anchor" href="#支持的平台"><span>支持的平台</span></a></h3>
<table>
<thead>
<tr>
<th>平台</th>
<th>架构</th>
<th>状态</th>
</tr>
</thead>
<tbody>
<tr>
<td>Windows</td>
<td>x64</td>
<td>✅ 支持</td>
</tr>
<tr>
<td>Linux</td>
<td>x64, ARM64</td>
<td>✅ 支持</td>
</tr>
<tr>
<td>macOS</td>
<td>x64, ARM64 (Apple Silicon)</td>
<td>✅ 支持</td>
</tr>
</tbody>
</table>
<h2 id="目录结构" tabindex="-1"><a class="header-anchor" href="#目录结构"><span>目录结构</span></a></h2>
<div class="language-text line-numbers-mode" data-highlighter="prismjs" data-ext="text"><pre v-pre><code class="language-text"><span class="line">croupier-sdk-cpp/</span>
<span class="line">├── include/           # 公共头文件</span>
<span class="line">├── src/               # 源代码</span>
<span class="line">├── examples/          # 示例程序</span>
<span class="line">├── scripts/           # 构建脚本</span>
<span class="line">├── cmake/             # CMake 模块</span>
<span class="line">├── configs/           # 配置文件示例</span>
<span class="line">└── vcpkg.json         # vcpkg 依赖清单</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="下一步" tabindex="-1"><a class="header-anchor" href="#下一步"><span>下一步</span></a></h2>
<ul>
<li><RouteLink to="/guide/installation.html">安装指南</RouteLink> - 详细安装步骤</li>
<li><RouteLink to="/guide/quick-start.html">快速开始</RouteLink> - 第一个示例程序</li>
<li><RouteLink to="/guide/building.html">构建指南</RouteLink> - 高级构建选项</li>
</ul>
</div></template>


