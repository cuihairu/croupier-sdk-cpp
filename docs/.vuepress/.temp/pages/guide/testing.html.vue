<template><div><h1 id="测试指南" tabindex="-1"><a class="header-anchor" href="#测试指南"><span>测试指南</span></a></h1>
<p>本指南介绍如何测试使用 Croupier C++ SDK 的应用程序。</p>
<h2 id="单元测试" tabindex="-1"><a class="header-anchor" href="#单元测试"><span>单元测试</span></a></h2>
<h3 id="使用-google-test" tabindex="-1"><a class="header-anchor" href="#使用-google-test"><span>使用 Google Test</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">&lt;gtest/gtest.h></span></span></span>
<span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">"croupier/sdk/croupier_client.h"</span></span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">class</span> <span class="token class-name">CroupierClientTest</span> <span class="token operator">:</span> <span class="token base-clause"><span class="token keyword">public</span> <span class="token double-colon punctuation">::</span>testing<span class="token double-colon punctuation">::</span><span class="token class-name">Test</span></span> <span class="token punctuation">{</span></span>
<span class="line"><span class="token keyword">protected</span><span class="token operator">:</span></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">SetUp</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token keyword">override</span> <span class="token punctuation">{</span></span>
<span class="line">        config_<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"test-game"</span><span class="token punctuation">;</span></span>
<span class="line">        config_<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"test"</span><span class="token punctuation">;</span></span>
<span class="line">        config_<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span></span>
<span class="line">        config_<span class="token punctuation">.</span>insecure <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    ClientConfig config_<span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token function">TEST_F</span><span class="token punctuation">(</span>CroupierClientTest<span class="token punctuation">,</span> RegisterFunction<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config_<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    FunctionDescriptor desc<span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>id <span class="token operator">=</span> <span class="token string">"test.function"</span><span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>version <span class="token operator">=</span> <span class="token string">"0.1.0"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">bool</span> result <span class="token operator">=</span> client<span class="token punctuation">.</span><span class="token function">RegisterFunction</span><span class="token punctuation">(</span>desc<span class="token punctuation">,</span> <span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token keyword">auto</span> ctx<span class="token punctuation">,</span> <span class="token keyword">auto</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">return</span> <span class="token raw-string string">R"({"success": true})"</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token function">EXPECT_TRUE</span><span class="token punctuation">(</span>result<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token function">TEST_F</span><span class="token punctuation">(</span>CroupierClientTest<span class="token punctuation">,</span> ParseJSON<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string json <span class="token operator">=</span> <span class="token raw-string string">R"({"key": "value"})"</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">auto</span> result <span class="token operator">=</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ParseJSON</span><span class="token punctuation">(</span>json<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token function">EXPECT_TRUE</span><span class="token punctuation">(</span>result<span class="token punctuation">.</span><span class="token function">contains</span><span class="token punctuation">(</span><span class="token string">"key"</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token function">EXPECT_EQ</span><span class="token punctuation">(</span>result<span class="token punctuation">[</span><span class="token string">"key"</span><span class="token punctuation">]</span><span class="token punctuation">,</span> <span class="token string">"value"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token function">TEST_F</span><span class="token punctuation">(</span>CroupierClientTest<span class="token punctuation">,</span> HandlerFunction<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token keyword">auto</span> handler <span class="token operator">=</span> <span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> ctx<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token operator">-></span> std<span class="token double-colon punctuation">::</span>string <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">auto</span> data <span class="token operator">=</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ParseJSON</span><span class="token punctuation">(</span>payload<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token keyword">int</span> a <span class="token operator">=</span> data<span class="token punctuation">[</span><span class="token string">"a"</span><span class="token punctuation">]</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token keyword">int</span> b <span class="token operator">=</span> data<span class="token punctuation">[</span><span class="token string">"b"</span><span class="token punctuation">]</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token keyword">return</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ToJSON</span><span class="token punctuation">(</span><span class="token punctuation">{</span><span class="token punctuation">{</span><span class="token string">"result"</span><span class="token punctuation">,</span> a <span class="token operator">+</span> b<span class="token punctuation">}</span><span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string result <span class="token operator">=</span> <span class="token function">handler</span><span class="token punctuation">(</span><span class="token string">""</span><span class="token punctuation">,</span> <span class="token raw-string string">R"({"a": 2, "b": 3})"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">auto</span> response <span class="token operator">=</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ParseJSON</span><span class="token punctuation">(</span>result<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token function">EXPECT_EQ</span><span class="token punctuation">(</span>response<span class="token punctuation">[</span><span class="token string">"result"</span><span class="token punctuation">]</span><span class="token punctuation">,</span> <span class="token number">5</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="运行测试" tabindex="-1"><a class="header-anchor" href="#运行测试"><span>运行测试</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 启用测试构建</span></span>
<span class="line">./scripts/build.sh <span class="token parameter variable">--tests</span> ON</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 运行所有测试</span></span>
<span class="line"><span class="token builtin class-name">cd</span> build</span>
<span class="line">ctest</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 运行特定测试</span></span>
<span class="line">./tests/unit_tests <span class="token parameter variable">--gtest_filter</span><span class="token operator">=</span><span class="token string">"CroupierClientTest.*"</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 详细输出</span></span>
<span class="line">./tests/unit_tests <span class="token parameter variable">--gtest_filter</span><span class="token operator">=</span><span class="token string">"*"</span> <span class="token parameter variable">--gtest_print_time</span><span class="token operator">=</span><span class="token number">1</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="mock-测试" tabindex="-1"><a class="header-anchor" href="#mock-测试"><span>Mock 测试</span></a></h2>
<h3 id="mock-agent" tabindex="-1"><a class="header-anchor" href="#mock-agent"><span>Mock Agent</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">class</span> <span class="token class-name">MockAgent</span> <span class="token punctuation">{</span></span>
<span class="line"><span class="token keyword">public</span><span class="token operator">:</span></span>
<span class="line">    <span class="token function">MockAgent</span><span class="token punctuation">(</span><span class="token keyword">int</span> port<span class="token punctuation">)</span> <span class="token operator">:</span> <span class="token function">port_</span><span class="token punctuation">(</span>port<span class="token punctuation">)</span> <span class="token punctuation">{</span><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">Start</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        server_thread_ <span class="token operator">=</span> std<span class="token double-colon punctuation">::</span><span class="token function">thread</span><span class="token punctuation">(</span><span class="token punctuation">[</span><span class="token keyword">this</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">            <span class="token comment">// 启动简单的 gRPC 测试服务器</span></span>
<span class="line">            <span class="token comment">// ...</span></span>
<span class="line">        <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">Stop</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token comment">// 停止服务器</span></span>
<span class="line">        server_thread_<span class="token punctuation">.</span><span class="token function">join</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">SetResponse</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> response<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        mock_response_ <span class="token operator">=</span> response<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">private</span><span class="token operator">:</span></span>
<span class="line">    <span class="token keyword">int</span> port_<span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>thread server_thread_<span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string mock_response_<span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 使用 Mock</span></span>
<span class="line"><span class="token function">TEST_F</span><span class="token punctuation">(</span>CroupierClientTest<span class="token punctuation">,</span> ConnectToMockAgent<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    MockAgent <span class="token function">mock</span><span class="token punctuation">(</span><span class="token number">19090</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    mock<span class="token punctuation">.</span><span class="token function">Start</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config_<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token function">EXPECT_TRUE</span><span class="token punctuation">(</span>client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    mock<span class="token punctuation">.</span><span class="token function">Stop</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="函数-mock" tabindex="-1"><a class="header-anchor" href="#函数-mock"><span>函数 Mock</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">class</span> <span class="token class-name">MockFunctionHandler</span> <span class="token punctuation">{</span></span>
<span class="line"><span class="token keyword">public</span><span class="token operator">:</span></span>
<span class="line">    <span class="token function">MOCK_METHOD</span><span class="token punctuation">(</span>std<span class="token double-colon punctuation">::</span>string<span class="token punctuation">,</span> Handle<span class="token punctuation">,</span> <span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span><span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string <span class="token keyword">operator</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> ctx<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">return</span> <span class="token function">Handle</span><span class="token punctuation">(</span>ctx<span class="token punctuation">,</span> payload<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">using</span> <span class="token double-colon punctuation">::</span>testing<span class="token double-colon punctuation">::</span>Return<span class="token punctuation">;</span></span>
<span class="line"><span class="token keyword">using</span> <span class="token double-colon punctuation">::</span>testing<span class="token double-colon punctuation">::</span>_<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token function">TEST_F</span><span class="token punctuation">(</span>CroupierClientTest<span class="token punctuation">,</span> MockHandler<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    MockFunctionHandler mock_handler<span class="token punctuation">;</span></span>
<span class="line">    <span class="token function">EXPECT_CALL</span><span class="token punctuation">(</span>mock_handler<span class="token punctuation">,</span> <span class="token function">Handle</span><span class="token punctuation">(</span>_<span class="token punctuation">,</span> _<span class="token punctuation">)</span><span class="token punctuation">)</span></span>
<span class="line">        <span class="token punctuation">.</span><span class="token function">WillOnce</span><span class="token punctuation">(</span><span class="token function">Return</span><span class="token punctuation">(</span><span class="token raw-string string">R"({"result": "mocked"})"</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string result <span class="token operator">=</span> <span class="token function">mock_handler</span><span class="token punctuation">(</span><span class="token string">""</span><span class="token punctuation">,</span> <span class="token string">"{}"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">auto</span> response <span class="token operator">=</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ParseJSON</span><span class="token punctuation">(</span>result<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token function">EXPECT_EQ</span><span class="token punctuation">(</span>response<span class="token punctuation">[</span><span class="token string">"result"</span><span class="token punctuation">]</span><span class="token punctuation">,</span> <span class="token string">"mocked"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="集成测试" tabindex="-1"><a class="header-anchor" href="#集成测试"><span>集成测试</span></a></h2>
<h3 id="测试场景" tabindex="-1"><a class="header-anchor" href="#测试场景"><span>测试场景</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">class</span> <span class="token class-name">IntegrationTest</span> <span class="token operator">:</span> <span class="token base-clause"><span class="token keyword">public</span> <span class="token double-colon punctuation">::</span>testing<span class="token double-colon punctuation">::</span><span class="token class-name">Test</span></span> <span class="token punctuation">{</span></span>
<span class="line"><span class="token keyword">protected</span><span class="token operator">:</span></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">SetUp</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token keyword">override</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token comment">// 启动测试 Agent</span></span>
<span class="line">        <span class="token function">StartTestAgent</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">        <span class="token comment">// 配置客户端</span></span>
<span class="line">        config_<span class="token punctuation">.</span>game_id <span class="token operator">=</span> <span class="token string">"integration-test"</span><span class="token punctuation">;</span></span>
<span class="line">        config_<span class="token punctuation">.</span>env <span class="token operator">=</span> <span class="token string">"test"</span><span class="token punctuation">;</span></span>
<span class="line">        config_<span class="token punctuation">.</span>agent_addr <span class="token operator">=</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">;</span></span>
<span class="line">        config_<span class="token punctuation">.</span>insecure <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">TearDown</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token keyword">override</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token function">StopTestAgent</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">StartTestAgent</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token comment">// 启动实际的 Agent 进程</span></span>
<span class="line">        agent_process_ <span class="token operator">=</span> std<span class="token double-colon punctuation">::</span><span class="token generic-function"><span class="token function">make_unique</span><span class="token generic class-name"><span class="token operator">&lt;</span>Process<span class="token operator">></span></span></span><span class="token punctuation">(</span><span class="token string">"croupier-agent"</span><span class="token punctuation">,</span> <span class="token string">"-f"</span><span class="token punctuation">,</span> <span class="token string">"test-config.yaml"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        agent_process_<span class="token operator">-></span><span class="token function">Start</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>this_thread<span class="token double-colon punctuation">::</span><span class="token function">sleep_for</span><span class="token punctuation">(</span>std<span class="token double-colon punctuation">::</span>chrono<span class="token double-colon punctuation">::</span><span class="token function">seconds</span><span class="token punctuation">(</span><span class="token number">2</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">void</span> <span class="token function">StopTestAgent</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">if</span> <span class="token punctuation">(</span>agent_process_<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">            agent_process_<span class="token operator">-></span><span class="token function">Stop</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token punctuation">}</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    ClientConfig config_<span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>unique_ptr<span class="token operator">&lt;</span>Process<span class="token operator">></span> agent_process_<span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token function">TEST_F</span><span class="token punctuation">(</span>IntegrationTest<span class="token punctuation">,</span> FullWorkflow<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config_<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 注册函数</span></span>
<span class="line">    FunctionDescriptor desc<span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>id <span class="token operator">=</span> <span class="token string">"test.workflow"</span><span class="token punctuation">;</span></span>
<span class="line">    desc<span class="token punctuation">.</span>version <span class="token operator">=</span> <span class="token string">"0.1.0"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">bool</span> registered <span class="token operator">=</span> client<span class="token punctuation">.</span><span class="token function">RegisterFunction</span><span class="token punctuation">(</span>desc<span class="token punctuation">,</span> <span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token keyword">auto</span> ctx<span class="token punctuation">,</span> <span class="token keyword">auto</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">return</span> <span class="token raw-string string">R"({"status": "completed"})"</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token function">ASSERT_TRUE</span><span class="token punctuation">(</span>registered<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 连接</span></span>
<span class="line">    <span class="token function">ASSERT_TRUE</span><span class="token punctuation">(</span>client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 等待注册完成</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>this_thread<span class="token double-colon punctuation">::</span><span class="token function">sleep_for</span><span class="token punctuation">(</span>std<span class="token double-colon punctuation">::</span>chrono<span class="token double-colon punctuation">::</span><span class="token function">milliseconds</span><span class="token punctuation">(</span><span class="token number">500</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 这里可以通过 Agent 调用函数验证...</span></span>
<span class="line"></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Close</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="性能测试" tabindex="-1"><a class="header-anchor" href="#性能测试"><span>性能测试</span></a></h2>
<h3 id="基准测试" tabindex="-1"><a class="header-anchor" href="#基准测试"><span>基准测试</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">&lt;benchmark/benchmark.h></span></span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">static</span> <span class="token keyword">void</span> <span class="token function">BM_FunctionCall</span><span class="token punctuation">(</span>benchmark<span class="token double-colon punctuation">::</span>State<span class="token operator">&amp;</span> state<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token keyword">auto</span> handler <span class="token operator">=</span> <span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> ctx<span class="token punctuation">,</span> <span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> payload<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">return</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ToJSON</span><span class="token punctuation">(</span><span class="token punctuation">{</span><span class="token punctuation">{</span><span class="token string">"result"</span><span class="token punctuation">,</span> <span class="token number">42</span><span class="token punctuation">}</span><span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string payload <span class="token operator">=</span> <span class="token raw-string string">R"({"value": 100})"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">for</span> <span class="token punctuation">(</span><span class="token keyword">auto</span> _ <span class="token operator">:</span> state<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>string result <span class="token operator">=</span> <span class="token function">handler</span><span class="token punctuation">(</span><span class="token string">""</span><span class="token punctuation">,</span> payload<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        benchmark<span class="token double-colon punctuation">::</span><span class="token function">DoNotOptimize</span><span class="token punctuation">(</span>result<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token function">BENCHMARK</span><span class="token punctuation">(</span>BM_FunctionCall<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">static</span> <span class="token keyword">void</span> <span class="token function">BM_JSONParsing</span><span class="token punctuation">(</span>benchmark<span class="token double-colon punctuation">::</span>State<span class="token operator">&amp;</span> state<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string json <span class="token operator">=</span> <span class="token raw-string string">R"({"key": "value", "number": 42})"</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">for</span> <span class="token punctuation">(</span><span class="token keyword">auto</span> _ <span class="token operator">:</span> state<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        <span class="token keyword">auto</span> result <span class="token operator">=</span> utils<span class="token double-colon punctuation">::</span><span class="token function">ParseJSON</span><span class="token punctuation">(</span>json<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        benchmark<span class="token double-colon punctuation">::</span><span class="token function">DoNotOptimize</span><span class="token punctuation">(</span>result<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token function">BENCHMARK</span><span class="token punctuation">(</span>BM_JSONParsing<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token function">BENCHMARK_MAIN</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="运行性能测试" tabindex="-1"><a class="header-anchor" href="#运行性能测试"><span>运行性能测试</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 构建 benchmark</span></span>
<span class="line">cmake <span class="token parameter variable">-DBUILD_BENCHMARKS</span><span class="token operator">=</span>ON <span class="token punctuation">..</span></span>
<span class="line"><span class="token function">make</span> benchmark</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 运行</span></span>
<span class="line">./benchmark <span class="token parameter variable">--benchmark_filter</span><span class="token operator">=</span>.*</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="端到端测试" tabindex="-1"><a class="header-anchor" href="#端到端测试"><span>端到端测试</span></a></h2>
<h3 id="测试脚本" tabindex="-1"><a class="header-anchor" href="#测试脚本"><span>测试脚本</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token shebang important">#!/bin/bash</span></span>
<span class="line"><span class="token comment"># e2e_test.sh</span></span>
<span class="line"></span>
<span class="line"><span class="token builtin class-name">set</span> <span class="token parameter variable">-e</span></span>
<span class="line"></span>
<span class="line"><span class="token builtin class-name">echo</span> <span class="token string">"Starting end-to-end tests..."</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 启动 Server</span></span>
<span class="line">croupier-server <span class="token parameter variable">-f</span> test-config/server.yaml <span class="token operator">&amp;</span></span>
<span class="line"><span class="token assign-left variable">SERVER_PID</span><span class="token operator">=</span><span class="token variable">$!</span></span>
<span class="line"><span class="token function">sleep</span> <span class="token number">2</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 启动 Agent</span></span>
<span class="line">croupier-agent <span class="token parameter variable">-f</span> test-config/agent.yaml <span class="token operator">&amp;</span></span>
<span class="line"><span class="token assign-left variable">AGENT_PID</span><span class="token operator">=</span><span class="token variable">$!</span></span>
<span class="line"><span class="token function">sleep</span> <span class="token number">2</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 启动测试客户端</span></span>
<span class="line">./build/test-client <span class="token operator">&amp;</span></span>
<span class="line"><span class="token assign-left variable">CLIENT_PID</span><span class="token operator">=</span><span class="token variable">$!</span></span>
<span class="line"><span class="token function">sleep</span> <span class="token number">2</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 运行测试用例</span></span>
<span class="line">python tests/e2e/run_tests.py</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 清理</span></span>
<span class="line"><span class="token function">kill</span> <span class="token variable">$CLIENT_PID</span> <span class="token variable">$AGENT_PID</span> <span class="token variable">$SERVER_PID</span></span>
<span class="line"></span>
<span class="line"><span class="token builtin class-name">echo</span> <span class="token string">"E2E tests completed!"</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="python-测试客户端" tabindex="-1"><a class="header-anchor" href="#python-测试客户端"><span>Python 测试客户端</span></a></h3>
<div class="language-python line-numbers-mode" data-highlighter="prismjs" data-ext="py"><pre v-pre><code class="language-python"><span class="line"><span class="token keyword">import</span> requests</span>
<span class="line"><span class="token keyword">import</span> unittest</span>
<span class="line"></span>
<span class="line"><span class="token keyword">class</span> <span class="token class-name">E2ETest</span><span class="token punctuation">(</span>unittest<span class="token punctuation">.</span>TestCase<span class="token punctuation">)</span><span class="token punctuation">:</span></span>
<span class="line">    <span class="token decorator annotation punctuation">@classmethod</span></span>
<span class="line">    <span class="token keyword">def</span> <span class="token function">setUpClass</span><span class="token punctuation">(</span>cls<span class="token punctuation">)</span><span class="token punctuation">:</span></span>
<span class="line">        cls<span class="token punctuation">.</span>base_url <span class="token operator">=</span> <span class="token string">"http://localhost:8080"</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">def</span> <span class="token function">test_invoke_function</span><span class="token punctuation">(</span>self<span class="token punctuation">)</span><span class="token punctuation">:</span></span>
<span class="line">        response <span class="token operator">=</span> requests<span class="token punctuation">.</span>post<span class="token punctuation">(</span></span>
<span class="line">            <span class="token string-interpolation"><span class="token string">f"</span><span class="token interpolation"><span class="token punctuation">{</span>self<span class="token punctuation">.</span>base_url<span class="token punctuation">}</span></span><span class="token string">/api/v1/functions/test.workflow/invoke"</span></span><span class="token punctuation">,</span></span>
<span class="line">            json<span class="token operator">=</span><span class="token punctuation">{</span><span class="token string">"player_id"</span><span class="token punctuation">:</span> <span class="token string">"test123"</span><span class="token punctuation">,</span> <span class="token string">"amount"</span><span class="token punctuation">:</span> <span class="token number">100</span><span class="token punctuation">}</span><span class="token punctuation">,</span></span>
<span class="line">            headers<span class="token operator">=</span><span class="token punctuation">{</span><span class="token string">"X-Game-ID"</span><span class="token punctuation">:</span> <span class="token string">"integration-test"</span><span class="token punctuation">}</span></span>
<span class="line">        <span class="token punctuation">)</span></span>
<span class="line">        self<span class="token punctuation">.</span>assertEqual<span class="token punctuation">(</span>response<span class="token punctuation">.</span>status_code<span class="token punctuation">,</span> <span class="token number">200</span><span class="token punctuation">)</span></span>
<span class="line">        self<span class="token punctuation">.</span>assertEqual<span class="token punctuation">(</span>response<span class="token punctuation">.</span>json<span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">[</span><span class="token string">"status"</span><span class="token punctuation">]</span><span class="token punctuation">,</span> <span class="token string">"completed"</span><span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">def</span> <span class="token function">test_virtual_object_get</span><span class="token punctuation">(</span>self<span class="token punctuation">)</span><span class="token punctuation">:</span></span>
<span class="line">        response <span class="token operator">=</span> requests<span class="token punctuation">.</span>get<span class="token punctuation">(</span></span>
<span class="line">            <span class="token string-interpolation"><span class="token string">f"</span><span class="token interpolation"><span class="token punctuation">{</span>self<span class="token punctuation">.</span>base_url<span class="token punctuation">}</span></span><span class="token string">/api/v1/objects/wallet.entity/test123"</span></span><span class="token punctuation">,</span></span>
<span class="line">            headers<span class="token operator">=</span><span class="token punctuation">{</span><span class="token string">"X-Game-ID"</span><span class="token punctuation">:</span> <span class="token string">"integration-test"</span><span class="token punctuation">}</span></span>
<span class="line">        <span class="token punctuation">)</span></span>
<span class="line">        self<span class="token punctuation">.</span>assertEqual<span class="token punctuation">(</span>response<span class="token punctuation">.</span>status_code<span class="token punctuation">,</span> <span class="token number">200</span><span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">if</span> __name__ <span class="token operator">==</span> <span class="token string">"__main__"</span><span class="token punctuation">:</span></span>
<span class="line">    unittest<span class="token punctuation">.</span>main<span class="token punctuation">(</span><span class="token punctuation">)</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="测试配置" tabindex="-1"><a class="header-anchor" href="#测试配置"><span>测试配置</span></a></h2>
<h3 id="测试配置文件" tabindex="-1"><a class="header-anchor" href="#测试配置文件"><span>测试配置文件</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"test-game"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"env"</span><span class="token operator">:</span> <span class="token string">"test"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"service_id"</span><span class="token operator">:</span> <span class="token string">"test-service"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"agent_addr"</span><span class="token operator">:</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"insecure"</span><span class="token operator">:</span> <span class="token boolean">true</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"timeout_seconds"</span><span class="token operator">:</span> <span class="token number">5</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"auto_reconnect"</span><span class="token operator">:</span> <span class="token boolean">false</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="cmake-测试配置" tabindex="-1"><a class="header-anchor" href="#cmake-测试配置"><span>CMake 测试配置</span></a></h3>
<div class="language-cmake line-numbers-mode" data-highlighter="prismjs" data-ext="cmake"><pre v-pre><code class="language-cmake"><span class="line"><span class="token comment"># CMakeLists.txt</span></span>
<span class="line"><span class="token keyword">include</span><span class="token punctuation">(</span>CTest<span class="token punctuation">)</span></span>
<span class="line"><span class="token keyword">include</span><span class="token punctuation">(</span>GoogleTest<span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">enable_testing</span><span class="token punctuation">(</span><span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 测试可执行文件</span></span>
<span class="line"><span class="token keyword">add_executable</span><span class="token punctuation">(</span>unit_tests</span>
<span class="line">    tests/unit_tests.cpp</span>
<span class="line">    tests/mock_agent.cpp</span>
<span class="line"><span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">target_link_libraries</span><span class="token punctuation">(</span>unit_tests</span>
<span class="line">    <span class="token namespace">PRIVATE</span></span>
<span class="line">    croupier-<span class="token inserted class-name">sdk::croupier</span>-sdk</span>
<span class="line">    <span class="token inserted class-name">GTest::gtest_main</span></span>
<span class="line"><span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 注册测试</span></span>
<span class="line"><span class="token function">discover_tests</span><span class="token punctuation">(</span>unit_tests<span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 集成测试</span></span>
<span class="line"><span class="token keyword">add_executable</span><span class="token punctuation">(</span>integration_tests</span>
<span class="line">    tests/integration_tests.cpp</span>
<span class="line"><span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">target_link_libraries</span><span class="token punctuation">(</span>integration_tests</span>
<span class="line">    <span class="token namespace">PRIVATE</span></span>
<span class="line">    croupier-<span class="token inserted class-name">sdk::croupier</span>-sdk</span>
<span class="line">    <span class="token inserted class-name">GTest::gtest_main</span></span>
<span class="line"><span class="token punctuation">)</span></span>
<span class="line"></span>
<span class="line"><span class="token keyword">add_test</span><span class="token punctuation">(</span><span class="token property">NAME</span> Integration COMMAND integration_tests<span class="token punctuation">)</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="覆盖率报告" tabindex="-1"><a class="header-anchor" href="#覆盖率报告"><span>覆盖率报告</span></a></h2>
<h3 id="启用代码覆盖率" tabindex="-1"><a class="header-anchor" href="#启用代码覆盖率"><span>启用代码覆盖率</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># GCC/Clang</span></span>
<span class="line">cmake <span class="token parameter variable">-DCMAKE_BUILD_TYPE</span><span class="token operator">=</span>Debug <span class="token punctuation">\</span></span>
<span class="line">      <span class="token parameter variable">-DCMAKE_CXX_FLAGS</span><span class="token operator">=</span><span class="token string">"--coverage"</span> <span class="token punctuation">\</span></span>
<span class="line">      <span class="token parameter variable">-DCMAKE_EXE_LINKER_FLAGS</span><span class="token operator">=</span><span class="token string">"--coverage"</span> <span class="token punctuation">\</span></span>
<span class="line">      <span class="token parameter variable">-B</span> build</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 运行测试</span></span>
<span class="line"><span class="token builtin class-name">cd</span> build</span>
<span class="line">ctest</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 生成覆盖率报告</span></span>
<span class="line">lcov <span class="token parameter variable">--capture</span> <span class="token parameter variable">--directory</span> <span class="token builtin class-name">.</span> --output-file coverage.info</span>
<span class="line">lcov <span class="token parameter variable">--remove</span> coverage.info <span class="token string">'/usr/*'</span> --output-file coverage.info</span>
<span class="line">genhtml coverage.info --output-directory coverage_html</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="覆盖率目标" tabindex="-1"><a class="header-anchor" href="#覆盖率目标"><span>覆盖率目标</span></a></h3>
<table>
<thead>
<tr>
<th>组件</th>
<th>目标覆盖率</th>
</tr>
</thead>
<tbody>
<tr>
<td>核心库</td>
<td>80%+</td>
</tr>
<tr>
<td>工具函数</td>
<td>70%+</td>
</tr>
<tr>
<td>示例代码</td>
<td>60%+</td>
</tr>
</tbody>
</table>
<h2 id="最佳实践" tabindex="-1"><a class="header-anchor" href="#最佳实践"><span>最佳实践</span></a></h2>
<h3 id="_1-测试隔离" tabindex="-1"><a class="header-anchor" href="#_1-测试隔离"><span>1. 测试隔离</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token comment">// 每个测试使用独立的命名空间</span></span>
<span class="line"><span class="token function">TEST_F</span><span class="token punctuation">(</span>CroupierClientTest<span class="token punctuation">,</span> RegisterFunction_UniqueName<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>string unique_id <span class="token operator">=</span> <span class="token string">"test.function."</span> <span class="token operator">+</span> std<span class="token double-colon punctuation">::</span><span class="token function">to_string</span><span class="token punctuation">(</span>std<span class="token double-colon punctuation">::</span><span class="token function">rand</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token comment">// ...</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="_2-清理资源" tabindex="-1"><a class="header-anchor" href="#_2-清理资源"><span>2. 清理资源</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token function">TEST_F</span><span class="token punctuation">(</span>CroupierClientTest<span class="token punctuation">,</span> ResourceCleanup<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    CroupierClient <span class="token function">client</span><span class="token punctuation">(</span>config_<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 测试逻辑...</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 确保清理</span></span>
<span class="line">    client<span class="token punctuation">.</span><span class="token function">Close</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="_3-超时控制" tabindex="-1"><a class="header-anchor" href="#_3-超时控制"><span>3. 超时控制</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token function">TEST_F</span><span class="token punctuation">(</span>CroupierClientTest<span class="token punctuation">,</span> Timeout<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 设置测试超时</span></span>
<span class="line">    <span class="token function">ASSERT_DURATION_LE</span><span class="token punctuation">(</span><span class="token number">5</span>s<span class="token punctuation">,</span> <span class="token punctuation">{</span></span>
<span class="line">        client<span class="token punctuation">.</span><span class="token function">Connect</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="_4-参数化测试" tabindex="-1"><a class="header-anchor" href="#_4-参数化测试"><span>4. 参数化测试</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">class</span> <span class="token class-name">ParamTest</span> <span class="token operator">:</span> <span class="token base-clause"><span class="token keyword">public</span> <span class="token double-colon punctuation">::</span>testing<span class="token double-colon punctuation">::</span><span class="token class-name">TestWithParam</span><span class="token operator">&lt;</span><span class="token keyword">int</span><span class="token operator">></span></span> <span class="token punctuation">{</span><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token function">TEST_P</span><span class="token punctuation">(</span>ParamTest<span class="token punctuation">,</span> VariousAmounts<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token keyword">int</span> amount <span class="token operator">=</span> <span class="token function">GetParam</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">auto</span> result <span class="token operator">=</span> <span class="token function">ProcessTransfer</span><span class="token punctuation">(</span>amount<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token function">EXPECT_TRUE</span><span class="token punctuation">(</span>result<span class="token punctuation">[</span><span class="token string">"success"</span><span class="token punctuation">]</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line"><span class="token function">INSTANTIATE_TEST_SUITE_P</span><span class="token punctuation">(</span></span>
<span class="line">    TransferAmounts<span class="token punctuation">,</span></span>
<span class="line">    ParamTest<span class="token punctuation">,</span></span>
<span class="line">    <span class="token double-colon punctuation">::</span>testing<span class="token double-colon punctuation">::</span><span class="token function">Values</span><span class="token punctuation">(</span><span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">10</span><span class="token punctuation">,</span> <span class="token number">100</span><span class="token punctuation">,</span> <span class="token number">1000</span><span class="token punctuation">)</span></span>
<span class="line"><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div></div></template>


