<template><div><h1 id="客户端配置详解" tabindex="-1"><a class="header-anchor" href="#客户端配置详解"><span>客户端配置详解</span></a></h1>
<p><code v-pre>ClientConfig</code> 结构定义了 Croupier 客户端的所有配置选项。</p>
<h2 id="完整结构" tabindex="-1"><a class="header-anchor" href="#完整结构"><span>完整结构</span></a></h2>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">struct</span> <span class="token class-name">ClientConfig</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 连接配置</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string game_id<span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string service_id <span class="token operator">=</span> <span class="token string">"cpp-service"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 超时</span></span>
<span class="line">    <span class="token keyword">int</span> timeout_seconds <span class="token operator">=</span> <span class="token number">30</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// TLS</span></span>
<span class="line">    <span class="token keyword">bool</span> insecure <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">struct</span> <span class="token class-name">Security</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string cert_file<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string key_file<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string ca_file<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string server_name<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span> security<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 重连</span></span>
<span class="line">    <span class="token keyword">bool</span> auto_reconnect <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> reconnect_interval_seconds <span class="token operator">=</span> <span class="token number">5</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> reconnect_max_attempts <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 认证</span></span>
<span class="line">    <span class="token keyword">struct</span> <span class="token class-name">Auth</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string token<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>map<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">></span> headers<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span> auth<span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="字段详解" tabindex="-1"><a class="header-anchor" href="#字段详解"><span>字段详解</span></a></h2>
<h3 id="agent-addr" tabindex="-1"><a class="header-anchor" href="#agent-addr"><span>agent_addr</span></a></h3>
<p>Agent 服务器地址，格式 <code v-pre>host:port</code>。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span>      <span class="token comment">// 本地</span></span>
<span class="line">config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"agent.internal:19090"</span><span class="token punctuation">;</span>  <span class="token comment">// 内部域名</span></span>
<span class="line">config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"10.0.0.5:19090"</span><span class="token punctuation">;</span>         <span class="token comment">// IP 地址</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="game-id" tabindex="-1"><a class="header-anchor" href="#game-id"><span>game_id</span></a></h3>
<p>游戏/项目唯一标识符。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"my-mmorpg"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"production-game-2024"</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="env" tabindex="-1"><a class="header-anchor" href="#env"><span>env</span></a></h3>
<p>部署环境标识。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">;</span>  <span class="token comment">// 开发</span></span>
<span class="line">config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"staging"</span><span class="token punctuation">;</span>      <span class="token comment">// 预发布</span></span>
<span class="line">config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"production"</span><span class="token punctuation">;</span>   <span class="token comment">// 生产</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="service-id" tabindex="-1"><a class="header-anchor" href="#service-id"><span>service_id</span></a></h3>
<p>服务实例标识符。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>service_id <span class="token operator">=</span> <span class="token string">"game-server-01"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>service_id <span class="token operator">=</span> <span class="token string">"backend-"</span> <span class="token operator">+</span> <span class="token function">GetHostname</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="timeout-seconds" tabindex="-1"><a class="header-anchor" href="#timeout-seconds"><span>timeout_seconds</span></a></h3>
<p>网络操作超时时间（秒）。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>timeout_seconds <span class="token operator">=</span> <span class="token number">30</span><span class="token punctuation">;</span>   <span class="token comment">// 默认</span></span>
<span class="line">config<span class="token punctuation">.</span>timeout_seconds <span class="token operator">=</span> <span class="token number">60</span><span class="token punctuation">;</span>   <span class="token comment">// 长操作</span></span>
<span class="line">config<span class="token punctuation">.</span>timeout_seconds <span class="token operator">=</span> <span class="token number">300</span><span class="token punctuation">;</span>  <span class="token comment">// 非常长的操作</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="insecure" tabindex="-1"><a class="header-anchor" href="#insecure"><span>insecure</span></a></h3>
<p>是否跳过 TLS 验证。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>insecure <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span>   <span class="token comment">// 开发环境</span></span>
<span class="line">config<span class="token punctuation">.</span>insecure <span class="token operator">=</span> <span class="token boolean">false</span><span class="token punctuation">;</span>  <span class="token comment">// 生产环境（必须）</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="security-结构体" tabindex="-1"><a class="header-anchor" href="#security-结构体"><span>security (结构体)</span></a></h3>
<p>TLS 安全配置。</p>
<table>
<thead>
<tr>
<th>字段</th>
<th>说明</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>cert_file</code></td>
<td>客户端证书路径</td>
</tr>
<tr>
<td><code v-pre>key_file</code></td>
<td>客户端私钥路径</td>
</tr>
<tr>
<td><code v-pre>ca_file</code></td>
<td>CA 证书路径</td>
</tr>
<tr>
<td><code v-pre>server_name</code></td>
<td>TLS 服务器名称（SNI）</td>
</tr>
</tbody>
</table>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>cert_file <span class="token operator">=</span> <span class="token string">"/etc/tls/client.crt"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>key_file <span class="token operator">=</span> <span class="token string">"/etc/tls/client.key"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>ca_file <span class="token operator">=</span> <span class="token string">"/etc/tls/ca.crt"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>server_name <span class="token operator">=</span> <span class="token string">"croupier.internal"</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="auto-reconnect" tabindex="-1"><a class="header-anchor" href="#auto-reconnect"><span>auto_reconnect</span></a></h3>
<p>是否自动重连。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>auto_reconnect <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span>   <span class="token comment">// 断线自动重连</span></span>
<span class="line">config<span class="token punctuation">.</span>auto_reconnect <span class="token operator">=</span> <span class="token boolean">false</span><span class="token punctuation">;</span>  <span class="token comment">// 断线退出</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="reconnect-interval-seconds" tabindex="-1"><a class="header-anchor" href="#reconnect-interval-seconds"><span>reconnect_interval_seconds</span></a></h3>
<p>重连间隔（秒）。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>reconnect_interval_seconds <span class="token operator">=</span> <span class="token number">5</span><span class="token punctuation">;</span>   <span class="token comment">// 每 5 秒</span></span>
<span class="line">config<span class="token punctuation">.</span>reconnect_interval_seconds <span class="token operator">=</span> <span class="token number">30</span><span class="token punctuation">;</span>  <span class="token comment">// 每 30 秒</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="reconnect-max-attempts" tabindex="-1"><a class="header-anchor" href="#reconnect-max-attempts"><span>reconnect_max_attempts</span></a></h3>
<p>最大重连次数（0 = 无限）。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>reconnect_max_attempts <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>    <span class="token comment">// 无限重试</span></span>
<span class="line">config<span class="token punctuation">.</span>reconnect_max_attempts <span class="token operator">=</span> <span class="token number">10</span><span class="token punctuation">;</span>   <span class="token comment">// 最多 10 次</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="auth-结构体" tabindex="-1"><a class="header-anchor" href="#auth-结构体"><span>auth (结构体)</span></a></h3>
<p>认证配置。</p>
<table>
<thead>
<tr>
<th>字段</th>
<th>说明</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>token</code></td>
<td>JWT 令牌</td>
</tr>
<tr>
<td><code v-pre>headers</code></td>
<td>额外 HTTP 头部</td>
</tr>
</tbody>
</table>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>auth<span class="token punctuation">.</span>token <span class="token operator">=</span> <span class="token string">"Bearer eyJhbGciOiJIUzI1NiIs..."</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>auth<span class="token punctuation">.</span>headers <span class="token operator">=</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"X-Game-Version"</span><span class="token punctuation">,</span> <span class="token string">"0.1.0"</span><span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"X-Service-Region"</span><span class="token punctuation">,</span> <span class="token string">"us-west-2"</span><span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="配置示例" tabindex="-1"><a class="header-anchor" href="#配置示例"><span>配置示例</span></a></h2>
<h3 id="最小配置" tabindex="-1"><a class="header-anchor" href="#最小配置"><span>最小配置</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"my-game"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"agent_addr"</span><span class="token operator">:</span> <span class="token string">"127.0.0.1:19090"</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="开发环境" tabindex="-1"><a class="header-anchor" href="#开发环境"><span>开发环境</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"dev-game"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"env"</span><span class="token operator">:</span> <span class="token string">"development"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"agent_addr"</span><span class="token operator">:</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"insecure"</span><span class="token operator">:</span> <span class="token boolean">true</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"timeout_seconds"</span><span class="token operator">:</span> <span class="token number">30</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="生产环境" tabindex="-1"><a class="header-anchor" href="#生产环境"><span>生产环境</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"prod-game"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"env"</span><span class="token operator">:</span> <span class="token string">"production"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"service_id"</span><span class="token operator">:</span> <span class="token string">"game-server-01"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"agent_addr"</span><span class="token operator">:</span> <span class="token string">"croupier-agent.internal:19090"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"insecure"</span><span class="token operator">:</span> <span class="token boolean">false</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"timeout_seconds"</span><span class="token operator">:</span> <span class="token number">60</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"security"</span><span class="token operator">:</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token property">"cert_file"</span><span class="token operator">:</span> <span class="token string">"/etc/tls/client.crt"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token property">"key_file"</span><span class="token operator">:</span> <span class="token string">"/etc/tls/client.key"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token property">"ca_file"</span><span class="token operator">:</span> <span class="token string">"/etc/tls/ca.crt"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token property">"server_name"</span><span class="token operator">:</span> <span class="token string">"croupier.internal"</span></span>
<span class="line">  <span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"auth"</span><span class="token operator">:</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token property">"token"</span><span class="token operator">:</span> <span class="token string">"Bearer ${JWT_TOKEN}"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token property">"headers"</span><span class="token operator">:</span> <span class="token punctuation">{</span></span>
<span class="line">      <span class="token property">"X-Game-Version"</span><span class="token operator">:</span> <span class="token string">"0.1.0"</span><span class="token punctuation">,</span></span>
<span class="line">      <span class="token property">"X-Service-Region"</span><span class="token operator">:</span> <span class="token string">"us-west-2"</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line">  <span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"auto_reconnect"</span><span class="token operator">:</span> <span class="token boolean">true</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"reconnect_interval_seconds"</span><span class="token operator">:</span> <span class="token number">10</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"reconnect_max_attempts"</span><span class="token operator">:</span> <span class="token number">0</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="默认值" tabindex="-1"><a class="header-anchor" href="#默认值"><span>默认值</span></a></h2>
<table>
<thead>
<tr>
<th>字段</th>
<th>默认值</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>agent_addr</code></td>
<td><code v-pre>127.0.0.1:19090</code></td>
</tr>
<tr>
<td><code v-pre>env</code></td>
<td><code v-pre>development</code></td>
</tr>
<tr>
<td><code v-pre>service_id</code></td>
<td><code v-pre>cpp-service</code></td>
</tr>
<tr>
<td><code v-pre>timeout_seconds</code></td>
<td><code v-pre>30</code></td>
</tr>
<tr>
<td><code v-pre>insecure</code></td>
<td><code v-pre>true</code></td>
</tr>
<tr>
<td><code v-pre>auto_reconnect</code></td>
<td><code v-pre>true</code></td>
</tr>
<tr>
<td><code v-pre>reconnect_interval_seconds</code></td>
<td><code v-pre>5</code></td>
</tr>
<tr>
<td><code v-pre>reconnect_max_attempts</code></td>
<td><code v-pre>0</code></td>
</tr>
<tr>
<td><code v-pre>security.cert_file</code></td>
<td>空</td>
</tr>
<tr>
<td><code v-pre>security.key_file</code></td>
<td>空</td>
</tr>
<tr>
<td><code v-pre>security.ca_file</code></td>
<td>空</td>
</tr>
<tr>
<td><code v-pre>security.server_name</code></td>
<td>空</td>
</tr>
<tr>
<td><code v-pre>auth.token</code></td>
<td>空</td>
</tr>
<tr>
<td><code v-pre>auth.headers</code></td>
<td>空</td>
</tr>
</tbody>
</table>
</div></template>


