<template><div><h1 id="部署指南" tabindex="-1"><a class="header-anchor" href="#部署指南"><span>部署指南</span></a></h1>
<p>本指南介绍如何部署使用 Croupier C++ SDK 的应用程序。</p>
<h2 id="部署模式" tabindex="-1"><a class="header-anchor" href="#部署模式"><span>部署模式</span></a></h2>
<h3 id="模式对比" tabindex="-1"><a class="header-anchor" href="#模式对比"><span>模式对比</span></a></h3>
<table>
<thead>
<tr>
<th>模式</th>
<th>复杂度</th>
<th>性能</th>
<th>适用场景</th>
</tr>
</thead>
<tbody>
<tr>
<td>独立进程</td>
<td>低</td>
<td>中</td>
<td>小规模游戏</td>
</tr>
<tr>
<td>容器化</td>
<td>中</td>
<td>高</td>
<td>微服务架构</td>
</tr>
<tr>
<td>多实例</td>
<td>高</td>
<td>最高</td>
<td>大规模游戏</td>
</tr>
</tbody>
</table>
<h2 id="独立进程部署" tabindex="-1"><a class="header-anchor" href="#独立进程部署"><span>独立进程部署</span></a></h2>
<h3 id="目录结构" tabindex="-1"><a class="header-anchor" href="#目录结构"><span>目录结构</span></a></h3>
<div class="language-text line-numbers-mode" data-highlighter="prismjs" data-ext="text"><pre v-pre><code class="language-text"><span class="line">/opt/game-server/</span>
<span class="line">├── bin/</span>
<span class="line">│   ├── game-server          # 主程序</span>
<span class="line">│   └── croupier-example     # 示例程序</span>
<span class="line">├── lib/</span>
<span class="line">│   └── libcroupier_sdk.so   # SDK 动态库</span>
<span class="line">├── configs/</span>
<span class="line">│   ├── development.json</span>
<span class="line">│   └── production.json</span>
<span class="line">└── scripts/</span>
<span class="line">    ├── start.sh</span>
<span class="line">    └── stop.sh</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="启动脚本" tabindex="-1"><a class="header-anchor" href="#启动脚本"><span>启动脚本</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token shebang important">#!/bin/bash</span></span>
<span class="line"><span class="token comment"># start.sh</span></span>
<span class="line"></span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">LD_LIBRARY_PATH</span><span class="token operator">=</span>/opt/game-server/lib:<span class="token variable">$LD_LIBRARY_PATH</span></span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_ENV</span><span class="token operator">=</span>production</span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_AGENT_ADDR</span><span class="token operator">=</span>croupier-agent.internal:19090</span>
<span class="line"></span>
<span class="line">/opt/game-server/bin/game-server</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="停止脚本" tabindex="-1"><a class="header-anchor" href="#停止脚本"><span>停止脚本</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token shebang important">#!/bin/bash</span></span>
<span class="line"><span class="token comment"># stop.sh</span></span>
<span class="line"></span>
<span class="line"><span class="token function">pkill</span> <span class="token parameter variable">-f</span> game-server</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="系统服务-systemd" tabindex="-1"><a class="header-anchor" href="#系统服务-systemd"><span>系统服务（systemd）</span></a></h3>
<div class="language-ini line-numbers-mode" data-highlighter="prismjs" data-ext="ini"><pre v-pre><code class="language-ini"><span class="line"><span class="token section"><span class="token punctuation">[</span><span class="token section-name selector">Unit</span><span class="token punctuation">]</span></span></span>
<span class="line"><span class="token key attr-name">Description</span><span class="token punctuation">=</span><span class="token value attr-value">Game Server with Croupier SDK</span></span>
<span class="line"><span class="token key attr-name">After</span><span class="token punctuation">=</span><span class="token value attr-value">network.target</span></span>
<span class="line"></span>
<span class="line"><span class="token section"><span class="token punctuation">[</span><span class="token section-name selector">Service</span><span class="token punctuation">]</span></span></span>
<span class="line"><span class="token key attr-name">Type</span><span class="token punctuation">=</span><span class="token value attr-value">simple</span></span>
<span class="line"><span class="token key attr-name">User</span><span class="token punctuation">=</span><span class="token value attr-value">gameserver</span></span>
<span class="line"><span class="token key attr-name">WorkingDirectory</span><span class="token punctuation">=</span><span class="token value attr-value">/opt/game-server</span></span>
<span class="line"><span class="token key attr-name">Environment</span><span class="token punctuation">=</span><span class="token value attr-value">"<span class="token inner-value">LD_LIBRARY_PATH=/opt/game-server/lib</span>"</span></span>
<span class="line"><span class="token key attr-name">Environment</span><span class="token punctuation">=</span><span class="token value attr-value">"<span class="token inner-value">CROUPIER_ENV=production</span>"</span></span>
<span class="line"><span class="token key attr-name">Environment</span><span class="token punctuation">=</span><span class="token value attr-value">"<span class="token inner-value">CROUPIER_AGENT_ADDR=croupier-agent.internal:19090</span>"</span></span>
<span class="line"><span class="token key attr-name">ExecStart</span><span class="token punctuation">=</span><span class="token value attr-value">/opt/game-server/bin/game-server</span></span>
<span class="line"><span class="token key attr-name">Restart</span><span class="token punctuation">=</span><span class="token value attr-value">always</span></span>
<span class="line"><span class="token key attr-name">RestartSec</span><span class="token punctuation">=</span><span class="token value attr-value">5</span></span>
<span class="line"></span>
<span class="line"><span class="token section"><span class="token punctuation">[</span><span class="token section-name selector">Install</span><span class="token punctuation">]</span></span></span>
<span class="line"><span class="token key attr-name">WantedBy</span><span class="token punctuation">=</span><span class="token value attr-value">multi-user.target</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><p>安装服务：</p>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token function">sudo</span> <span class="token function">cp</span> game-server.service /etc/systemd/system/</span>
<span class="line"><span class="token function">sudo</span> systemctl daemon-reload</span>
<span class="line"><span class="token function">sudo</span> systemctl <span class="token builtin class-name">enable</span> game-server</span>
<span class="line"><span class="token function">sudo</span> systemctl start game-server</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="容器化部署" tabindex="-1"><a class="header-anchor" href="#容器化部署"><span>容器化部署</span></a></h2>
<h3 id="dockerfile" tabindex="-1"><a class="header-anchor" href="#dockerfile"><span>Dockerfile</span></a></h3>
<div class="language-docker line-numbers-mode" data-highlighter="prismjs" data-ext="docker"><pre v-pre><code class="language-docker"><span class="line"><span class="token instruction"><span class="token keyword">FROM</span> ubuntu:22.04 <span class="token keyword">AS</span> base</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 安装运行时依赖</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">RUN</span> apt-get update &amp;&amp; apt-get install -y <span class="token operator">\</span></span>
<span class="line">    libgrpc++1.54 <span class="token operator">\</span></span>
<span class="line">    libprotobuf32 <span class="token operator">\</span></span>
<span class="line">    ca-certificates <span class="token operator">\</span></span>
<span class="line">    &amp;&amp; rm -rf /var/lib/apt/lists/*</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 构建阶段</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">FROM</span> base <span class="token keyword">AS</span> builder</span></span>
<span class="line"></span>
<span class="line"><span class="token instruction"><span class="token keyword">RUN</span> apt-get update &amp;&amp; apt-get install -y <span class="token operator">\</span></span>
<span class="line">    cmake <span class="token operator">\</span></span>
<span class="line">    g++ <span class="token operator">\</span></span>
<span class="line">    git <span class="token operator">\</span></span>
<span class="line">    pkg-config <span class="token operator">\</span></span>
<span class="line">    &amp;&amp; rm -rf /var/lib/apt/lists/*</span></span>
<span class="line"></span>
<span class="line"><span class="token instruction"><span class="token keyword">WORKDIR</span> /build</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">COPY</span> . .</span></span>
<span class="line"></span>
<span class="line"><span class="token instruction"><span class="token keyword">RUN</span> cmake -B build <span class="token operator">\</span></span>
<span class="line">    -DCMAKE_BUILD_TYPE=Release <span class="token operator">\</span></span>
<span class="line">    -DBUILD_EXAMPLES=OFF <span class="token operator">\</span></span>
<span class="line">    -DBUILD_TESTING=OFF</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">RUN</span> cmake --build build --parallel</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">RUN</span> cmake --install build --prefix /usr/local</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 运行阶段</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">FROM</span> base</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 复制构建产物</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">COPY</span> <span class="token options"><span class="token property">--from</span><span class="token punctuation">=</span><span class="token string">builder</span></span> /usr/local/lib /usr/local/lib</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">COPY</span> <span class="token options"><span class="token property">--from</span><span class="token punctuation">=</span><span class="token string">builder</span></span> /usr/local/bin /usr/local/bin</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 复制配置</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">COPY</span> configs/ /etc/croupier/</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">COPY</span> bin/game-server /app/</span></span>
<span class="line"></span>
<span class="line"><span class="token instruction"><span class="token keyword">ENV</span> LD_LIBRARY_PATH=/usr/local/lib</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">ENV</span> CROUPIER_ENV=production</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">ENV</span> CROUPIER_AGENT_ADDR=croupier-agent:19090</span></span>
<span class="line"></span>
<span class="line"><span class="token instruction"><span class="token keyword">WORKDIR</span> /app</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">EXPOSE</span> 8080</span></span>
<span class="line"></span>
<span class="line"><span class="token instruction"><span class="token keyword">CMD</span> [<span class="token string">"game-server"</span>]</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="构建镜像" tabindex="-1"><a class="header-anchor" href="#构建镜像"><span>构建镜像</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token function">docker</span> build <span class="token parameter variable">-t</span> game-server:latest <span class="token builtin class-name">.</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><h3 id="docker-compose" tabindex="-1"><a class="header-anchor" href="#docker-compose"><span>Docker Compose</span></a></h3>
<div class="language-yaml line-numbers-mode" data-highlighter="prismjs" data-ext="yml"><pre v-pre><code class="language-yaml"><span class="line"><span class="token key atrule">version</span><span class="token punctuation">:</span> <span class="token string">'3.8'</span></span>
<span class="line"></span>
<span class="line"><span class="token key atrule">services</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">croupier-agent</span><span class="token punctuation">:</span></span>
<span class="line">    <span class="token key atrule">image</span><span class="token punctuation">:</span> croupier/agent<span class="token punctuation">:</span>latest</span>
<span class="line">    <span class="token key atrule">ports</span><span class="token punctuation">:</span></span>
<span class="line">      <span class="token punctuation">-</span> <span class="token string">"19090:19090"</span></span>
<span class="line">    <span class="token key atrule">environment</span><span class="token punctuation">:</span></span>
<span class="line">      <span class="token punctuation">-</span> CROUPIER_SERVER_ADDR=croupier<span class="token punctuation">-</span>server<span class="token punctuation">:</span><span class="token number">8443</span></span>
<span class="line"></span>
<span class="line">  <span class="token key atrule">game-server</span><span class="token punctuation">:</span></span>
<span class="line">    <span class="token key atrule">build</span><span class="token punctuation">:</span> .</span>
<span class="line">    <span class="token key atrule">depends_on</span><span class="token punctuation">:</span></span>
<span class="line">      <span class="token punctuation">-</span> croupier<span class="token punctuation">-</span>agent</span>
<span class="line">    <span class="token key atrule">environment</span><span class="token punctuation">:</span></span>
<span class="line">      <span class="token punctuation">-</span> CROUPIER_ENV=production</span>
<span class="line">      <span class="token punctuation">-</span> CROUPIER_AGENT_ADDR=croupier<span class="token punctuation">-</span>agent<span class="token punctuation">:</span><span class="token number">19090</span></span>
<span class="line">      <span class="token punctuation">-</span> CROUPIER_GAME_ID=production<span class="token punctuation">-</span>game</span>
<span class="line">    <span class="token key atrule">restart</span><span class="token punctuation">:</span> unless<span class="token punctuation">-</span>stopped</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><p>运行：</p>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token function">docker-compose</span> up <span class="token parameter variable">-d</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><h2 id="kubernetes-部署" tabindex="-1"><a class="header-anchor" href="#kubernetes-部署"><span>Kubernetes 部署</span></a></h2>
<h3 id="deployment" tabindex="-1"><a class="header-anchor" href="#deployment"><span>Deployment</span></a></h3>
<div class="language-yaml line-numbers-mode" data-highlighter="prismjs" data-ext="yml"><pre v-pre><code class="language-yaml"><span class="line"><span class="token key atrule">apiVersion</span><span class="token punctuation">:</span> apps/v1</span>
<span class="line"><span class="token key atrule">kind</span><span class="token punctuation">:</span> Deployment</span>
<span class="line"><span class="token key atrule">metadata</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">name</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>server</span>
<span class="line">  <span class="token key atrule">namespace</span><span class="token punctuation">:</span> game</span>
<span class="line"><span class="token key atrule">spec</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">replicas</span><span class="token punctuation">:</span> <span class="token number">3</span></span>
<span class="line">  <span class="token key atrule">selector</span><span class="token punctuation">:</span></span>
<span class="line">    <span class="token key atrule">matchLabels</span><span class="token punctuation">:</span></span>
<span class="line">      <span class="token key atrule">app</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>server</span>
<span class="line">  <span class="token key atrule">template</span><span class="token punctuation">:</span></span>
<span class="line">    <span class="token key atrule">metadata</span><span class="token punctuation">:</span></span>
<span class="line">      <span class="token key atrule">labels</span><span class="token punctuation">:</span></span>
<span class="line">        <span class="token key atrule">app</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>server</span>
<span class="line">    <span class="token key atrule">spec</span><span class="token punctuation">:</span></span>
<span class="line">      <span class="token key atrule">containers</span><span class="token punctuation">:</span></span>
<span class="line">      <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>server</span>
<span class="line">        <span class="token key atrule">image</span><span class="token punctuation">:</span> your<span class="token punctuation">-</span>registry/game<span class="token punctuation">-</span>server<span class="token punctuation">:</span>v1.0.0</span>
<span class="line">        <span class="token key atrule">ports</span><span class="token punctuation">:</span></span>
<span class="line">        <span class="token punctuation">-</span> <span class="token key atrule">containerPort</span><span class="token punctuation">:</span> <span class="token number">8080</span></span>
<span class="line">        <span class="token key atrule">env</span><span class="token punctuation">:</span></span>
<span class="line">        <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> CROUPIER_ENV</span>
<span class="line">          <span class="token key atrule">value</span><span class="token punctuation">:</span> <span class="token string">"production"</span></span>
<span class="line">        <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> CROUPIER_AGENT_ADDR</span>
<span class="line">          <span class="token key atrule">value</span><span class="token punctuation">:</span> <span class="token string">"croupier-agent.game.svc.cluster.local:19090"</span></span>
<span class="line">        <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> CROUPIER_GAME_ID</span>
<span class="line">          <span class="token key atrule">valueFrom</span><span class="token punctuation">:</span></span>
<span class="line">            <span class="token key atrule">configMapKeyRef</span><span class="token punctuation">:</span></span>
<span class="line">              <span class="token key atrule">name</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>config</span>
<span class="line">              <span class="token key atrule">key</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>id</span>
<span class="line">        <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> CROUPIER_AUTH_TOKEN</span>
<span class="line">          <span class="token key atrule">valueFrom</span><span class="token punctuation">:</span></span>
<span class="line">            <span class="token key atrule">secretKeyRef</span><span class="token punctuation">:</span></span>
<span class="line">              <span class="token key atrule">name</span><span class="token punctuation">:</span> croupier<span class="token punctuation">-</span>auth</span>
<span class="line">              <span class="token key atrule">key</span><span class="token punctuation">:</span> jwt<span class="token punctuation">-</span>token</span>
<span class="line">        <span class="token key atrule">resources</span><span class="token punctuation">:</span></span>
<span class="line">          <span class="token key atrule">requests</span><span class="token punctuation">:</span></span>
<span class="line">            <span class="token key atrule">memory</span><span class="token punctuation">:</span> <span class="token string">"256Mi"</span></span>
<span class="line">            <span class="token key atrule">cpu</span><span class="token punctuation">:</span> <span class="token string">"500m"</span></span>
<span class="line">          <span class="token key atrule">limits</span><span class="token punctuation">:</span></span>
<span class="line">            <span class="token key atrule">memory</span><span class="token punctuation">:</span> <span class="token string">"512Mi"</span></span>
<span class="line">            <span class="token key atrule">cpu</span><span class="token punctuation">:</span> <span class="token string">"1000m"</span></span>
<span class="line">        <span class="token key atrule">livenessProbe</span><span class="token punctuation">:</span></span>
<span class="line">          <span class="token key atrule">httpGet</span><span class="token punctuation">:</span></span>
<span class="line">            <span class="token key atrule">path</span><span class="token punctuation">:</span> /health</span>
<span class="line">            <span class="token key atrule">port</span><span class="token punctuation">:</span> <span class="token number">8080</span></span>
<span class="line">          <span class="token key atrule">initialDelaySeconds</span><span class="token punctuation">:</span> <span class="token number">30</span></span>
<span class="line">          <span class="token key atrule">periodSeconds</span><span class="token punctuation">:</span> <span class="token number">10</span></span>
<span class="line">        <span class="token key atrule">readinessProbe</span><span class="token punctuation">:</span></span>
<span class="line">          <span class="token key atrule">httpGet</span><span class="token punctuation">:</span></span>
<span class="line">            <span class="token key atrule">path</span><span class="token punctuation">:</span> /ready</span>
<span class="line">            <span class="token key atrule">port</span><span class="token punctuation">:</span> <span class="token number">8080</span></span>
<span class="line">          <span class="token key atrule">initialDelaySeconds</span><span class="token punctuation">:</span> <span class="token number">5</span></span>
<span class="line">          <span class="token key atrule">periodSeconds</span><span class="token punctuation">:</span> <span class="token number">5</span></span>
<span class="line"><span class="token punctuation">---</span></span>
<span class="line"><span class="token key atrule">apiVersion</span><span class="token punctuation">:</span> v1</span>
<span class="line"><span class="token key atrule">kind</span><span class="token punctuation">:</span> Service</span>
<span class="line"><span class="token key atrule">metadata</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">name</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>server</span>
<span class="line">  <span class="token key atrule">namespace</span><span class="token punctuation">:</span> game</span>
<span class="line"><span class="token key atrule">spec</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">selector</span><span class="token punctuation">:</span></span>
<span class="line">    <span class="token key atrule">app</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>server</span>
<span class="line">  <span class="token key atrule">ports</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token punctuation">-</span> <span class="token key atrule">port</span><span class="token punctuation">:</span> <span class="token number">80</span></span>
<span class="line">    <span class="token key atrule">targetPort</span><span class="token punctuation">:</span> <span class="token number">8080</span></span>
<span class="line">  <span class="token key atrule">type</span><span class="token punctuation">:</span> ClusterIP</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="configmap" tabindex="-1"><a class="header-anchor" href="#configmap"><span>ConfigMap</span></a></h3>
<div class="language-yaml line-numbers-mode" data-highlighter="prismjs" data-ext="yml"><pre v-pre><code class="language-yaml"><span class="line"><span class="token key atrule">apiVersion</span><span class="token punctuation">:</span> v1</span>
<span class="line"><span class="token key atrule">kind</span><span class="token punctuation">:</span> ConfigMap</span>
<span class="line"><span class="token key atrule">metadata</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">name</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>config</span>
<span class="line">  <span class="token key atrule">namespace</span><span class="token punctuation">:</span> game</span>
<span class="line"><span class="token key atrule">data</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">game-id</span><span class="token punctuation">:</span> <span class="token string">"production-game"</span></span>
<span class="line">  <span class="token key atrule">env</span><span class="token punctuation">:</span> <span class="token string">"production"</span></span>
<span class="line">  <span class="token key atrule">log-level</span><span class="token punctuation">:</span> <span class="token string">"info"</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="secret" tabindex="-1"><a class="header-anchor" href="#secret"><span>Secret</span></a></h3>
<div class="language-yaml line-numbers-mode" data-highlighter="prismjs" data-ext="yml"><pre v-pre><code class="language-yaml"><span class="line"><span class="token key atrule">apiVersion</span><span class="token punctuation">:</span> v1</span>
<span class="line"><span class="token key atrule">kind</span><span class="token punctuation">:</span> Secret</span>
<span class="line"><span class="token key atrule">metadata</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">name</span><span class="token punctuation">:</span> croupier<span class="token punctuation">-</span>auth</span>
<span class="line">  <span class="token key atrule">namespace</span><span class="token punctuation">:</span> game</span>
<span class="line"><span class="token key atrule">type</span><span class="token punctuation">:</span> Opaque</span>
<span class="line"><span class="token key atrule">data</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">jwt-token</span><span class="token punctuation">:</span> &lt;base64<span class="token punctuation">-</span>encoded<span class="token punctuation">-</span>token<span class="token punctuation">></span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="负载均衡" tabindex="-1"><a class="header-anchor" href="#负载均衡"><span>负载均衡</span></a></h2>
<h3 id="nginx-配置" tabindex="-1"><a class="header-anchor" href="#nginx-配置"><span>Nginx 配置</span></a></h3>
<div class="language-nginx line-numbers-mode" data-highlighter="prismjs" data-ext="nginx"><pre v-pre><code class="language-nginx"><span class="line"><span class="token directive"><span class="token keyword">upstream</span> game_servers</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token directive"><span class="token keyword">least_conn</span></span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token directive"><span class="token keyword">server</span> game-server-1:8080</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token directive"><span class="token keyword">server</span> game-server-2:8080</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token directive"><span class="token keyword">server</span> game-server-3:8080</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token directive"><span class="token keyword">server</span></span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token directive"><span class="token keyword">listen</span> <span class="token number">80</span></span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token directive"><span class="token keyword">server_name</span> game.example.com</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token directive"><span class="token keyword">location</span> /</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token directive"><span class="token keyword">proxy_pass</span> http://game_servers</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token directive"><span class="token keyword">proxy_set_header</span> Host <span class="token variable">$host</span></span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token directive"><span class="token keyword">proxy_set_header</span> X-Real-IP <span class="token variable">$remote_addr</span></span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token directive"><span class="token keyword">proxy_set_header</span> X-Forwarded-For <span class="token variable">$proxy_add_x_forwarded_for</span></span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token directive"><span class="token keyword">proxy_set_header</span> X-Game-ID <span class="token variable">$http_x_game_id</span></span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="监控和日志" tabindex="-1"><a class="header-anchor" href="#监控和日志"><span>监控和日志</span></a></h2>
<h3 id="健康检查端点" tabindex="-1"><a class="header-anchor" href="#健康检查端点"><span>健康检查端点</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">&lt;cpprest/http_listener.h></span></span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">class</span> <span class="token class-name">HealthCheckServer</span> <span class="token punctuation">{</span></span>
<span class="line"><span class="token keyword">public</span><span class="token operator">:</span></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">Start</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        http_listener <span class="token function">listener</span><span class="token punctuation">(</span><span class="token string">"http://0.0.0.0:8080/health"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        listener<span class="token punctuation">.</span><span class="token function">support</span><span class="token punctuation">(</span><span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span>http_request request<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">            <span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token function">IsHealthy</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">                request<span class="token punctuation">.</span><span class="token function">reply</span><span class="token punctuation">(</span>status_codes<span class="token double-colon punctuation">::</span>OK<span class="token punctuation">,</span> <span class="token raw-string string">R"({"status": "healthy"})"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">            <span class="token punctuation">}</span> <span class="token keyword">else</span> <span class="token punctuation">{</span></span>
<span class="line">                request<span class="token punctuation">.</span><span class="token function">reply</span><span class="token punctuation">(</span>status_codes<span class="token double-colon punctuation">::</span>ServiceUnavailable<span class="token punctuation">,</span> <span class="token raw-string string">R"({"status": "unhealthy"})"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">            <span class="token punctuation">}</span></span>
<span class="line">        <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        listener<span class="token punctuation">.</span><span class="token function">open</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">.</span><span class="token function">wait</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">private</span><span class="token operator">:</span></span>
<span class="line">    <span class="token keyword">bool</span> <span class="token function">IsHealthy</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token comment">// 检查 Croupier 连接状态</span></span>
<span class="line">        <span class="token keyword">return</span> client_<span class="token punctuation">.</span><span class="token function">IsConnected</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    CroupierClient<span class="token operator">&amp;</span> client_<span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="日志配置" tabindex="-1"><a class="header-anchor" href="#日志配置"><span>日志配置</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">&lt;spdlog/spdlog.h></span></span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">void</span> <span class="token function">SetupLogging</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 根据环境设置日志级别</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string env <span class="token operator">=</span> std<span class="token double-colon punctuation">::</span><span class="token function">getenv</span><span class="token punctuation">(</span><span class="token string">"CROUPIER_ENV"</span><span class="token punctuation">)</span> <span class="token operator">?</span><span class="token operator">:</span> <span class="token string">"development"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">if</span> <span class="token punctuation">(</span>env <span class="token operator">==</span> <span class="token string">"production"</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        spdlog<span class="token double-colon punctuation">::</span><span class="token function">set_level</span><span class="token punctuation">(</span>spdlog<span class="token double-colon punctuation">::</span>level<span class="token double-colon punctuation">::</span>info<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span> <span class="token keyword">else</span> <span class="token punctuation">{</span></span>
<span class="line">        spdlog<span class="token double-colon punctuation">::</span><span class="token function">set_level</span><span class="token punctuation">(</span>spdlog<span class="token double-colon punctuation">::</span>level<span class="token double-colon punctuation">::</span>debug<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 输出到文件</span></span>
<span class="line">    <span class="token keyword">auto</span> logger <span class="token operator">=</span> spdlog<span class="token double-colon punctuation">::</span><span class="token function">basic_logger_mt</span><span class="token punctuation">(</span><span class="token string">"file_logger"</span><span class="token punctuation">,</span> <span class="token string">"/var/log/game-server.log"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    spdlog<span class="token double-colon punctuation">::</span><span class="token function">set_default_logger</span><span class="token punctuation">(</span>logger<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="安全加固" tabindex="-1"><a class="header-anchor" href="#安全加固"><span>安全加固</span></a></h2>
<h3 id="tls-配置" tabindex="-1"><a class="header-anchor" href="#tls-配置"><span>TLS 配置</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"secure-game"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"env"</span><span class="token operator">:</span> <span class="token string">"production"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"agent_addr"</span><span class="token operator">:</span> <span class="token string">"croupier-agent:19090"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"insecure"</span><span class="token operator">:</span> <span class="token boolean">false</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"security"</span><span class="token operator">:</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token property">"cert_file"</span><span class="token operator">:</span> <span class="token string">"/etc/tls/client.crt"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token property">"key_file"</span><span class="token operator">:</span> <span class="token string">"/etc/tls/client.key"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token property">"ca_file"</span><span class="token operator">:</span> <span class="token string">"/etc/tls/ca.crt"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token property">"server_name"</span><span class="token operator">:</span> <span class="token string">"croupier.internal"</span></span>
<span class="line">  <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="secret-管理" tabindex="-1"><a class="header-anchor" href="#secret-管理"><span>Secret 管理</span></a></h3>
<p>使用 Kubernetes Secrets 或 Vault 管理敏感信息：</p>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 创建 Secret</span></span>
<span class="line">kubectl create secret generic croupier-secrets <span class="token punctuation">\</span></span>
<span class="line">  --from-literal<span class="token operator">=</span>jwt-token<span class="token operator">=</span><span class="token string">'your-jwt-token'</span> <span class="token punctuation">\</span></span>
<span class="line">  --from-literal<span class="token operator">=</span>api-key<span class="token operator">=</span><span class="token string">'your-api-key'</span> <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-n</span> game</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="高可用配置" tabindex="-1"><a class="header-anchor" href="#高可用配置"><span>高可用配置</span></a></h2>
<h3 id="多区域部署" tabindex="-1"><a class="header-anchor" href="#多区域部署"><span>多区域部署</span></a></h3>
<div class="language-yaml line-numbers-mode" data-highlighter="prismjs" data-ext="yml"><pre v-pre><code class="language-yaml"><span class="line"><span class="token comment"># 不同区域的 Agent 配置</span></span>
<span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token key atrule">"agent_addrs"</span><span class="token punctuation">:</span> <span class="token punctuation">[</span></span>
<span class="line">    <span class="token string">"croupier-agent-us-east:19090"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token string">"croupier-agent-us-west:19090"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token string">"croupier-agent-eu-west:19090"</span></span>
<span class="line">  <span class="token punctuation">]</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token key atrule">"reconnect_max_attempts"</span><span class="token punctuation">:</span> <span class="token number">0</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token key atrule">"reconnect_interval_seconds"</span><span class="token punctuation">:</span> <span class="token number">5</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="故障转移" tabindex="-1"><a class="header-anchor" href="#故障转移"><span>故障转移</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">class</span> <span class="token class-name">FailoverClient</span> <span class="token operator">:</span> <span class="token base-clause"><span class="token keyword">public</span> <span class="token class-name">CroupierClient</span></span> <span class="token punctuation">{</span></span>
<span class="line"><span class="token keyword">public</span><span class="token operator">:</span></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">ConnectWithFailover</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>vector<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token operator">></span><span class="token operator">&amp;</span> agents<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">for</span> <span class="token punctuation">(</span><span class="token keyword">const</span> <span class="token keyword">auto</span><span class="token operator">&amp;</span> agent <span class="token operator">:</span> agents<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">            config_<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> agent<span class="token punctuation">;</span></span>
<span class="line">            <span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">                <span class="token function">SPDLOG_INFO</span><span class="token punctuation">(</span><span class="token string">"Connected to {}"</span><span class="token punctuation">,</span> agent<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">                <span class="token keyword">return</span><span class="token punctuation">;</span></span>
<span class="line">            <span class="token punctuation">}</span></span>
<span class="line">            <span class="token function">SPDLOG_WARN</span><span class="token punctuation">(</span><span class="token string">"Failed to connect to {}, trying next..."</span><span class="token punctuation">,</span> agent<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token punctuation">}</span></span>
<span class="line">        <span class="token keyword">throw</span> std<span class="token double-colon punctuation">::</span><span class="token function">runtime_error</span><span class="token punctuation">(</span><span class="token string">"All agents failed"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div></div></template>


