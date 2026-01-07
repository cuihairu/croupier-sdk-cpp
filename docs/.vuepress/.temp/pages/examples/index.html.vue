<template><div><h1 id="使用示例" tabindex="-1"><a class="header-anchor" href="#使用示例"><span>使用示例</span></a></h1>
<p>本章节提供 Croupier C++ SDK 的各种使用示例。</p>
<h2 id="示例列表" tabindex="-1"><a class="header-anchor" href="#示例列表"><span>示例列表</span></a></h2>
<ul>
<li><RouteLink to="/examples/basic-function.html">基础函数</RouteLink> - 最简单的函数注册示例</li>
<li><RouteLink to="/examples/virtual-object.html">虚拟对象</RouteLink> - 钱包虚拟对象完整示例</li>
<li><RouteLink to="/examples/plugin.html">插件</RouteLink> - 动态加载插件示例</li>
<li><RouteLink to="/examples/comprehensive.html">综合示例</RouteLink> - 完整的游戏服务端示例</li>
</ul>
<h2 id="运行示例" tabindex="-1"><a class="header-anchor" href="#运行示例"><span>运行示例</span></a></h2>
<h3 id="构建示例" tabindex="-1"><a class="header-anchor" href="#构建示例"><span>构建示例</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 克隆仓库</span></span>
<span class="line"><span class="token function">git</span> clone https://github.com/cuihairu/croupier-sdk-cpp.git</span>
<span class="line"><span class="token builtin class-name">cd</span> croupier-sdk-cpp</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 构建（包含示例）</span></span>
<span class="line">./scripts/build.sh <span class="token parameter variable">--examples</span> ON</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 或者使用 CMake</span></span>
<span class="line">cmake <span class="token parameter variable">-B</span> build <span class="token parameter variable">-DBUILD_EXAMPLES</span><span class="token operator">=</span>ON</span>
<span class="line">cmake <span class="token parameter variable">--build</span> build</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="运行示例-1" tabindex="-1"><a class="header-anchor" href="#运行示例-1"><span>运行示例</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 确保 Agent 已启动</span></span>
<span class="line">./build/bin/croupier-example</span>
<span class="line">./build/bin/croupier-virtual-object-demo</span>
<span class="line">./build/bin/croupier-plugin-demo</span>
<span class="line">./build/bin/croupier-comprehensive-demo</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="前置准备" tabindex="-1"><a class="header-anchor" href="#前置准备"><span>前置准备</span></a></h2>
<p>在运行示例前，需要：</p>
<ol>
<li><strong>启动 Croupier Server</strong></li>
</ol>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token builtin class-name">cd</span> /path/to/croupier/server</span>
<span class="line">go run ./services/server <span class="token parameter variable">-f</span> services/server/etc/server.yaml</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><ol start="2">
<li><strong>启动 Croupier Agent</strong></li>
</ol>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token builtin class-name">cd</span> /path/to/croupier/server</span>
<span class="line">go run ./services/agent <span class="token parameter variable">-f</span> services/agent/etc/agent.yaml</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><ol start="3">
<li><strong>验证连接</strong></li>
</ol>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># Agent 默认监听 127.0.0.1:19090</span></span>
<span class="line"><span class="token function">curl</span> http://127.0.0.1:19090/health</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="示例配置" tabindex="-1"><a class="header-anchor" href="#示例配置"><span>示例配置</span></a></h2>
<p>所有示例使用以下默认配置：</p>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"demo-game"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"env"</span><span class="token operator">:</span> <span class="token string">"development"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"service_id"</span><span class="token operator">:</span> <span class="token string">"demo-service"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"agent_addr"</span><span class="token operator">:</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"insecure"</span><span class="token operator">:</span> <span class="token boolean">true</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><p>可以通过环境变量覆盖：</p>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_GAME_ID</span><span class="token operator">=</span>my-game</span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_ENV</span><span class="token operator">=</span>production</span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_AGENT_ADDR</span><span class="token operator">=</span><span class="token number">10.0</span>.0.5:19090</span>
<span class="line"></span>
<span class="line">./build/bin/croupier-example</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="下一步" tabindex="-1"><a class="header-anchor" href="#下一步"><span>下一步</span></a></h2>
<p>查看具体示例了解详细用法：</p>
<ul>
<li><RouteLink to="/examples/basic-function.html">基础函数示例</RouteLink></li>
<li><RouteLink to="/examples/virtual-object.html">虚拟对象示例</RouteLink></li>
<li><RouteLink to="/examples/plugin.html">插件示例</RouteLink></li>
<li><RouteLink to="/examples/comprehensive.html">综合示例</RouteLink></li>
</ul>
</div></template>


