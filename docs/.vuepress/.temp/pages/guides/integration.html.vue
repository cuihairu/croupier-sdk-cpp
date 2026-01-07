<template><div><h1 id="croupier-c-sdk-集成指南" tabindex="-1"><a class="header-anchor" href="#croupier-c-sdk-集成指南"><span>Croupier C++ SDK 集成指南</span></a></h1>
<p>本指南提供完整的 Croupier C++ SDK 集成步骤，帮助开发者快速接入游戏后端平台。</p>
<h2 id="目录" tabindex="-1"><a class="header-anchor" href="#目录"><span>目录</span></a></h2>
<ul>
<li><a href="#%E5%BF%AB%E9%80%9F%E5%BC%80%E5%A7%8B">快速开始</a></li>
<li><a href="#%E6%A0%B8%E5%BF%83%E6%A6%82%E5%BF%B5">核心概念</a></li>
<li><a href="#%E5%AE%8C%E6%95%B4%E6%8E%A5%E5%8F%A3%E5%8F%82%E8%80%83">完整接口参考</a></li>
<li><a href="#%E9%85%8D%E7%BD%AE%E8%AF%B4%E6%98%8E">配置说明</a></li>
<li><a href="#%E7%94%9F%E4%BA%A7%E9%83%A8%E7%BD%B2">生产部署</a></li>
<li><a href="#%E6%95%85%E9%9A%9C%E6%8E%92%E6%9F%A5">故障排查</a></li>
</ul>
<hr>
<h2 id="快速开始" tabindex="-1"><a class="header-anchor" href="#快速开始"><span>快速开始</span></a></h2>
<h3 id="_1-安装依赖" tabindex="-1"><a class="header-anchor" href="#_1-安装依赖"><span>1. 安装依赖</span></a></h3>
<p><strong>系统要求：</strong></p>
<ul>
<li>64位操作系统 (Windows x64 / Linux x64 / macOS x64 or ARM64)</li>
<li>C++17 编译器（GCC 8+, Clang 10+, MSVC 2019+）</li>
<li>CMake 3.20+</li>
<li>vcpkg（推荐）</li>
</ul>
<p><strong>Linux/macOS:</strong></p>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 安装构建工具</span></span>
<span class="line"><span class="token function">sudo</span> <span class="token function">apt-get</span> <span class="token function">install</span> build-essential cmake ninja-build  <span class="token comment"># Linux</span></span>
<span class="line">brew <span class="token function">install</span> cmake ninja                                 <span class="token comment"># macOS</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 克隆仓库</span></span>
<span class="line"><span class="token function">git</span> clone https://github.com/cuihairu/croupier-sdk-cpp.git</span>
<span class="line"><span class="token builtin class-name">cd</span> croupier-sdk-cpp</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 配置构建</span></span>
<span class="line">cmake <span class="token parameter variable">-B</span> build <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-DCMAKE_BUILD_TYPE</span><span class="token operator">=</span>Release <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-DCMAKE_TOOLCHAIN_FILE</span><span class="token operator">=</span>./cmake/vcpkg-bootstrap.cmake <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-DVCPKG_OVERLAY_PORTS</span><span class="token operator">=</span>./vcpkg-overlays <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-DVCPKG_OVERLAY_TRIPLETS</span><span class="token operator">=</span>./vcpkg-overlays/triplets</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 构建</span></span>
<span class="line">cmake <span class="token parameter variable">--build</span> build <span class="token parameter variable">--parallel</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><p><strong>Windows:</strong></p>
<div class="language-powershell line-numbers-mode" data-highlighter="prismjs" data-ext="powershell"><pre v-pre><code class="language-powershell"><span class="line"><span class="token comment"># 克隆仓库</span></span>
<span class="line">git clone https:<span class="token operator">/</span><span class="token operator">/</span>github<span class="token punctuation">.</span>com/cuihairu/croupier-sdk-<span class="token function">cpp</span><span class="token punctuation">.</span>git</span>
<span class="line">cd croupier-sdk-<span class="token function">cpp</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 配置构建 (使用 Visual Studio 2022)</span></span>
<span class="line">cmake <span class="token operator">-</span>B build <span class="token operator">-</span>G <span class="token string">"Visual Studio 17 2022"</span> `</span>
<span class="line">  <span class="token operator">-</span>DCMAKE_TOOLCHAIN_FILE=<span class="token punctuation">.</span><span class="token operator">/</span>cmake/vcpkg-bootstrap<span class="token punctuation">.</span>cmake `</span>
<span class="line">  <span class="token operator">-</span>DVCPKG_OVERLAY_PORTS=<span class="token punctuation">.</span><span class="token operator">/</span>vcpkg-overlays</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 构建</span></span>
<span class="line">cmake <span class="token operator">--</span>build build <span class="token operator">--</span>config Release</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="_2-最小集成示例" tabindex="-1"><a class="header-anchor" href="#_2-最小集成示例"><span>2. 最小集成示例</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">"croupier/sdk/croupier_client.h"</span></span></span>
<span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">&lt;iostream></span></span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">using</span> <span class="token keyword">namespace</span> croupier<span class="token double-colon punctuation">::</span>sdk<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 定义函数处理器</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>string <span class="token function">MyGameHandler</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> context<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 处理游戏逻辑</span></span>
<span class="line">    <span class="token keyword">return</span> <span class="token raw-string string">R"({"status":"success","data":"processed"})"</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">int</span> <span class="token function">main</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 1. 配置客户端</span></span>
<span class="line">    ClientConfig config<span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"my-game"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"production"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"agent.croupier.internal:19090"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>insecure <span class="token operator">=</span> <span class="token boolean">false</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>cert_file <span class="token operator">=</span> <span class="token string">"/etc/tls/client.crt"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>key_file <span class="token operator">=</span> <span class="token string">"/etc/tls/client.key"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>ca_file <span class="token operator">=</span> <span class="token string">"/etc/tls/ca.crt"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 2. 创建客户端</span></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 3. 注册函数</span></span>
<span class="line">    FunctionDescriptor desc<span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>id <span class="token operator">=</span> <span class="token string">"game.action"</span><span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>version <span class="token operator">=</span> <span class="token string">"1.0.0"</span><span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>category <span class="token operator">=</span> <span class="token string">"gameplay"</span><span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>risk <span class="token operator">=</span> <span class="token string">"low"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">RegisterFunction</span><span class="token punctuation">(</span>desc<span class="token punctuation">,</span> MyGameHandler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 4. 连接并启动服务</span></span>
<span class="line">    <span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token operator">!</span>client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>cerr <span class="token operator">&lt;&lt;</span> <span class="token string">"连接失败\n"</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token keyword">return</span> <span class="token number">1</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>  <span class="token comment">// 阻塞运行</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> <span class="token number">0</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h2 id="核心概念" tabindex="-1"><a class="header-anchor" href="#核心概念"><span>核心概念</span></a></h2>
<h3 id="客户端-client" tabindex="-1"><a class="header-anchor" href="#客户端-client"><span>客户端 (Client)</span></a></h3>
<p>客户端负责注册和管理游戏函数，接收来自 Agent 的调用请求。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><h3 id="调用器-invoker" tabindex="-1"><a class="header-anchor" href="#调用器-invoker"><span>调用器 (Invoker)</span></a></h3>
<p>调用器用于主动调用远程函数（可选）。</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">CroupierInvoker <span class="token function">invoker</span><span class="token punctuation">(</span>invoker_config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>string result <span class="token operator">=</span> invoker<span class="token punctuation">.</span><span class="token function">Invoke</span><span class="token punctuation">(</span><span class="token string">"remote.function"</span><span class="token punctuation">,</span> payload<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="函数描述符-functiondescriptor" tabindex="-1"><a class="header-anchor" href="#函数描述符-functiondescriptor"><span>函数描述符 (FunctionDescriptor)</span></a></h3>
<p>描述函数的元数据：</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">struct</span> <span class="token class-name">FunctionDescriptor</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string id<span class="token punctuation">;</span>           <span class="token comment">// 函数唯一标识 (如 "player.ban")</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string version<span class="token punctuation">;</span>      <span class="token comment">// 版本号 (如 "1.0.0")</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string category<span class="token punctuation">;</span>     <span class="token comment">// 分类 (如 "gameplay", "inventory")</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string risk<span class="token punctuation">;</span>         <span class="token comment">// 风险级别 ("low", "medium", "high")</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string entity<span class="token punctuation">;</span>       <span class="token comment">// 关联实体 (如 "player", "item")</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string operation<span class="token punctuation">;</span>    <span class="token comment">// 操作类型 ("create", "read", "update", "delete")</span></span>
<span class="line">    <span class="token keyword">bool</span> enabled <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span>      <span class="token comment">// 是否启用</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="虚拟对象-virtualobject" tabindex="-1"><a class="header-anchor" href="#虚拟对象-virtualobject"><span>虚拟对象 (VirtualObject)</span></a></h3>
<p>将 CRUD 操作映射到函数：</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">VirtualObjectDescriptor player<span class="token punctuation">;</span></span>
<span class="line">player<span class="token punctuation">.</span>id <span class="token operator">=</span> <span class="token string">"player"</span><span class="token punctuation">;</span></span>
<span class="line">player<span class="token punctuation">.</span>operations <span class="token operator">=</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"create"</span><span class="token punctuation">,</span> <span class="token string">"player.create"</span><span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"read"</span><span class="token punctuation">,</span> <span class="token string">"player.get"</span><span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"update"</span><span class="token punctuation">,</span> <span class="token string">"player.update"</span><span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token punctuation">{</span><span class="token string">"delete"</span><span class="token punctuation">,</span> <span class="token string">"player.delete"</span><span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="组件-component" tabindex="-1"><a class="header-anchor" href="#组件-component"><span>组件 (Component)</span></a></h3>
<p>包含多个虚拟对象和函数的可分发单元：</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">ComponentDescriptor component<span class="token punctuation">;</span></span>
<span class="line">component<span class="token punctuation">.</span>id <span class="token operator">=</span> <span class="token string">"economy-system"</span><span class="token punctuation">;</span></span>
<span class="line">component<span class="token punctuation">.</span>entities<span class="token punctuation">.</span><span class="token function">push_back</span><span class="token punctuation">(</span>wallet_object<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">component<span class="token punctuation">.</span>functions<span class="token punctuation">.</span><span class="token function">push_back</span><span class="token punctuation">(</span>trade_function<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h2 id="完整接口参考" tabindex="-1"><a class="header-anchor" href="#完整接口参考"><span>完整接口参考</span></a></h2>
<h3 id="croupierclient-接口" tabindex="-1"><a class="header-anchor" href="#croupierclient-接口"><span>CroupierClient 接口</span></a></h3>
<h4 id="注册相关" tabindex="-1"><a class="header-anchor" href="#注册相关"><span>注册相关</span></a></h4>
<table>
<thead>
<tr>
<th>接口</th>
<th>说明</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>RegisterFunction(const FunctionDescriptor&amp;, FunctionHandler)</code></td>
<td>注册单个函数</td>
</tr>
<tr>
<td><code v-pre>RegisterVirtualObject(const VirtualObjectDescriptor&amp;, HandlerMap)</code></td>
<td>注册虚拟对象</td>
</tr>
<tr>
<td><code v-pre>RegisterComponent(const ComponentDescriptor&amp;)</code></td>
<td>注册组件</td>
</tr>
<tr>
<td><code v-pre>LoadComponentFromFile(const std::string&amp;)</code></td>
<td>从文件加载组件</td>
</tr>
</tbody>
</table>
<h4 id="查询相关" tabindex="-1"><a class="header-anchor" href="#查询相关"><span>查询相关</span></a></h4>
<table>
<thead>
<tr>
<th>接口</th>
<th>说明</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>GetRegisteredObjects()</code></td>
<td>获取已注册的虚拟对象列表</td>
</tr>
<tr>
<td><code v-pre>GetRegisteredComponents()</code></td>
<td>获取已注册的组件列表</td>
</tr>
<tr>
<td><code v-pre>GetLocalAddress()</code></td>
<td>获取本地服务地址</td>
</tr>
</tbody>
</table>
<h4 id="取消注册" tabindex="-1"><a class="header-anchor" href="#取消注册"><span>取消注册</span></a></h4>
<table>
<thead>
<tr>
<th>接口</th>
<th>说明</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>UnregisterVirtualObject(const std::string&amp;)</code></td>
<td>取消注册虚拟对象</td>
</tr>
<tr>
<td><code v-pre>UnregisterComponent(const std::string&amp;)</code></td>
<td>取消注册组件</td>
</tr>
</tbody>
</table>
<h4 id="生命周期" tabindex="-1"><a class="header-anchor" href="#生命周期"><span>生命周期</span></a></h4>
<table>
<thead>
<tr>
<th>接口</th>
<th>说明</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>Connect()</code></td>
<td>连接到 Agent</td>
</tr>
<tr>
<td><code v-pre>Serve()</code></td>
<td>启动服务循环（阻塞）</td>
</tr>
<tr>
<td><code v-pre>Stop()</code></td>
<td>停止服务</td>
</tr>
<tr>
<td><code v-pre>Close()</code></td>
<td>完全关闭客户端</td>
</tr>
</tbody>
</table>
<h3 id="croupierinvoker-接口" tabindex="-1"><a class="header-anchor" href="#croupierinvoker-接口"><span>CroupierInvoker 接口</span></a></h3>
<table>
<thead>
<tr>
<th>接口</th>
<th>说明</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>Connect()</code></td>
<td>连接到服务器</td>
</tr>
<tr>
<td><code v-pre>Invoke(function_id, payload, options)</code></td>
<td>同步调用</td>
</tr>
<tr>
<td><code v-pre>StartJob(function_id, payload, options)</code></td>
<td>启动异步作业</td>
</tr>
<tr>
<td><code v-pre>StreamJob(job_id)</code></td>
<td>流式获取作业事件</td>
</tr>
<tr>
<td><code v-pre>CancelJob(job_id)</code></td>
<td>取消作业</td>
</tr>
<tr>
<td><code v-pre>SetSchema(function_id, schema)</code></td>
<td>设置验证模式</td>
</tr>
<tr>
<td><code v-pre>Close()</code></td>
<td>关闭连接</td>
</tr>
</tbody>
</table>
<hr>
<h2 id="配置说明" tabindex="-1"><a class="header-anchor" href="#配置说明"><span>配置说明</span></a></h2>
<h3 id="clientconfig-完整参数" tabindex="-1"><a class="header-anchor" href="#clientconfig-完整参数"><span>ClientConfig 完整参数</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">struct</span> <span class="token class-name">ClientConfig</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// === 连接配置 ===</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span>  <span class="token comment">// Agent 地址</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string local_listen <span class="token operator">=</span> <span class="token string">"127.0.0.1:0"</span><span class="token punctuation">;</span>    <span class="token comment">// 本地监听地址</span></span>
<span class="line">    <span class="token keyword">bool</span> insecure <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span>                         <span class="token comment">// 是否禁用 TLS</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// === 身份配置 ===</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string game_id<span class="token punctuation">;</span>          <span class="token comment">// 游戏标识 (必填)</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">;</span> <span class="token comment">// 环境 (development/staging/production)</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string service_id <span class="token operator">=</span> <span class="token string">"cpp-service"</span><span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string service_version <span class="token operator">=</span> <span class="token string">"1.0.0"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// === TLS 配置 (insecure=false 时必填) ===</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string cert_file<span class="token punctuation">;</span>   <span class="token comment">// 客户端证书</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string key_file<span class="token punctuation">;</span>    <span class="token comment">// 客户端私钥</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string ca_file<span class="token punctuation">;</span>     <span class="token comment">// CA 证书</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string server_name<span class="token punctuation">;</span> <span class="token comment">// 服务器名称验证</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// === 认证配置 ===</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string auth_token<span class="token punctuation">;</span>              <span class="token comment">// Bearer Token</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>map<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">></span> headers<span class="token punctuation">;</span> <span class="token comment">// 自定义 HTTP 头</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// === 超时配置 ===</span></span>
<span class="line">    <span class="token keyword">int</span> timeout_seconds <span class="token operator">=</span> <span class="token number">30</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// === 重连配置 ===</span></span>
<span class="line">    <span class="token keyword">bool</span> auto_reconnect <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> reconnect_interval_seconds <span class="token operator">=</span> <span class="token number">5</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> reconnect_max_attempts <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>  <span class="token comment">// 0 = 无限重试</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="环境变量覆盖" tabindex="-1"><a class="header-anchor" href="#环境变量覆盖"><span>环境变量覆盖</span></a></h3>
<p>可通过环境变量覆盖配置：</p>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_AUTO_RECONNECT</span><span class="token operator">=</span>true</span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_RECONNECT_INTERVAL_SECONDS</span><span class="token operator">=</span><span class="token number">5</span></span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_RECONNECT_MAX_ATTEMPTS</span><span class="token operator">=</span><span class="token number">0</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h2 id="生产部署" tabindex="-1"><a class="header-anchor" href="#生产部署"><span>生产部署</span></a></h2>
<h3 id="docker-部署" tabindex="-1"><a class="header-anchor" href="#docker-部署"><span>Docker 部署</span></a></h3>
<p>创建 <code v-pre>Dockerfile</code>:</p>
<div class="language-docker line-numbers-mode" data-highlighter="prismjs" data-ext="docker"><pre v-pre><code class="language-docker"><span class="line"><span class="token instruction"><span class="token keyword">FROM</span> ubuntu:22.04</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 安装依赖</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">RUN</span> apt-get update &amp;&amp; apt-get install -y <span class="token operator">\</span></span>
<span class="line">    ca-certificates <span class="token operator">\</span></span>
<span class="line">    libgrpc++-dev <span class="token operator">\</span></span>
<span class="line">    libprotobuf-dev <span class="token operator">\</span></span>
<span class="line">    &amp;&amp; rm -rf /var/lib/apt/lists/*</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 复制 SDK 文件</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">COPY</span> lib/ /usr/local/lib/</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">COPY</span> include/ /usr/local/include/croupier/</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 复制游戏服务</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">COPY</span> build/game-server /app/game-server</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 设置 TLS 证书路径</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">ENV</span> CROUPIER_CERT_FILE=/etc/tls/client.crt</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">ENV</span> CROUPIER_KEY_FILE=/etc/tls/client.key</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">ENV</span> CROUPIER_CA_FILE=/etc/tls/ca.crt</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 暴露健康检查端口</span></span>
<span class="line"><span class="token instruction"><span class="token keyword">EXPOSE</span> 8080</span></span>
<span class="line"></span>
<span class="line"><span class="token instruction"><span class="token keyword">CMD</span> [<span class="token string">"/app/game-server"</span>]</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="kubernetes-部署" tabindex="-1"><a class="header-anchor" href="#kubernetes-部署"><span>Kubernetes 部署</span></a></h3>
<p>创建 <code v-pre>deployment.yaml</code>:</p>
<div class="language-yaml line-numbers-mode" data-highlighter="prismjs" data-ext="yml"><pre v-pre><code class="language-yaml"><span class="line"><span class="token key atrule">apiVersion</span><span class="token punctuation">:</span> apps/v1</span>
<span class="line"><span class="token key atrule">kind</span><span class="token punctuation">:</span> Deployment</span>
<span class="line"><span class="token key atrule">metadata</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">name</span><span class="token punctuation">:</span> croupier<span class="token punctuation">-</span>game<span class="token punctuation">-</span>server</span>
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
<span class="line">        <span class="token key atrule">image</span><span class="token punctuation">:</span> your<span class="token punctuation">-</span>registry/croupier<span class="token punctuation">-</span>game<span class="token punctuation">-</span>server<span class="token punctuation">:</span>latest</span>
<span class="line">        <span class="token key atrule">ports</span><span class="token punctuation">:</span></span>
<span class="line">        <span class="token punctuation">-</span> <span class="token key atrule">containerPort</span><span class="token punctuation">:</span> <span class="token number">8080</span></span>
<span class="line">          <span class="token key atrule">name</span><span class="token punctuation">:</span> health</span>
<span class="line">        <span class="token key atrule">env</span><span class="token punctuation">:</span></span>
<span class="line">        <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> CROUPIER_AGENT_ADDR</span>
<span class="line">          <span class="token key atrule">value</span><span class="token punctuation">:</span> <span class="token string">"croupier-agent:19090"</span></span>
<span class="line">        <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> CROUPIER_GAME_ID</span>
<span class="line">          <span class="token key atrule">value</span><span class="token punctuation">:</span> <span class="token string">"my-game"</span></span>
<span class="line">        <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> CROUPIER_ENV</span>
<span class="line">          <span class="token key atrule">value</span><span class="token punctuation">:</span> <span class="token string">"production"</span></span>
<span class="line">        <span class="token key atrule">volumeMounts</span><span class="token punctuation">:</span></span>
<span class="line">        <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> tls<span class="token punctuation">-</span>certs</span>
<span class="line">          <span class="token key atrule">mountPath</span><span class="token punctuation">:</span> /etc/tls</span>
<span class="line">          <span class="token key atrule">readOnly</span><span class="token punctuation">:</span> <span class="token boolean important">true</span></span>
<span class="line">        <span class="token key atrule">livenessProbe</span><span class="token punctuation">:</span></span>
<span class="line">          <span class="token key atrule">httpGet</span><span class="token punctuation">:</span></span>
<span class="line">            <span class="token key atrule">path</span><span class="token punctuation">:</span> /health</span>
<span class="line">            <span class="token key atrule">port</span><span class="token punctuation">:</span> <span class="token number">8080</span></span>
<span class="line">          <span class="token key atrule">initialDelaySeconds</span><span class="token punctuation">:</span> <span class="token number">10</span></span>
<span class="line">          <span class="token key atrule">periodSeconds</span><span class="token punctuation">:</span> <span class="token number">30</span></span>
<span class="line">        <span class="token key atrule">readinessProbe</span><span class="token punctuation">:</span></span>
<span class="line">          <span class="token key atrule">httpGet</span><span class="token punctuation">:</span></span>
<span class="line">            <span class="token key atrule">path</span><span class="token punctuation">:</span> /ready</span>
<span class="line">            <span class="token key atrule">port</span><span class="token punctuation">:</span> <span class="token number">8080</span></span>
<span class="line">          <span class="token key atrule">initialDelaySeconds</span><span class="token punctuation">:</span> <span class="token number">5</span></span>
<span class="line">          <span class="token key atrule">periodSeconds</span><span class="token punctuation">:</span> <span class="token number">10</span></span>
<span class="line">      <span class="token key atrule">volumes</span><span class="token punctuation">:</span></span>
<span class="line">      <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> tls<span class="token punctuation">-</span>certs</span>
<span class="line">        <span class="token key atrule">secret</span><span class="token punctuation">:</span></span>
<span class="line">          <span class="token key atrule">secretName</span><span class="token punctuation">:</span> croupier<span class="token punctuation">-</span>tls</span>
<span class="line"><span class="token punctuation">---</span></span>
<span class="line"><span class="token key atrule">apiVersion</span><span class="token punctuation">:</span> v1</span>
<span class="line"><span class="token key atrule">kind</span><span class="token punctuation">:</span> Service</span>
<span class="line"><span class="token key atrule">metadata</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">name</span><span class="token punctuation">:</span> croupier<span class="token punctuation">-</span>game<span class="token punctuation">-</span>server</span>
<span class="line"><span class="token key atrule">spec</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">selector</span><span class="token punctuation">:</span></span>
<span class="line">    <span class="token key atrule">app</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>server</span>
<span class="line">  <span class="token key atrule">ports</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token punctuation">-</span> <span class="token key atrule">port</span><span class="token punctuation">:</span> <span class="token number">80</span></span>
<span class="line">    <span class="token key atrule">targetPort</span><span class="token punctuation">:</span> <span class="token number">8080</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="健康检查端点" tabindex="-1"><a class="header-anchor" href="#健康检查端点"><span>健康检查端点</span></a></h3>
<p>实现健康检查：</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">&lt;micro_httpd.hpp></span></span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">void</span> <span class="token function">startHealthCheckServer</span><span class="token punctuation">(</span><span class="token keyword">int</span> port<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    httpd<span class="token double-colon punctuation">::</span>server <span class="token function">server</span><span class="token punctuation">(</span>port<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    server<span class="token punctuation">[</span><span class="token string">"/health"</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token keyword">auto</span><span class="token operator">&amp;</span> req<span class="token punctuation">,</span> <span class="token keyword">auto</span><span class="token operator">&amp;</span> res<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        res <span class="token operator">=</span> httpd<span class="token double-colon punctuation">::</span><span class="token function">response</span><span class="token punctuation">(</span><span class="token number">200</span><span class="token punctuation">,</span> <span class="token string">"OK"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line">    server<span class="token punctuation">[</span><span class="token string">"/ready"</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token keyword">auto</span><span class="token operator">&amp;</span> req<span class="token punctuation">,</span> <span class="token keyword">auto</span><span class="token operator">&amp;</span> res<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">bool</span> connected <span class="token operator">=</span> client<span class="token punctuation">.</span><span class="token function">IsConnected</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        res <span class="token operator">=</span> httpd<span class="token double-colon punctuation">::</span><span class="token function">response</span><span class="token punctuation">(</span>connected <span class="token operator">?</span> <span class="token number">200</span> <span class="token operator">:</span> <span class="token number">503</span><span class="token punctuation">,</span> connected <span class="token operator">?</span> <span class="token string">"Ready"</span> <span class="token operator">:</span> <span class="token string">"Not Ready"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line">    server<span class="token punctuation">.</span><span class="token function">start</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h2 id="故障排查" tabindex="-1"><a class="header-anchor" href="#故障排查"><span>故障排查</span></a></h2>
<h3 id="连接失败" tabindex="-1"><a class="header-anchor" href="#连接失败"><span>连接失败</span></a></h3>
<p><strong>问题</strong>: 无法连接到 Agent</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token comment">// 检查配置</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"Agent 地址: "</span> <span class="token operator">&lt;&lt;</span> config<span class="token punctuation">.</span>agent_addr <span class="token operator">&lt;&lt;</span> <span class="token char">'\n'</span><span class="token punctuation">;</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"TLS 设置: "</span> <span class="token operator">&lt;&lt;</span> <span class="token punctuation">(</span>config<span class="token punctuation">.</span>insecure <span class="token operator">?</span> <span class="token string">"禁用"</span> <span class="token operator">:</span> <span class="token string">"启用"</span><span class="token punctuation">)</span> <span class="token operator">&lt;&lt;</span> <span class="token char">'\n'</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 检查网络连通性</span></span>
<span class="line"><span class="token function">system</span><span class="token punctuation">(</span><span class="token punctuation">(</span><span class="token string">"ping -c 1 "</span> <span class="token operator">+</span> config<span class="token punctuation">.</span>agent_addr<span class="token punctuation">.</span><span class="token function">substr</span><span class="token punctuation">(</span><span class="token number">0</span><span class="token punctuation">,</span> config<span class="token punctuation">.</span>agent_addr<span class="token punctuation">.</span><span class="token function">find</span><span class="token punctuation">(</span><span class="token char">':'</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">.</span><span class="token function">c_str</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><p><strong>解决方案</strong>:</p>
<ol>
<li>确认 Agent 服务正在运行</li>
<li>检查防火墙规则</li>
<li>验证 TLS 证书路径</li>
</ol>
<h3 id="函数未被调用" tabindex="-1"><a class="header-anchor" href="#函数未被调用"><span>函数未被调用</span></a></h3>
<p><strong>问题</strong>: 函数已注册但从未收到调用</p>
<p><strong>检查清单</strong>:</p>
<ul>
<li>[ ] 函数 ID 与 Agent 侧配置一致</li>
<li>[ ] 函数版本匹配</li>
<li>[ ] 函数已启用 (<code v-pre>enabled = true</code>)</li>
<li>[ ] 客户端已调用 <code v-pre>Serve()</code></li>
<li>[ ] 网络连接正常</li>
</ul>
<h3 id="性能问题" tabindex="-1"><a class="header-anchor" href="#性能问题"><span>性能问题</span></a></h3>
<p><strong>问题</strong>: 响应延迟高</p>
<p><strong>优化建议</strong>:</p>
<ol>
<li>使用 <code v-pre>'\n'</code> 而非 <code v-pre>std::endl</code> 避免频繁刷新缓冲区</li>
<li>启用 gRPC 连接复用</li>
<li>使用异步处理模式</li>
</ol>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token comment">// 异步处理示例</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>string <span class="token function">AsyncHandler</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> context<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 立即返回，异步处理</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span><span class="token function">thread</span><span class="token punctuation">(</span><span class="token punctuation">[</span>payload<span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token function">processAsync</span><span class="token punctuation">(</span>payload<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">.</span><span class="token function">detach</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> <span class="token raw-string string">R"({"status":"accepted","message":"Processing asynchronously"})"</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><hr>
<h2 id="更多资源" tabindex="-1"><a class="header-anchor" href="#更多资源"><span>更多资源</span></a></h2>
<ul>
<li><a href="https://cuihairu.github.io/croupier-sdk-cpp/" target="_blank" rel="noopener noreferrer">完整 API 文档</a></li>
<li><RouteLink to="/examples/">示例代码</RouteLink></li>
<li><RouteLink to="/#%E6%9E%B6%E6%9E%84%E8%AE%BE%E8%AE%A1">架构设计</RouteLink></li>
<li><a href="https://github.com/cuihairu/croupier-sdk-cpp/issues" target="_blank" rel="noopener noreferrer">问题反馈</a></li>
</ul>
</div></template>


