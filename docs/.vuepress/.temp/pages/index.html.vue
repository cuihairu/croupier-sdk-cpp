<template><div><h2 id="📋-简介" tabindex="-1"><a class="header-anchor" href="#📋-简介"><span>📋 简介</span></a></h2>
<p>Croupier C++ SDK 是 <a href="https://github.com/cuihairu/croupier" target="_blank" rel="noopener noreferrer">Croupier</a> 游戏后端平台的官方 C++ 客户端实现。它提供了高性能的虚拟对象注册、gRPC 通信和多平台构建支持。</p>
<h2 id="🚀-快速开始" tabindex="-1"><a class="header-anchor" href="#🚀-快速开始"><span>🚀 快速开始</span></a></h2>
<h3 id="安装依赖" tabindex="-1"><a class="header-anchor" href="#安装依赖"><span>安装依赖</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 克隆仓库</span></span>
<span class="line"><span class="token function">git</span> clone https://github.com/cuihairu/croupier-sdk-cpp.git</span>
<span class="line"><span class="token builtin class-name">cd</span> croupier-sdk-cpp</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 使用脚本构建（推荐）</span></span>
<span class="line">./scripts/build.sh</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="基础使用" tabindex="-1"><a class="header-anchor" href="#基础使用"><span>基础使用</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">"croupier/sdk/croupier_client.h"</span></span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">int</span> <span class="token function">main</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    croupier<span class="token double-colon punctuation">::</span>sdk<span class="token double-colon punctuation">::</span>ClientConfig config<span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"my-game"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    croupier<span class="token double-colon punctuation">::</span>sdk<span class="token double-colon punctuation">::</span>CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="🔗-相关链接" tabindex="-1"><a class="header-anchor" href="#🔗-相关链接"><span>🔗 相关链接</span></a></h2>
<ul>
<li><a href="https://github.com/cuihairu/croupier" target="_blank" rel="noopener noreferrer">主项目</a></li>
<li><a href="https://github.com/cuihairu/croupier-sdk-go" target="_blank" rel="noopener noreferrer">Go SDK</a></li>
<li><a href="https://github.com/cuihairu/croupier-sdk-java" target="_blank" rel="noopener noreferrer">Java SDK</a></li>
<li><a href="https://github.com/cuihairu/croupier-sdk-js" target="_blank" rel="noopener noreferrer">JavaScript SDK</a></li>
<li><a href="https://github.com/cuihairu/croupier-sdk-python" target="_blank" rel="noopener noreferrer">Python SDK</a></li>
</ul>
</div></template>


