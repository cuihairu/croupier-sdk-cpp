<template><div><h1 id="快速开始" tabindex="-1"><a class="header-anchor" href="#快速开始"><span>快速开始</span></a></h1>
<p>本教程将带你创建第一个使用 Croupier C++ SDK 的应用程序。</p>
<h2 id="前置准备" tabindex="-1"><a class="header-anchor" href="#前置准备"><span>前置准备</span></a></h2>
<p>确保你已经：</p>
<ol>
<li>安装了 <a href="https://github.com/cuihairu/croupier" target="_blank" rel="noopener noreferrer">Croupier Agent</a></li>
<li>完成了 SDK 的 <RouteLink to="/guide/installation.html">安装</RouteLink></li>
</ol>
<h2 id="第一个程序" tabindex="-1"><a class="header-anchor" href="#第一个程序"><span>第一个程序</span></a></h2>
<h3 id="_1-创建项目文件" tabindex="-1"><a class="header-anchor" href="#_1-创建项目文件"><span>1. 创建项目文件</span></a></h3>
<p><code v-pre>main.cpp</code>:</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">"croupier/sdk/croupier_client.h"</span></span></span>
<span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">&lt;iostream></span></span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">using</span> <span class="token keyword">namespace</span> croupier<span class="token double-colon punctuation">::</span>sdk<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 定义函数处理器</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>string <span class="token function">HelloHandler</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> context<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"Context: "</span> <span class="token operator">&lt;&lt;</span> context <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"Payload: "</span> <span class="token operator">&lt;&lt;</span> payload <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">return</span> <span class="token raw-string string">R"({"message": "Hello from C++ SDK!"})"</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">int</span> <span class="token function">main</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 配置客户端</span></span>
<span class="line">    ClientConfig config<span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"demo-game"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 创建客户端</span></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 注册函数</span></span>
<span class="line">    FunctionDescriptor desc<span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>id <span class="token operator">=</span> <span class="token string">"hello.world"</span><span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>version <span class="token operator">=</span> <span class="token string">"0.1.0"</span><span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>name <span class="token operator">=</span> <span class="token string">"Hello World"</span><span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>description <span class="token operator">=</span> <span class="token string">"A simple hello world function"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">RegisterFunction</span><span class="token punctuation">(</span>desc<span class="token punctuation">,</span> HelloHandler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 连接并服务</span></span>
<span class="line">    <span class="token keyword">if</span> <span class="token punctuation">(</span>client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"Connected to agent!"</span> <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">        client<span class="token punctuation">.</span><span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span> <span class="token comment">// 阻塞运行</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> <span class="token number">0</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="_2-创建-cmakelists-txt" tabindex="-1"><a class="header-anchor" href="#_2-创建-cmakelists-txt"><span>2. 创建 CMakeLists.txt</span></a></h3>
<div class="language-cmake line-numbers-mode" data-highlighter="prismjs" data-ext="cmake"><pre v-pre><code class="language-cmake"><span class="line"><span class="token keyword">cmake_minimum_required</span><span class="token punctuation">(</span><span class="token property">VERSION</span> <span class="token number">3.20</span><span class="token punctuation">)</span></span>
<span class="line"><span class="token keyword">project</span><span class="token punctuation">(</span>HelloCroupier<span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">set</span><span class="token punctuation">(</span><span class="token variable">CMAKE_CXX_STANDARD</span> <span class="token number">17</span><span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 查找 Croupier SDK</span></span>
<span class="line"><span class="token keyword">find_package</span><span class="token punctuation">(</span>croupier-sdk REQUIRED<span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">add_executable</span><span class="token punctuation">(</span>hello-croupier main.cpp<span class="token punctuation">)</span></span>
<span class="line"><span class="token keyword">target_link_libraries</span><span class="token punctuation">(</span>hello-croupier <span class="token namespace">PRIVATE</span> croupier-<span class="token inserted class-name">sdk::croupier</span>-sdk<span class="token punctuation">)</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="_3-构建和运行" tabindex="-1"><a class="header-anchor" href="#_3-构建和运行"><span>3. 构建和运行</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 配置</span></span>
<span class="line">cmake <span class="token parameter variable">-B</span> build <span class="token parameter variable">-DCMAKE_TOOLCHAIN_FILE</span><span class="token operator">=</span>/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 构建</span></span>
<span class="line">cmake <span class="token parameter variable">--build</span> build</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 运行（确保 Agent 已启动）</span></span>
<span class="line">./build/hello-croupier</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="虚拟对象示例" tabindex="-1"><a class="header-anchor" href="#虚拟对象示例"><span>虚拟对象示例</span></a></h2>
<p>注册一个虚拟对象（如钱包）：</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">"croupier/sdk/croupier_client.h"</span></span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 钱包获取处理器</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>string <span class="token function">WalletGetHandler</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> context<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 解析 payload 获取玩家 ID</span></span>
<span class="line">    <span class="token keyword">auto</span> data <span class="token operator">=</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ParseJSON</span><span class="token punctuation">(</span>payload<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string player_id <span class="token operator">=</span> data<span class="token punctuation">[</span><span class="token string">"player_id"</span><span class="token punctuation">]</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 返回钱包信息</span></span>
<span class="line">    <span class="token keyword">return</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ToJSON</span><span class="token punctuation">(</span><span class="token punctuation">{</span></span>
<span class="line">        <span class="token punctuation">{</span><span class="token string">"player_id"</span><span class="token punctuation">,</span> player_id<span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">        <span class="token punctuation">{</span><span class="token string">"balance"</span><span class="token punctuation">,</span> <span class="token number">1000</span><span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">        <span class="token punctuation">{</span><span class="token string">"currency"</span><span class="token punctuation">,</span> <span class="token string">"gold"</span><span class="token punctuation">}</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 转账处理器</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>string <span class="token function">WalletTransferHandler</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> context<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token keyword">auto</span> data <span class="token operator">=</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ParseJSON</span><span class="token punctuation">(</span>payload<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token comment">// 执行转账逻辑...</span></span>
<span class="line">    <span class="token keyword">return</span> <span class="token raw-string string">R"({"success": true})"</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">int</span> <span class="token function">main</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    ClientConfig config<span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"mmorpg-demo"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"development"</span><span class="token punctuation">;</span></span>
<span class="line">    config<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 注册虚拟对象</span></span>
<span class="line">    VirtualObjectDescriptor wallet_entity<span class="token punctuation">;</span></span>
<span class="line">    wallet_entity<span class="token punctuation">.</span>id <span class="token operator">=</span> <span class="token string">"wallet.entity"</span><span class="token punctuation">;</span></span>
<span class="line">    wallet_entity<span class="token punctuation">.</span>version <span class="token operator">=</span> <span class="token string">"0.1.0"</span><span class="token punctuation">;</span></span>
<span class="line">    wallet_entity<span class="token punctuation">.</span>name <span class="token operator">=</span> <span class="token string">"Wallet"</span><span class="token punctuation">;</span></span>
<span class="line">    wallet_entity<span class="token punctuation">.</span>description <span class="token operator">=</span> <span class="token string">"Player wallet entity"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 定义操作</span></span>
<span class="line">    wallet_entity<span class="token punctuation">.</span>operations<span class="token punctuation">[</span><span class="token string">"get"</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token string">"wallet.get"</span><span class="token punctuation">;</span></span>
<span class="line">    wallet_entity<span class="token punctuation">.</span>operations<span class="token punctuation">[</span><span class="token string">"transfer"</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token string">"wallet.transfer"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 注册操作处理器</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>map<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> FunctionHandler<span class="token operator">></span> handlers<span class="token punctuation">;</span></span>
<span class="line">    handlers<span class="token punctuation">[</span><span class="token string">"wallet.get"</span><span class="token punctuation">]</span> <span class="token operator">=</span> WalletGetHandler<span class="token punctuation">;</span></span>
<span class="line">    handlers<span class="token punctuation">[</span><span class="token string">"wallet.transfer"</span><span class="token punctuation">]</span> <span class="token operator">=</span> WalletTransferHandler<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">RegisterVirtualObject</span><span class="token punctuation">(</span>wallet_entity<span class="token punctuation">,</span> handlers<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> <span class="token number">0</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="使用配置文件" tabindex="-1"><a class="header-anchor" href="#使用配置文件"><span>使用配置文件</span></a></h2>
<h3 id="创建配置文件-config-json" tabindex="-1"><a class="header-anchor" href="#创建配置文件-config-json"><span>创建配置文件 <code v-pre>config.json</code>:</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"demo-game"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"env"</span><span class="token operator">:</span> <span class="token string">"development"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"service_id"</span><span class="token operator">:</span> <span class="token string">"backend-service"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"agent_addr"</span><span class="token operator">:</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"insecure"</span><span class="token operator">:</span> <span class="token boolean">true</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"timeout_seconds"</span><span class="token operator">:</span> <span class="token number">30</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="使用配置加载器" tabindex="-1"><a class="header-anchor" href="#使用配置加载器"><span>使用配置加载器：</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">"croupier/sdk/config/client_config_loader.h"</span></span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">int</span> <span class="token function">main</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 从文件加载配置</span></span>
<span class="line">    ClientConfigLoader loader<span class="token punctuation">;</span></span>
<span class="line">    ClientConfig config <span class="token operator">=</span> loader<span class="token punctuation">.</span><span class="token function">LoadFromFile</span><span class="token punctuation">(</span><span class="token string">"./config.json"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 验证配置</span></span>
<span class="line">    <span class="token keyword">auto</span> errors <span class="token operator">=</span> loader<span class="token punctuation">.</span><span class="token function">ValidateConfig</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token operator">!</span>errors<span class="token punctuation">.</span><span class="token function">empty</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">for</span> <span class="token punctuation">(</span><span class="token keyword">const</span> <span class="token keyword">auto</span><span class="token operator">&amp;</span> error <span class="token operator">:</span> errors<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">            std<span class="token double-colon punctuation">::</span>cerr <span class="token operator">&lt;&lt;</span> <span class="token string">"Config error: "</span> <span class="token operator">&lt;&lt;</span> error <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">        <span class="token punctuation">}</span></span>
<span class="line">        <span class="token keyword">return</span> <span class="token number">1</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token comment">// ... 继续使用客户端</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="下一步" tabindex="-1"><a class="header-anchor" href="#下一步"><span>下一步</span></a></h2>
<ul>
<li><RouteLink to="/guide/building.html">构建指南</RouteLink> - 了解更多构建选项</li>
<li><RouteLink to="/api/">API 参考</RouteLink> - 详细 API 文档</li>
<li><RouteLink to="/examples/">示例</RouteLink> - 更多使用示例</li>
</ul>
</div></template>


