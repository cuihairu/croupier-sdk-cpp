<template><div><h1 id="clientconfig-api-详解" tabindex="-1"><a class="header-anchor" href="#clientconfig-api-详解"><span>ClientConfig API 详解</span></a></h1>
<p><code v-pre>ClientConfig</code> 结构定义了 Croupier 客户端的所有配置选项。</p>
<h2 id="结构定义" tabindex="-1"><a class="header-anchor" href="#结构定义"><span>结构定义</span></a></h2>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">namespace</span> croupier<span class="token double-colon punctuation">::</span>sdk <span class="token punctuation">{</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">struct</span> <span class="token class-name">ClientConfig</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 基础连接配置</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string game_id<span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string service_id <span class="token operator">=</span> <span class="token string">"cpp-service"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 超时配置</span></span>
<span class="line">    <span class="token keyword">int</span> timeout_seconds <span class="token operator">=</span> <span class="token number">30</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// TLS 配置</span></span>
<span class="line">    <span class="token keyword">bool</span> insecure <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">struct</span> <span class="token class-name">Security</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string cert_file<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string key_file<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string ca_file<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string server_name<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span> security<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 重连配置</span></span>
<span class="line">    <span class="token keyword">bool</span> auto_reconnect <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> reconnect_interval_seconds <span class="token operator">=</span> <span class="token number">5</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> reconnect_max_attempts <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>  <span class="token comment">// 0 = 无限重试</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 认证配置</span></span>
<span class="line">    <span class="token keyword">struct</span> <span class="token class-name">Auth</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string token<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>map<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">></span> headers<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span> auth<span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token punctuation">}</span> <span class="token comment">// namespace croupier::sdk</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="配置字段详解" tabindex="-1"><a class="header-anchor" href="#配置字段详解"><span>配置字段详解</span></a></h2>
<h3 id="基础连接配置" tabindex="-1"><a class="header-anchor" href="#基础连接配置"><span>基础连接配置</span></a></h3>
<h4 id="agent-addr" tabindex="-1"><a class="header-anchor" href="#agent-addr"><span>agent_addr</span></a></h4>
<p>Agent 服务器地址，格式为 <code v-pre>host:port</code>。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span>           <span class="token comment">// 本地 Agent</span></span>
<span class="line">config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"croupier-agent:19090"</span><span class="token punctuation">;</span>      <span class="token comment">// Kubernetes 服务</span></span>
<span class="line">config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"10.0.0.5:19090"</span><span class="token punctuation">;</span>            <span class="token comment">// IP 地址</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h4 id="game-id" tabindex="-1"><a class="header-anchor" href="#game-id"><span>game_id</span></a></h4>
<p>游戏/项目唯一标识符。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"my-mmorpg"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"production-game-2024"</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h4 id="env" tabindex="-1"><a class="header-anchor" href="#env"><span>env</span></a></h4>
<p>部署环境标识。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">;</span>  <span class="token comment">// 开发环境</span></span>
<span class="line">config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"staging"</span><span class="token punctuation">;</span>      <span class="token comment">// 预发布环境</span></span>
<span class="line">config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"production"</span><span class="token punctuation">;</span>   <span class="token comment">// 生产环境</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h4 id="service-id" tabindex="-1"><a class="header-anchor" href="#service-id"><span>service_id</span></a></h4>
<p>服务实例标识符，用于区分同一服务的多个实例。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>service_id <span class="token operator">=</span> <span class="token string">"game-server-01"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>service_id <span class="token operator">=</span> <span class="token string">"backend-service-"</span> <span class="token operator">+</span> std<span class="token double-colon punctuation">::</span><span class="token function">to_string</span><span class="token punctuation">(</span><span class="token function">GetProcessID</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="超时配置" tabindex="-1"><a class="header-anchor" href="#超时配置"><span>超时配置</span></a></h3>
<h4 id="timeout-seconds" tabindex="-1"><a class="header-anchor" href="#timeout-seconds"><span>timeout_seconds</span></a></h4>
<p>网络操作超时时间（秒）。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>timeout_seconds <span class="token operator">=</span> <span class="token number">30</span><span class="token punctuation">;</span>   <span class="token comment">// 默认 30 秒</span></span>
<span class="line">config<span class="token punctuation">.</span>timeout_seconds <span class="token operator">=</span> <span class="token number">60</span><span class="token punctuation">;</span>   <span class="token comment">// 1 分钟</span></span>
<span class="line">config<span class="token punctuation">.</span>timeout_seconds <span class="token operator">=</span> <span class="token number">300</span><span class="token punctuation">;</span>  <span class="token comment">// 5 分钟（长操作）</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="tls-配置" tabindex="-1"><a class="header-anchor" href="#tls-配置"><span>TLS 配置</span></a></h3>
<h4 id="insecure" tabindex="-1"><a class="header-anchor" href="#insecure"><span>insecure</span></a></h4>
<p>是否跳过 TLS 验证（仅用于开发）。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>insecure <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span>   <span class="token comment">// 开发环境：跳过验证</span></span>
<span class="line">config<span class="token punctuation">.</span>insecure <span class="token operator">=</span> <span class="token boolean">false</span><span class="token punctuation">;</span>  <span class="token comment">// 生产环境：启用 TLS</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h4 id="security-cert-file" tabindex="-1"><a class="header-anchor" href="#security-cert-file"><span>security.cert_file</span></a></h4>
<p>客户端证书文件路径。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>cert_file <span class="token operator">=</span> <span class="token string">"/etc/tls/client.crt"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>cert_file <span class="token operator">=</span> <span class="token string">"./certs/client-cert.pem"</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h4 id="security-key-file" tabindex="-1"><a class="header-anchor" href="#security-key-file"><span>security.key_file</span></a></h4>
<p>客户端私钥文件路径。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>key_file <span class="token operator">=</span> <span class="token string">"/etc/tls/client.key"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>key_file <span class="token operator">=</span> <span class="token string">"./certs/client-key.pem"</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h4 id="security-ca-file" tabindex="-1"><a class="header-anchor" href="#security-ca-file"><span>security.ca_file</span></a></h4>
<p>CA 证书文件路径。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>ca_file <span class="token operator">=</span> <span class="token string">"/etc/tls/ca.crt"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>ca_file <span class="token operator">=</span> <span class="token string">"./certs/ca-bundle.crt"</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h4 id="security-server-name" tabindex="-1"><a class="header-anchor" href="#security-server-name"><span>security.server_name</span></a></h4>
<p>TLS 服务器名称验证（SNI）。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>server_name <span class="token operator">=</span> <span class="token string">"croupier.internal"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>server_name <span class="token operator">=</span> <span class="token string">"agent.production.com"</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="重连配置" tabindex="-1"><a class="header-anchor" href="#重连配置"><span>重连配置</span></a></h3>
<h4 id="auto-reconnect" tabindex="-1"><a class="header-anchor" href="#auto-reconnect"><span>auto_reconnect</span></a></h4>
<p>是否自动重连。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>auto_reconnect <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span>   <span class="token comment">// 连接断开时自动重连</span></span>
<span class="line">config<span class="token punctuation">.</span>auto_reconnect <span class="token operator">=</span> <span class="token boolean">false</span><span class="token punctuation">;</span>  <span class="token comment">// 连接断开时退出</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h4 id="reconnect-interval-seconds" tabindex="-1"><a class="header-anchor" href="#reconnect-interval-seconds"><span>reconnect_interval_seconds</span></a></h4>
<p>重连尝试间隔（秒）。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>reconnect_interval_seconds <span class="token operator">=</span> <span class="token number">5</span><span class="token punctuation">;</span>   <span class="token comment">// 每 5 秒重试一次</span></span>
<span class="line">config<span class="token punctuation">.</span>reconnect_interval_seconds <span class="token operator">=</span> <span class="token number">30</span><span class="token punctuation">;</span>  <span class="token comment">// 每 30 秒重试一次</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h4 id="reconnect-max-attempts" tabindex="-1"><a class="header-anchor" href="#reconnect-max-attempts"><span>reconnect_max_attempts</span></a></h4>
<p>最大重连次数（0 表示无限重试）。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>reconnect_max_attempts <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>    <span class="token comment">// 无限重试</span></span>
<span class="line">config<span class="token punctuation">.</span>reconnect_max_attempts <span class="token operator">=</span> <span class="token number">10</span><span class="token punctuation">;</span>   <span class="token comment">// 最多尝试 10 次</span></span>
<span class="line">config<span class="token punctuation">.</span>reconnect_max_attempts <span class="token operator">=</span> <span class="token operator">-</span><span class="token number">1</span><span class="token punctuation">;</span>   <span class="token comment">// 不重连</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="认证配置" tabindex="-1"><a class="header-anchor" href="#认证配置"><span>认证配置</span></a></h3>
<h4 id="auth-token" tabindex="-1"><a class="header-anchor" href="#auth-token"><span>auth.token</span></a></h4>
<p>JWT 认证令牌。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>auth<span class="token punctuation">.</span>token <span class="token operator">=</span> <span class="token string">"Bearer eyJhbGciOiJIUzI1NiIs..."</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><h4 id="auth-headers" tabindex="-1"><a class="header-anchor" href="#auth-headers"><span>auth.headers</span></a></h4>
<p>额外的 HTTP 头部。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>auth<span class="token punctuation">.</span>headers <span class="token operator">=</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"X-Game-Version"</span><span class="token punctuation">,</span> <span class="token string">"0.1.0"</span><span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"X-Service-Region"</span><span class="token punctuation">,</span> <span class="token string">"us-west-2"</span><span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"X-Cluster"</span><span class="token punctuation">,</span> <span class="token string">"production-01"</span><span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="配置加载" tabindex="-1"><a class="header-anchor" href="#配置加载"><span>配置加载</span></a></h2>
<h3 id="从文件加载" tabindex="-1"><a class="header-anchor" href="#从文件加载"><span>从文件加载</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">"croupier/sdk/config/client_config_loader.h"</span></span></span>
<span class="line"></span>
<span class="line">ClientConfigLoader loader<span class="token punctuation">;</span></span>
<span class="line">ClientConfig config <span class="token operator">=</span> loader<span class="token punctuation">.</span><span class="token function">LoadFromFile</span><span class="token punctuation">(</span><span class="token string">"./config.json"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="从环境变量覆盖" tabindex="-1"><a class="header-anchor" href="#从环境变量覆盖"><span>从环境变量覆盖</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">ClientConfig config <span class="token operator">=</span> loader<span class="token punctuation">.</span><span class="token function">LoadWithEnvironmentOverrides</span><span class="token punctuation">(</span></span>
<span class="line">    <span class="token string">"./config.json"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token string">"CROUPIER_"</span>  <span class="token comment">// 环境变量前缀</span></span>
<span class="line"><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 环境变量:</span></span>
<span class="line"><span class="token comment">// CROUPIER_GAME_ID=override-game</span></span>
<span class="line"><span class="token comment">// CROUPIER_ENV=staging</span></span>
<span class="line"><span class="token comment">// CROUPIER_AGENT_ADDR=10.0.0.5:19090</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="配置验证" tabindex="-1"><a class="header-anchor" href="#配置验证"><span>配置验证</span></a></h2>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">ClientConfigLoader loader<span class="token punctuation">;</span></span>
<span class="line"><span class="token keyword">auto</span> errors <span class="token operator">=</span> loader<span class="token punctuation">.</span><span class="token function">ValidateConfig</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token operator">!</span>errors<span class="token punctuation">.</span><span class="token function">empty</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token keyword">for</span> <span class="token punctuation">(</span><span class="token keyword">const</span> <span class="token keyword">auto</span><span class="token operator">&amp;</span> error <span class="token operator">:</span> errors<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>cerr <span class="token operator">&lt;&lt;</span> <span class="token string">"配置错误: "</span> <span class="token operator">&lt;&lt;</span> error <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line">    <span class="token keyword">return</span> <span class="token number">1</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="配置示例" tabindex="-1"><a class="header-anchor" href="#配置示例"><span>配置示例</span></a></h2>
<h3 id="开发环境" tabindex="-1"><a class="header-anchor" href="#开发环境"><span>开发环境</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"dev-game"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"env"</span><span class="token operator">:</span> <span class="token string">"development"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"service_id"</span><span class="token operator">:</span> <span class="token string">"dev-backend"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"agent_addr"</span><span class="token operator">:</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"insecure"</span><span class="token operator">:</span> <span class="token boolean">true</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"timeout_seconds"</span><span class="token operator">:</span> <span class="token number">30</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"auto_reconnect"</span><span class="token operator">:</span> <span class="token boolean">true</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="生产环境" tabindex="-1"><a class="header-anchor" href="#生产环境"><span>生产环境</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"prod-game"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"env"</span><span class="token operator">:</span> <span class="token string">"production"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"service_id"</span><span class="token operator">:</span> <span class="token string">"prod-backend-01"</span><span class="token punctuation">,</span></span>
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
<span class="line">      <span class="token property">"X-Game-Version"</span><span class="token operator">:</span> <span class="token string">"2.1.0"</span><span class="token punctuation">,</span></span>
<span class="line">      <span class="token property">"X-Service-Region"</span><span class="token operator">:</span> <span class="token string">"us-west-2"</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line">  <span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"auto_reconnect"</span><span class="token operator">:</span> <span class="token boolean">true</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"reconnect_interval_seconds"</span><span class="token operator">:</span> <span class="token number">10</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"reconnect_max_attempts"</span><span class="token operator">:</span> <span class="token number">0</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="kubernetes-环境" tabindex="-1"><a class="header-anchor" href="#kubernetes-环境"><span>Kubernetes 环境</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"${GAME_ID}"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"env"</span><span class="token operator">:</span> <span class="token string">"production"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"service_id"</span><span class="token operator">:</span> <span class="token string">"${HOSTNAME}"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"agent_addr"</span><span class="token operator">:</span> <span class="token string">"croupier-agent:19090"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"insecure"</span><span class="token operator">:</span> <span class="token boolean">false</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"security"</span><span class="token operator">:</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token property">"cert_file"</span><span class="token operator">:</span> <span class="token string">"/etc/tls/client.crt"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token property">"key_file"</span><span class="token operator">:</span> <span class="token string">"/etc/tls/client.key"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token property">"ca_file"</span><span class="token operator">:</span> <span class="token string">"/etc/tls/ca.crt"</span></span>
<span class="line">  <span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"auth"</span><span class="token operator">:</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token property">"token"</span><span class="token operator">:</span> <span class="token string">"Bearer ${JWT_TOKEN}"</span></span>
<span class="line">  <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div></div></template>


