<template><div><h1 id="croupierclient-api-详解" tabindex="-1"><a class="header-anchor" href="#croupierclient-api-详解"><span>CroupierClient API 详解</span></a></h1>
<p><code v-pre>CroupierClient</code> 是 SDK 的核心类，负责管理与 Croupier Agent 的连接和函数注册。</p>
<h2 id="类定义" tabindex="-1"><a class="header-anchor" href="#类定义"><span>类定义</span></a></h2>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">namespace</span> croupier<span class="token double-colon punctuation">::</span>sdk <span class="token punctuation">{</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">class</span> <span class="token class-name">CroupierClient</span> <span class="token punctuation">{</span></span>
<span class="line"><span class="token keyword">public</span><span class="token operator">:</span></span>
<span class="line">    <span class="token comment">// 构造函数</span></span>
<span class="line">    <span class="token keyword">explicit</span> <span class="token function">CroupierClient</span><span class="token punctuation">(</span><span class="token keyword">const</span> ClientConfig<span class="token operator">&amp;</span> config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 析构函数</span></span>
<span class="line">    <span class="token operator">~</span><span class="token function">CroupierClient</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 函数注册</span></span>
<span class="line">    <span class="token keyword">bool</span> <span class="token function">RegisterFunction</span><span class="token punctuation">(</span><span class="token keyword">const</span> FunctionDescriptor<span class="token operator">&amp;</span> desc<span class="token punctuation">,</span> FunctionHandler handler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">bool</span> <span class="token function">RegisterFunctions</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>vector<span class="token operator">&lt;</span>FunctionDescriptor<span class="token operator">></span><span class="token operator">&amp;</span> handlers<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 虚拟对象注册</span></span>
<span class="line">    <span class="token keyword">bool</span> <span class="token function">RegisterVirtualObject</span><span class="token punctuation">(</span></span>
<span class="line">        <span class="token keyword">const</span> VirtualObjectDescriptor<span class="token operator">&amp;</span> desc<span class="token punctuation">,</span></span>
<span class="line">        <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>map<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> FunctionHandler<span class="token operator">></span><span class="token operator">&amp;</span> handlers</span>
<span class="line">    <span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 组件注册</span></span>
<span class="line">    <span class="token keyword">bool</span> <span class="token function">RegisterComponent</span><span class="token punctuation">(</span><span class="token keyword">const</span> ComponentDescriptor<span class="token operator">&amp;</span> comp<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 连接管理</span></span>
<span class="line">    <span class="token keyword">bool</span> <span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">Disconnect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">bool</span> <span class="token function">IsConnected</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token keyword">const</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 服务管理</span></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">Stop</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 回调设置</span></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">SetConnectionCallback</span><span class="token punctuation">(</span>ConnectionCallback callback<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">SetErrorCallback</span><span class="token punctuation">(</span>ErrorCallback callback<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">SetLogCallback</span><span class="token punctuation">(</span>LogCallback callback<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 配置</span></span>
<span class="line">    <span class="token keyword">const</span> ClientConfig<span class="token operator">&amp;</span> <span class="token function">GetConfig</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token keyword">const</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">private</span><span class="token operator">:</span></span>
<span class="line">    <span class="token comment">// 内部实现...</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token punctuation">}</span> <span class="token comment">// namespace croupier::sdk</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="方法详解" tabindex="-1"><a class="header-anchor" href="#方法详解"><span>方法详解</span></a></h2>
<h3 id="构造函数" tabindex="-1"><a class="header-anchor" href="#构造函数"><span>构造函数</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">explicit</span> <span class="token function">CroupierClient</span><span class="token punctuation">(</span><span class="token keyword">const</span> ClientConfig<span class="token operator">&amp;</span> config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p>创建客户端实例。</p>
<p><strong>参数:</strong></p>
<ul>
<li><code v-pre>config</code>: 客户端配置</li>
</ul>
<p><strong>示例:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">ClientConfig config<span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"my-game"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"production"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"croupier-agent:19090"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="registerfunction" tabindex="-1"><a class="header-anchor" href="#registerfunction"><span>RegisterFunction</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">bool</span> <span class="token function">RegisterFunction</span><span class="token punctuation">(</span><span class="token keyword">const</span> FunctionDescriptor<span class="token operator">&amp;</span> desc<span class="token punctuation">,</span> FunctionHandler handler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p>注册单个函数到 Agent。</p>
<p><strong>参数:</strong></p>
<ul>
<li><code v-pre>desc</code>: 函数描述符</li>
<li><code v-pre>handler</code>: 函数处理器</li>
</ul>
<p><strong>返回值:</strong> 成功返回 <code v-pre>true</code></p>
<p><strong>示例:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">FunctionDescriptor desc<span class="token punctuation">;</span></span>
<span class="line">desc<span class="token punctuation">.</span>id <span class="token operator">=</span> <span class="token string">"math.add"</span><span class="token punctuation">;</span></span>
<span class="line">desc<span class="token punctuation">.</span>version <span class="token operator">=</span> <span class="token string">"0.1.0"</span><span class="token punctuation">;</span></span>
<span class="line">desc<span class="token punctuation">.</span>name <span class="token operator">=</span> <span class="token string">"Add Numbers"</span><span class="token punctuation">;</span></span>
<span class="line">desc<span class="token punctuation">.</span>description <span class="token operator">=</span> <span class="token string">"Adds two numbers together"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">client<span class="token punctuation">.</span><span class="token function">RegisterFunction</span><span class="token punctuation">(</span>desc<span class="token punctuation">,</span> <span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> ctx<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token keyword">auto</span> data <span class="token operator">=</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ParseJSON</span><span class="token punctuation">(</span>payload<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> result <span class="token operator">=</span> data<span class="token punctuation">[</span><span class="token string">"a"</span><span class="token punctuation">]</span> <span class="token operator">+</span> data<span class="token punctuation">[</span><span class="token string">"b"</span><span class="token punctuation">]</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">return</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ToJSON</span><span class="token punctuation">(</span><span class="token punctuation">{</span><span class="token punctuation">{</span><span class="token string">"result"</span><span class="token punctuation">,</span> result<span class="token punctuation">}</span><span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="registervirtualobject" tabindex="-1"><a class="header-anchor" href="#registervirtualobject"><span>RegisterVirtualObject</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">bool</span> <span class="token function">RegisterVirtualObject</span><span class="token punctuation">(</span></span>
<span class="line">    <span class="token keyword">const</span> VirtualObjectDescriptor<span class="token operator">&amp;</span> desc<span class="token punctuation">,</span></span>
<span class="line">    <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>map<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> FunctionHandler<span class="token operator">></span><span class="token operator">&amp;</span> handlers</span>
<span class="line"><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><p>注册虚拟对象及其操作处理器。</p>
<p><strong>参数:</strong></p>
<ul>
<li><code v-pre>desc</code>: 虚拟对象描述符</li>
<li><code v-pre>handlers</code>: 操作名到处理器的映射</li>
</ul>
<p><strong>返回值:</strong> 成功返回 <code v-pre>true</code></p>
<p><strong>示例:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">VirtualObjectDescriptor wallet<span class="token punctuation">;</span></span>
<span class="line">wallet<span class="token punctuation">.</span>id <span class="token operator">=</span> <span class="token string">"wallet.entity"</span><span class="token punctuation">;</span></span>
<span class="line">wallet<span class="token punctuation">.</span>operations<span class="token punctuation">[</span><span class="token string">"get"</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token string">"wallet.get"</span><span class="token punctuation">;</span></span>
<span class="line">wallet<span class="token punctuation">.</span>operations<span class="token punctuation">[</span><span class="token string">"transfer"</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token string">"wallet.transfer"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">std<span class="token double-colon punctuation">::</span>map<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> FunctionHandler<span class="token operator">></span> handlers <span class="token operator">=</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"wallet.get"</span><span class="token punctuation">,</span> GetWalletHandler<span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"wallet.transfer"</span><span class="token punctuation">,</span> TransferHandler<span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">client<span class="token punctuation">.</span><span class="token function">RegisterVirtualObject</span><span class="token punctuation">(</span>wallet<span class="token punctuation">,</span> handlers<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="connect" tabindex="-1"><a class="header-anchor" href="#connect"><span>Connect</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">bool</span> <span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p>连接到 Croupier Agent。</p>
<p><strong>返回值:</strong> 成功返回 <code v-pre>true</code></p>
<p><strong>连接流程:</strong></p>
<ol>
<li>解析 Agent 地址</li>
<li>建立 gRPC 连接</li>
<li>发送注册信息</li>
<li>启动心跳</li>
</ol>
<p><strong>示例:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token operator">!</span>client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>cerr <span class="token operator">&lt;&lt;</span> <span class="token string">"Failed to connect to agent"</span> <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">return</span> <span class="token number">1</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="serve" tabindex="-1"><a class="header-anchor" href="#serve"><span>Serve</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">void</span> <span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p>开始处理请求（阻塞调用）。</p>
<p><strong>行为:</strong></p>
<ul>
<li>阻塞当前线程</li>
<li>处理来自 Agent 的函数调用请求</li>
<li>自动重连（如果启用）</li>
<li>直到调用 <code v-pre>Stop()</code> 或连接关闭</li>
</ul>
<p><strong>示例:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token comment">// 在单独的线程中运行</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>thread <span class="token function">server_thread</span><span class="token punctuation">(</span><span class="token punctuation">[</span><span class="token operator">&amp;</span>client<span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 主线程继续其他工作...</span></span>
<span class="line"><span class="token comment">// ...</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 需要停止时</span></span>
<span class="line">client<span class="token punctuation">.</span><span class="token function">Stop</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">server_thread<span class="token punctuation">.</span><span class="token function">join</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="stop" tabindex="-1"><a class="header-anchor" href="#stop"><span>Stop</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">void</span> <span class="token function">Stop</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p>停止服务并退出 <code v-pre>Serve()</code> 循环。</p>
<p><strong>示例:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token comment">// 信号处理</span></span>
<span class="line"><span class="token keyword">void</span> <span class="token function">SignalHandler</span><span class="token punctuation">(</span><span class="token keyword">int</span> signal<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Stop</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">std<span class="token double-colon punctuation">::</span><span class="token function">signal</span><span class="token punctuation">(</span>SIGINT<span class="token punctuation">,</span> SignalHandler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">client<span class="token punctuation">.</span><span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="setconnectioncallback" tabindex="-1"><a class="header-anchor" href="#setconnectioncallback"><span>SetConnectionCallback</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">void</span> <span class="token function">SetConnectionCallback</span><span class="token punctuation">(</span>ConnectionCallback callback<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p>设置连接状态变化回调。</p>
<p><strong>回调签名:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">using</span> ConnectionCallback <span class="token operator">=</span> std<span class="token double-colon punctuation">::</span>function<span class="token operator">&lt;</span><span class="token keyword">void</span><span class="token punctuation">(</span><span class="token keyword">bool</span> connected<span class="token punctuation">)</span><span class="token operator">></span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>示例:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">client<span class="token punctuation">.</span><span class="token function">SetConnectionCallback</span><span class="token punctuation">(</span><span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token keyword">bool</span> connected<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token keyword">if</span> <span class="token punctuation">(</span>connected<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"Connected to agent"</span> <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span> <span class="token keyword">else</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"Disconnected from agent"</span> <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="seterrorcallback" tabindex="-1"><a class="header-anchor" href="#seterrorcallback"><span>SetErrorCallback</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">void</span> <span class="token function">SetErrorCallback</span><span class="token punctuation">(</span>ErrorCallback callback<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p>设置错误回调。</p>
<p><strong>回调签名:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">using</span> ErrorCallback <span class="token operator">=</span> std<span class="token double-colon punctuation">::</span>function<span class="token operator">&lt;</span><span class="token keyword">void</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> error<span class="token punctuation">)</span><span class="token operator">></span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>示例:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">client<span class="token punctuation">.</span><span class="token function">SetErrorCallback</span><span class="token punctuation">(</span><span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> error<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>cerr <span class="token operator">&lt;&lt;</span> <span class="token string">"Error: "</span> <span class="token operator">&lt;&lt;</span> error <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h3 id="setlogcallback" tabindex="-1"><a class="header-anchor" href="#setlogcallback"><span>SetLogCallback</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">void</span> <span class="token function">SetLogCallback</span><span class="token punctuation">(</span>LogCallback callback<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p>设置日志回调。</p>
<p><strong>回调签名:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">using</span> LogCallback <span class="token operator">=</span> std<span class="token double-colon punctuation">::</span>function<span class="token operator">&lt;</span><span class="token keyword">void</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> level<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> message<span class="token punctuation">)</span><span class="token operator">></span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>示例:</strong></p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">client<span class="token punctuation">.</span><span class="token function">SetLogCallback</span><span class="token punctuation">(</span><span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> level<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> message<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"["</span> <span class="token operator">&lt;&lt;</span> level <span class="token operator">&lt;&lt;</span> <span class="token string">"] "</span> <span class="token operator">&lt;&lt;</span> message <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="使用模式" tabindex="-1"><a class="header-anchor" href="#使用模式"><span>使用模式</span></a></h2>
<h3 id="基础模式" tabindex="-1"><a class="header-anchor" href="#基础模式"><span>基础模式</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">int</span> <span class="token function">main</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    ClientConfig config<span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"demo-game"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 注册函数</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">RegisterFunction</span><span class="token punctuation">(</span>desc<span class="token punctuation">,</span> handler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 连接并服务</span></span>
<span class="line">    <span class="token keyword">if</span> <span class="token punctuation">(</span>client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        client<span class="token punctuation">.</span><span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>  <span class="token comment">// 阻塞</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> <span class="token number">0</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="多线程模式" tabindex="-1"><a class="header-anchor" href="#多线程模式"><span>多线程模式</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">int</span> <span class="token function">main</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 后台线程服务</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>thread <span class="token function">service_thread</span><span class="token punctuation">(</span><span class="token punctuation">[</span><span class="token operator">&amp;</span>client<span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">if</span> <span class="token punctuation">(</span>client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">            client<span class="token punctuation">.</span><span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token punctuation">}</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 主线程做其他工作</span></span>
<span class="line">    <span class="token keyword">while</span> <span class="token punctuation">(</span>running<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token comment">// ...</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>this_thread<span class="token double-colon punctuation">::</span><span class="token function">sleep_for</span><span class="token punctuation">(</span>std<span class="token double-colon punctuation">::</span>chrono<span class="token double-colon punctuation">::</span><span class="token function">seconds</span><span class="token punctuation">(</span><span class="token number">1</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 清理</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Stop</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    service_thread<span class="token punctuation">.</span><span class="token function">join</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> <span class="token number">0</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="优雅退出模式" tabindex="-1"><a class="header-anchor" href="#优雅退出模式"><span>优雅退出模式</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">std<span class="token double-colon punctuation">::</span>atomic<span class="token operator">&lt;</span><span class="token keyword">bool</span><span class="token operator">></span> <span class="token function">shutdown</span><span class="token punctuation">(</span><span class="token boolean">false</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">void</span> <span class="token function">SignalHandler</span><span class="token punctuation">(</span><span class="token keyword">int</span> signal<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    shutdown <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">int</span> <span class="token function">main</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span><span class="token function">signal</span><span class="token punctuation">(</span>SIGINT<span class="token punctuation">,</span> SignalHandler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span><span class="token function">signal</span><span class="token punctuation">(</span>SIGTERM<span class="token punctuation">,</span> SignalHandler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">RegisterFunction</span><span class="token punctuation">(</span>desc<span class="token punctuation">,</span> handler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>thread <span class="token function">service_thread</span><span class="token punctuation">(</span><span class="token punctuation">[</span><span class="token operator">&amp;</span>client<span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">while</span> <span class="token punctuation">(</span><span class="token operator">!</span>shutdown<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">            <span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token operator">!</span>client<span class="token punctuation">.</span><span class="token function">IsConnected</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">                client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">            <span class="token punctuation">}</span></span>
<span class="line">            client<span class="token punctuation">.</span><span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token punctuation">}</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">while</span> <span class="token punctuation">(</span><span class="token operator">!</span>shutdown<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>this_thread<span class="token double-colon punctuation">::</span><span class="token function">sleep_for</span><span class="token punctuation">(</span>std<span class="token double-colon punctuation">::</span>chrono<span class="token double-colon punctuation">::</span><span class="token function">seconds</span><span class="token punctuation">(</span><span class="token number">1</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Stop</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    service_thread<span class="token punctuation">.</span><span class="token function">join</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> <span class="token number">0</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div></div></template>


