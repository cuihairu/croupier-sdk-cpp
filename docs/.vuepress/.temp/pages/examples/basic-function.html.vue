<template><div><h1 id="基础函数示例" tabindex="-1"><a class="header-anchor" href="#基础函数示例"><span>基础函数示例</span></a></h1>
<p>本示例展示如何注册一个简单的函数。</p>
<h2 id="完整代码" tabindex="-1"><a class="header-anchor" href="#完整代码"><span>完整代码</span></a></h2>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">"croupier/sdk/croupier_client.h"</span></span></span>
<span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">"croupier/sdk/utils/json_utils.h"</span></span></span>
<span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">&lt;iostream></span></span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">using</span> <span class="token keyword">namespace</span> croupier<span class="token double-colon punctuation">::</span>sdk<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 函数处理器</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>string <span class="token function">HelloHandler</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> context<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"Context: "</span> <span class="token operator">&lt;&lt;</span> context <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"Payload: "</span> <span class="token operator">&lt;&lt;</span> payload <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">auto</span> data <span class="token operator">=</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ParseJSON</span><span class="token punctuation">(</span>payload<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string name <span class="token operator">=</span> data<span class="token punctuation">.</span><span class="token function">value</span><span class="token punctuation">(</span><span class="token string">"name"</span><span class="token punctuation">,</span> <span class="token string">"World"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ToJSON</span><span class="token punctuation">(</span><span class="token punctuation">{</span></span>
<span class="line">        <span class="token punctuation">{</span><span class="token string">"message"</span><span class="token punctuation">,</span> <span class="token string">"Hello, "</span> <span class="token operator">+</span> name <span class="token operator">+</span> <span class="token string">"!"</span><span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">        <span class="token punctuation">{</span><span class="token string">"timestamp"</span><span class="token punctuation">,</span> std<span class="token double-colon punctuation">::</span>chrono<span class="token double-colon punctuation">::</span>system_clock<span class="token double-colon punctuation">::</span><span class="token function">now</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">}</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">std<span class="token double-colon punctuation">::</span>string <span class="token function">AddHandler</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> context<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token keyword">auto</span> data <span class="token operator">=</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ParseJSON</span><span class="token punctuation">(</span>payload<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> a <span class="token operator">=</span> data<span class="token punctuation">[</span><span class="token string">"a"</span><span class="token punctuation">]</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">int</span> b <span class="token operator">=</span> data<span class="token punctuation">[</span><span class="token string">"b"</span><span class="token punctuation">]</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ToJSON</span><span class="token punctuation">(</span><span class="token punctuation">{</span></span>
<span class="line">        <span class="token punctuation">{</span><span class="token string">"result"</span><span class="token punctuation">,</span> a <span class="token operator">+</span> b<span class="token punctuation">}</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
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
<span class="line">    FunctionDescriptor hello_desc<span class="token punctuation">;</span></span>
<span class="line">    hello_desc<span class="token punctuation">.</span>id <span class="token operator">=</span> <span class="token string">"hello.world"</span><span class="token punctuation">;</span></span>
<span class="line">    hello_desc<span class="token punctuation">.</span>version <span class="token operator">=</span> <span class="token string">"0.1.0"</span><span class="token punctuation">;</span></span>
<span class="line">    hello_desc<span class="token punctuation">.</span>name <span class="token operator">=</span> <span class="token string">"Hello World"</span><span class="token punctuation">;</span></span>
<span class="line">    hello_desc<span class="token punctuation">.</span>description <span class="token operator">=</span> <span class="token string">"A simple greeting function"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">RegisterFunction</span><span class="token punctuation">(</span>hello_desc<span class="token punctuation">,</span> HelloHandler<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 注册数学函数</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">RegisterFunction</span><span class="token punctuation">(</span></span>
<span class="line">        FunctionDescriptor<span class="token punctuation">{</span><span class="token string">"math.add"</span><span class="token punctuation">,</span> <span class="token string">"0.1.0"</span><span class="token punctuation">,</span> <span class="token string">"Add"</span><span class="token punctuation">,</span> <span class="token string">"Add two numbers"</span><span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">        AddHandler</span>
<span class="line">    <span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 连接并服务</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"Connecting to agent..."</span> <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">if</span> <span class="token punctuation">(</span>client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>cout <span class="token operator">&lt;&lt;</span> <span class="token string">"Connected! Serving..."</span> <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">        client<span class="token punctuation">.</span><span class="token function">Serve</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>  <span class="token comment">// 阻塞</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> <span class="token number">0</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="编译" tabindex="-1"><a class="header-anchor" href="#编译"><span>编译</span></a></h2>
<h3 id="cmakelists-txt" tabindex="-1"><a class="header-anchor" href="#cmakelists-txt"><span>CMakeLists.txt</span></a></h3>
<div class="language-cmake line-numbers-mode" data-highlighter="prismjs" data-ext="cmake"><pre v-pre><code class="language-cmake"><span class="line"><span class="token keyword">cmake_minimum_required</span><span class="token punctuation">(</span><span class="token property">VERSION</span> <span class="token number">3.20</span><span class="token punctuation">)</span></span>
<span class="line"><span class="token keyword">project</span><span class="token punctuation">(</span>basic_function<span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">set</span><span class="token punctuation">(</span><span class="token variable">CMAKE_CXX_STANDARD</span> <span class="token number">17</span><span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">find_package</span><span class="token punctuation">(</span>croupier-sdk REQUIRED<span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">add_executable</span><span class="token punctuation">(</span>basic_function main.cpp<span class="token punctuation">)</span></span>
<span class="line"><span class="token keyword">target_link_libraries</span><span class="token punctuation">(</span>basic_function <span class="token namespace">PRIVATE</span> croupier-<span class="token inserted class-name">sdk::croupier</span>-sdk<span class="token punctuation">)</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="构建命令" tabindex="-1"><a class="header-anchor" href="#构建命令"><span>构建命令</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line">cmake <span class="token parameter variable">-B</span> build <span class="token parameter variable">-DCMAKE_TOOLCHAIN_FILE</span><span class="token operator">=</span>/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake</span>
<span class="line">cmake <span class="token parameter variable">--build</span> build</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="运行" tabindex="-1"><a class="header-anchor" href="#运行"><span>运行</span></a></h2>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line">./build/basic_function</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><h2 id="测试" tabindex="-1"><a class="header-anchor" href="#测试"><span>测试</span></a></h2>
<h3 id="使用-curl-调用" tabindex="-1"><a class="header-anchor" href="#使用-curl-调用"><span>使用 curl 调用</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 调用 hello.world</span></span>
<span class="line"><span class="token function">curl</span> <span class="token parameter variable">-X</span> POST http://localhost:8080/api/v1/functions/hello.world/invoke <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-H</span> <span class="token string">"Content-Type: application/json"</span> <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-H</span> <span class="token string">"X-Game-ID: demo-game"</span> <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-d</span> <span class="token string">'{"name": "Croupier"}'</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 调用 math.add</span></span>
<span class="line"><span class="token function">curl</span> <span class="token parameter variable">-X</span> POST http://localhost:8080/api/v1/functions/math.add/invoke <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-H</span> <span class="token string">"Content-Type: application/json"</span> <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-H</span> <span class="token string">"X-Game-ID: demo-game"</span> <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-d</span> <span class="token string">'{"a": 5, "b": 3}'</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="预期响应" tabindex="-1"><a class="header-anchor" href="#预期响应"><span>预期响应</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token comment">// hello.world</span></span>
<span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"message"</span><span class="token operator">:</span> <span class="token string">"Hello, Croupier!"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"timestamp"</span><span class="token operator">:</span> <span class="token string">"2024-01-01T00:00:00Z"</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// math.add</span></span>
<span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"result"</span><span class="token operator">:</span> <span class="token number">8</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="输出示例" tabindex="-1"><a class="header-anchor" href="#输出示例"><span>输出示例</span></a></h2>
<p>程序运行时输出：</p>
<div class="language-text line-numbers-mode" data-highlighter="prismjs" data-ext="text"><pre v-pre><code class="language-text"><span class="line">Connecting to agent...</span>
<span class="line">Connected! Serving...</span>
<span class="line">Context: {"game_id":"demo-game","env":"development","caller_id":"web-ui"}</span>
<span class="line">Payload: {"name":"Croupier"}</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div></div></template>


