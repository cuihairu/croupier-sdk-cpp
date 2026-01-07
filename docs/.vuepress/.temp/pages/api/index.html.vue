<template><div><h1 id="api-参考" tabindex="-1"><a class="header-anchor" href="#api-参考"><span>API 参考</span></a></h1>
<p>本文档提供 Croupier C++ SDK 的完整 API 参考。</p>
<h2 id="命名空间" tabindex="-1"><a class="header-anchor" href="#命名空间"><span>命名空间</span></a></h2>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">namespace</span> croupier<span class="token double-colon punctuation">::</span>sdk <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 核心类</span></span>
<span class="line">    <span class="token keyword">class</span> <span class="token class-name">CroupierClient</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">struct</span> <span class="token class-name">ClientConfig</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 描述符</span></span>
<span class="line">    <span class="token keyword">struct</span> <span class="token class-name">FunctionDescriptor</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">struct</span> <span class="token class-name">VirtualObjectDescriptor</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">struct</span> <span class="token class-name">ComponentDescriptor</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 工具</span></span>
<span class="line">    <span class="token keyword">namespace</span> utils <span class="token punctuation">{</span></span>
<span class="line">        nlohmann<span class="token double-colon punctuation">::</span>json <span class="token function">ParseJSON</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> str<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string <span class="token function">ToJSON</span><span class="token punctuation">(</span><span class="token keyword">const</span> nlohmann<span class="token double-colon punctuation">::</span>json<span class="token operator">&amp;</span> json<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="核心类型" tabindex="-1"><a class="header-anchor" href="#核心类型"><span>核心类型</span></a></h2>
<h3 id="functionhandler" tabindex="-1"><a class="header-anchor" href="#functionhandler"><span>FunctionHandler</span></a></h3>
<p>函数处理器类型定义。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">using</span> FunctionHandler <span class="token operator">=</span> std<span class="token double-colon punctuation">::</span>function<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span><span class="token function">string</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> context<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span><span class="token operator">></span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>参数:</strong></p>
<ul>
<li><code v-pre>context</code>: 调用上下文（JSON 字符串）</li>
<li><code v-pre>payload</code>: 函数参数（JSON 字符串）</li>
</ul>
<p><strong>返回值:</strong> 函数执行结果（JSON 字符串）</p>
<hr>
<h3 id="clientconfig" tabindex="-1"><a class="header-anchor" href="#clientconfig"><span>ClientConfig</span></a></h3>
<p>客户端配置结构。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">struct</span> <span class="token class-name">ClientConfig</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span>  <span class="token comment">// Agent 地址</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string game_id<span class="token punctuation">;</span>                          <span class="token comment">// 游戏 ID</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">;</span>              <span class="token comment">// 环境</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string service_id <span class="token operator">=</span> <span class="token string">"cpp-service"</span><span class="token punctuation">;</span>       <span class="token comment">// 服务 ID</span></span>
<span class="line">    <span class="token keyword">bool</span> insecure <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span>                         <span class="token comment">// 是否跳过 TLS 验证</span></span>
<span class="line">    <span class="token keyword">int</span> timeout_seconds <span class="token operator">=</span> <span class="token number">30</span><span class="token punctuation">;</span>                     <span class="token comment">// 超时时间</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 重连配置</span></span>
<span class="line">    <span class="token keyword">bool</span> auto_reconnect <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> reconnect_interval_seconds <span class="token operator">=</span> <span class="token number">5</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> reconnect_max_attempts <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>  <span class="token comment">// 0 = 无限</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 安全配置</span></span>
<span class="line">    <span class="token keyword">struct</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string cert_file<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string key_file<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string ca_file<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string server_name<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span> security<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 认证配置</span></span>
<span class="line">    <span class="token keyword">struct</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string token<span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>map<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">></span> headers<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span> auth<span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><p><strong>环境变量覆盖:</strong></p>
<table>
<thead>
<tr>
<th>环境变量</th>
<th>说明</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>CROUPIER_GAME_ID</code></td>
<td>游戏 ID</td>
</tr>
<tr>
<td><code v-pre>CROUPIER_ENV</code></td>
<td>环境</td>
</tr>
<tr>
<td><code v-pre>CROUPIER_AGENT_ADDR</code></td>
<td>Agent 地址</td>
</tr>
<tr>
<td><code v-pre>CROUPIER_INSECURE</code></td>
<td>是否跳过 TLS</td>
</tr>
<tr>
<td><code v-pre>CROUPIER_AUTO_RECONNECT</code></td>
<td>自动重连</td>
</tr>
<tr>
<td><code v-pre>CROUPIER_RECONNECT_INTERVAL_SECONDS</code></td>
<td>重连间隔</td>
</tr>
<tr>
<td><code v-pre>CROUPIER_RECONNECT_MAX_ATTEMPTS</code></td>
<td>最大重连次数</td>
</tr>
</tbody>
</table>
<hr>
<h3 id="functiondescriptor" tabindex="-1"><a class="header-anchor" href="#functiondescriptor"><span>FunctionDescriptor</span></a></h3>
<p>函数描述符。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">struct</span> <span class="token class-name">FunctionDescriptor</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string id<span class="token punctuation">;</span>                    <span class="token comment">// 函数 ID，如 "wallet.transfer"</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string version<span class="token punctuation">;</span>               <span class="token comment">// 版本号，如 "0.1.0"</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string name<span class="token punctuation">;</span>                  <span class="token comment">// 显示名称</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string description<span class="token punctuation">;</span>           <span class="token comment">// 描述</span></span>
<span class="line">    nlohmann<span class="token double-colon punctuation">::</span>json input_schema<span class="token punctuation">;</span>       <span class="token comment">// 输入 Schema</span></span>
<span class="line">    nlohmann<span class="token double-colon punctuation">::</span>json output_schema<span class="token punctuation">;</span>      <span class="token comment">// 输出 Schema</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>vector<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token operator">></span> tags<span class="token punctuation">;</span>     <span class="token comment">// 标签</span></span>
<span class="line">    <span class="token keyword">int</span> timeout_ms <span class="token operator">=</span> <span class="token number">30000</span><span class="token punctuation">;</span>            <span class="token comment">// 超时时间（毫秒）</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="virtualobjectdescriptor" tabindex="-1"><a class="header-anchor" href="#virtualobjectdescriptor"><span>VirtualObjectDescriptor</span></a></h3>
<p>虚拟对象描述符。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">struct</span> <span class="token class-name">VirtualObjectDescriptor</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string id<span class="token punctuation">;</span>                    <span class="token comment">// 对象 ID</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string version<span class="token punctuation">;</span>               <span class="token comment">// 版本号</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string name<span class="token punctuation">;</span>                  <span class="token comment">// 显示名称</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string description<span class="token punctuation">;</span>           <span class="token comment">// 描述</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>map<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">></span> operations<span class="token punctuation">;</span>  <span class="token comment">// 操作映射</span></span>
<span class="line">    nlohmann<span class="token double-colon punctuation">::</span>json schema<span class="token punctuation">;</span>             <span class="token comment">// 数据 Schema</span></span>
<span class="line">    nlohmann<span class="token double-colon punctuation">::</span>json metadata<span class="token punctuation">;</span>           <span class="token comment">// 元数据</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h2 id="类-croupierclient" tabindex="-1"><a class="header-anchor" href="#类-croupierclient"><span>类: CroupierClient</span></a></h2>
<p>主客户端类，管理与 Croupier Agent 的连接和函数注册。</p>
<h3 id="构造函数" tabindex="-1"><a class="header-anchor" href="#构造函数"><span>构造函数</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token function">CroupierClient</span><span class="token punctuation">(</span><span class="token keyword">const</span> ClientConfig<span class="token operator">&amp;</span> config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><h3 id="公共方法" tabindex="-1"><a class="header-anchor" href="#公共方法"><span>公共方法</span></a></h3>
<h4 id="registerfunction" tabindex="-1"><a class="header-anchor" href="#registerfunction"><span>RegisterFunction</span></a></h4>
<p>注册单个函数。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">bool</span> <span class="token function">RegisterFunction</span><span class="token punctuation">(</span><span class="token keyword">const</span> FunctionDescriptor<span class="token operator">&amp;</span> desc<span class="token punctuation">,</span> FunctionHandler handler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>参数:</strong></p>
<ul>
<li><code v-pre>desc</code>: 函数描述符</li>
<li><code v-pre>handler</code>: 函数处理器</li>
</ul>
<p><strong>返回值:</strong> 成功返回 <code v-pre>true</code>，失败返回 <code v-pre>false</code></p>
<hr>
<h4 id="registervirtualobject" tabindex="-1"><a class="header-anchor" href="#registervirtualobject"><span>RegisterVirtualObject</span></a></h4>
<p>注册虚拟对象。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">bool</span> <span class="token function">RegisterVirtualObject</span><span class="token punctuation">(</span></span>
<span class="line">    <span class="token keyword">const</span> VirtualObjectDescriptor<span class="token operator">&amp;</span> desc<span class="token punctuation">,</span></span>
<span class="line">    <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>map<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> FunctionHandler<span class="token operator">></span><span class="token operator">&amp;</span> handlers</span>
<span class="line"><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><p><strong>参数:</strong></p>
<ul>
<li><code v-pre>desc</code>: 虚拟对象描述符</li>
<li><code v-pre>handlers</code>: 操作处理器映射</li>
</ul>
<p><strong>返回值:</strong> 成功返回 <code v-pre>true</code>，失败返回 <code v-pre>false</code></p>
<hr>
<h4 id="registercomponent" tabindex="-1"><a class="header-anchor" href="#registercomponent"><span>RegisterComponent</span></a></h4>
<p>注册组件。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">bool</span> <span class="token function">RegisterComponent</span><span class="token punctuation">(</span><span class="token keyword">const</span> ComponentDescriptor<span class="token operator">&amp;</span> comp<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>参数:</strong></p>
<ul>
<li><code v-pre>comp</code>: 组件描述符</li>
</ul>
<p><strong>返回值:</strong> 成功返回 <code v-pre>true</code>，失败返回 <code v-pre>false</code></p>
<hr>
<h4 id="connect" tabindex="-1"><a class="header-anchor" href="#connect"><span>Connect</span></a></h4>
<p>连接到 Agent。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">bool</span> <span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>返回值:</strong> 成功返回 <code v-pre>true</code>，失败返回 <code v-pre>false</code></p>
<hr>
<h4 id="serve" tabindex="-1"><a class="header-anchor" href="#serve"><span>Serve</span></a></h4>
<p>开始服务（阻塞调用）。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">void</span> <span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p>此方法会阻塞当前线程，处理来自 Agent 的函数调用请求。</p>
<hr>
<h4 id="stop" tabindex="-1"><a class="header-anchor" href="#stop"><span>Stop</span></a></h4>
<p>停止服务。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">void</span> <span class="token function">Stop</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><hr>
<h4 id="close" tabindex="-1"><a class="header-anchor" href="#close"><span>Close</span></a></h4>
<p>关闭连接并释放资源。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">void</span> <span class="token function">Close</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><hr>
<h4 id="isconnected" tabindex="-1"><a class="header-anchor" href="#isconnected"><span>IsConnected</span></a></h4>
<p>检查连接状态。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">bool</span> <span class="token function">IsConnected</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token keyword">const</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>返回值:</strong> 已连接返回 <code v-pre>true</code></p>
<hr>
<h2 id="工具函数" tabindex="-1"><a class="header-anchor" href="#工具函数"><span>工具函数</span></a></h2>
<h3 id="utils-parsejson" tabindex="-1"><a class="header-anchor" href="#utils-parsejson"><span>utils::ParseJSON</span></a></h3>
<p>解析 JSON 字符串。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">nlohmann<span class="token double-colon punctuation">::</span>json <span class="token function">ParseJSON</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> str<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>异常:</strong> 如果 JSON 格式无效，抛出 <code v-pre>std::runtime_error</code></p>
<hr>
<h3 id="utils-tojson" tabindex="-1"><a class="header-anchor" href="#utils-tojson"><span>utils::ToJSON</span></a></h3>
<p>将对象转换为 JSON 字符串。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">std<span class="token double-colon punctuation">::</span>string <span class="token function">ToJSON</span><span class="token punctuation">(</span><span class="token keyword">const</span> nlohmann<span class="token double-colon punctuation">::</span>json<span class="token operator">&amp;</span> json<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><hr>
<h3 id="utils-validatejson" tabindex="-1"><a class="header-anchor" href="#utils-validatejson"><span>utils::ValidateJSON</span></a></h3>
<p>根据 Schema 验证 JSON。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">bool</span> <span class="token function">ValidateJSON</span><span class="token punctuation">(</span><span class="token keyword">const</span> nlohmann<span class="token double-colon punctuation">::</span>json<span class="token operator">&amp;</span> data<span class="token punctuation">,</span> <span class="token keyword">const</span> nlohmann<span class="token double-colon punctuation">::</span>json<span class="token operator">&amp;</span> schema<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><hr>
<h2 id="配置加载" tabindex="-1"><a class="header-anchor" href="#配置加载"><span>配置加载</span></a></h2>
<h3 id="clientconfigloader" tabindex="-1"><a class="header-anchor" href="#clientconfigloader"><span>ClientConfigLoader</span></a></h3>
<p>配置加载器类。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">class</span> <span class="token class-name">ClientConfigLoader</span> <span class="token punctuation">{</span></span>
<span class="line"><span class="token keyword">public</span><span class="token operator">:</span></span>
<span class="line">    <span class="token comment">// 从文件加载</span></span>
<span class="line">    ClientConfig <span class="token function">LoadFromFile</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> file_path<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 从 JSON 字符串加载</span></span>
<span class="line">    ClientConfig <span class="token function">LoadFromJson</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> json_content<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 带环境变量覆盖加载</span></span>
<span class="line">    ClientConfig <span class="token function">LoadWithEnvironmentOverrides</span><span class="token punctuation">(</span></span>
<span class="line">        <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> file_path<span class="token punctuation">,</span></span>
<span class="line">        <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> env_prefix <span class="token operator">=</span> <span class="token string">"CROUPIER_"</span></span>
<span class="line">    <span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 验证配置</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>vector<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token operator">></span> <span class="token function">ValidateConfig</span><span class="token punctuation">(</span><span class="token keyword">const</span> ClientConfig<span class="token operator">&amp;</span> config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 生成示例配置</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string <span class="token function">GenerateExampleConfig</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="错误处理" tabindex="-1"><a class="header-anchor" href="#错误处理"><span>错误处理</span></a></h2>
<h3 id="croupierexception" tabindex="-1"><a class="header-anchor" href="#croupierexception"><span>CroupierException</span></a></h3>
<p>基础异常类。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">class</span> <span class="token class-name">CroupierException</span> <span class="token operator">:</span> <span class="token base-clause"><span class="token keyword">public</span> std<span class="token double-colon punctuation">::</span><span class="token class-name">runtime_error</span></span> <span class="token punctuation">{</span></span>
<span class="line"><span class="token keyword">public</span><span class="token operator">:</span></span>
<span class="line">    <span class="token keyword">explicit</span> <span class="token function">CroupierException</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> message<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">explicit</span> <span class="token function">CroupierException</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> code<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> message<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="异常类型" tabindex="-1"><a class="header-anchor" href="#异常类型"><span>异常类型</span></a></h3>
<table>
<thead>
<tr>
<th>异常类</th>
<th>说明</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>ConnectionException</code></td>
<td>连接失败</td>
</tr>
<tr>
<td><code v-pre>RegistrationException</code></td>
<td>注册失败</td>
</tr>
<tr>
<td><code v-pre>ConfigException</code></td>
<td>配置错误</td>
</tr>
<tr>
<td><code v-pre>TimeoutException</code></td>
<td>操作超时</td>
</tr>
</tbody>
</table>
<h2 id="回调类型" tabindex="-1"><a class="header-anchor" href="#回调类型"><span>回调类型</span></a></h2>
<h3 id="connectioncallback" tabindex="-1"><a class="header-anchor" href="#connectioncallback"><span>ConnectionCallback</span></a></h3>
<p>连接状态变化回调。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">using</span> ConnectionCallback <span class="token operator">=</span> std<span class="token double-colon punctuation">::</span>function<span class="token operator">&lt;</span><span class="token keyword">void</span><span class="token punctuation">(</span><span class="token keyword">bool</span> connected<span class="token punctuation">)</span><span class="token operator">></span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><h3 id="errorcallback" tabindex="-1"><a class="header-anchor" href="#errorcallback"><span>ErrorCallback</span></a></h3>
<p>错误回调。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">using</span> ErrorCallback <span class="token operator">=</span> std<span class="token double-colon punctuation">::</span>function<span class="token operator">&lt;</span><span class="token keyword">void</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> error<span class="token punctuation">)</span><span class="token operator">></span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><h3 id="logcallback" tabindex="-1"><a class="header-anchor" href="#logcallback"><span>LogCallback</span></a></h3>
<p>日志回调。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">using</span> LogCallback <span class="token operator">=</span> std<span class="token double-colon punctuation">::</span>function<span class="token operator">&lt;</span><span class="token keyword">void</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> level<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> message<span class="token punctuation">)</span><span class="token operator">></span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div></div></template>


