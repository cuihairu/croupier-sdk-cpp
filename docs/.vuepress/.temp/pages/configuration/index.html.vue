<template><div><h1 id="配置指南" tabindex="-1"><a class="header-anchor" href="#配置指南"><span>配置指南</span></a></h1>
<p>Croupier C++ SDK 支持灵活的配置系统，包括文件配置、环境变量覆盖和配置验证。</p>
<h2 id="目录" tabindex="-1"><a class="header-anchor" href="#目录"><span>目录</span></a></h2>
<ul>
<li><RouteLink to="/configuration/client-config.html">客户端配置</RouteLink> - ClientConfig 完整参考</li>
<li><RouteLink to="/configuration/environments.html">环境配置</RouteLink> - 多环境配置管理</li>
<li><RouteLink to="/configuration/security.html">安全配置</RouteLink> - TLS 和认证配置</li>
</ul>
<h2 id="快速开始" tabindex="-1"><a class="header-anchor" href="#快速开始"><span>快速开始</span></a></h2>
<h3 id="基础配置文件" tabindex="-1"><a class="header-anchor" href="#基础配置文件"><span>基础配置文件</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"game_id"</span><span class="token operator">:</span> <span class="token string">"demo-game"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"env"</span><span class="token operator">:</span> <span class="token string">"development"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"service_id"</span><span class="token operator">:</span> <span class="token string">"demo-service"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"agent_addr"</span><span class="token operator">:</span> <span class="token string">"127.0.0.1:19090"</span><span class="token punctuation">,</span></span>
<span class="line">  <span class="token property">"insecure"</span><span class="token operator">:</span> <span class="token boolean">true</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="加载配置" tabindex="-1"><a class="header-anchor" href="#加载配置"><span>加载配置</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">include</span> <span class="token string">"croupier/sdk/config/client_config_loader.h"</span></span></span>
<span class="line"></span>
<span class="line">ClientConfigLoader loader<span class="token punctuation">;</span></span>
<span class="line">ClientConfig config <span class="token operator">=</span> loader<span class="token punctuation">.</span><span class="token function">LoadFromFile</span><span class="token punctuation">(</span><span class="token string">"./config.json"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="环境变量覆盖" tabindex="-1"><a class="header-anchor" href="#环境变量覆盖"><span>环境变量覆盖</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_GAME_ID</span><span class="token operator">=</span>production-game</span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_ENV</span><span class="token operator">=</span>production</span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_AGENT_ADDR</span><span class="token operator">=</span>croupier-agent:19090</span>
<span class="line"></span>
<span class="line">./your-app</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="配置加载器" tabindex="-1"><a class="header-anchor" href="#配置加载器"><span>配置加载器</span></a></h2>
<h3 id="clientconfigloader-方法" tabindex="-1"><a class="header-anchor" href="#clientconfigloader-方法"><span>ClientConfigLoader 方法</span></a></h3>
<table>
<thead>
<tr>
<th>方法</th>
<th>说明</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>LoadFromFile(path)</code></td>
<td>从 JSON 文件加载</td>
</tr>
<tr>
<td><code v-pre>LoadFromJson(json)</code></td>
<td>从 JSON 字符串加载</td>
</tr>
<tr>
<td><code v-pre>LoadWithEnvironmentOverrides(path, prefix)</code></td>
<td>加载并应用环境变量</td>
</tr>
<tr>
<td><code v-pre>LoadProfile(dir, profile)</code></td>
<td>加载配置 profile</td>
</tr>
<tr>
<td><code v-pre>ValidateConfig(config)</code></td>
<td>验证配置</td>
</tr>
</tbody>
</table>
<h3 id="示例" tabindex="-1"><a class="header-anchor" href="#示例"><span>示例</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">ClientConfigLoader loader<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 文件加载</span></span>
<span class="line">ClientConfig config <span class="token operator">=</span> loader<span class="token punctuation">.</span><span class="token function">LoadFromFile</span><span class="token punctuation">(</span><span class="token string">"./production.json"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 环境变量覆盖</span></span>
<span class="line">ClientConfig config <span class="token operator">=</span> loader<span class="token punctuation">.</span><span class="token function">LoadWithEnvironmentOverrides</span><span class="token punctuation">(</span></span>
<span class="line">    <span class="token string">"./production.json"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token string">"CROUPIER_"</span></span>
<span class="line"><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 验证</span></span>
<span class="line"><span class="token keyword">auto</span> errors <span class="token operator">=</span> loader<span class="token punctuation">.</span><span class="token function">ValidateConfig</span><span class="token punctuation">(</span>config<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token operator">!</span>errors<span class="token punctuation">.</span><span class="token function">empty</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token keyword">for</span> <span class="token punctuation">(</span><span class="token keyword">const</span> <span class="token keyword">auto</span><span class="token operator">&amp;</span> error <span class="token operator">:</span> errors<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>cerr <span class="token operator">&lt;&lt;</span> error <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="环境变量" tabindex="-1"><a class="header-anchor" href="#环境变量"><span>环境变量</span></a></h2>
<p>所有配置字段都可以通过环境变量覆盖，使用 <code v-pre>CROUPIER_</code> 前缀：</p>
<table>
<thead>
<tr>
<th>配置字段</th>
<th>环境变量</th>
</tr>
</thead>
<tbody>
<tr>
<td><code v-pre>game_id</code></td>
<td><code v-pre>CROUPIER_GAME_ID</code></td>
</tr>
<tr>
<td><code v-pre>env</code></td>
<td><code v-pre>CROUPIER_ENV</code></td>
</tr>
<tr>
<td><code v-pre>agent_addr</code></td>
<td><code v-pre>CROUPIER_AGENT_ADDR</code></td>
</tr>
<tr>
<td><code v-pre>service_id</code></td>
<td><code v-pre>CROUPIER_SERVICE_ID</code></td>
</tr>
<tr>
<td><code v-pre>insecure</code></td>
<td><code v-pre>CROUPIER_INSECURE</code></td>
</tr>
<tr>
<td><code v-pre>timeout_seconds</code></td>
<td><code v-pre>CROUPIER_TIMEOUT_SECONDS</code></td>
</tr>
<tr>
<td><code v-pre>auto_reconnect</code></td>
<td><code v-pre>CROUPIER_AUTO_RECONNECT</code></td>
</tr>
<tr>
<td><code v-pre>reconnect_interval_seconds</code></td>
<td><code v-pre>CROUPIER_RECONNECT_INTERVAL_SECONDS</code></td>
</tr>
</tbody>
</table>
<h3 id="嵌套字段" tabindex="-1"><a class="header-anchor" href="#嵌套字段"><span>嵌套字段</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 安全配置</span></span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_CERT_FILE</span><span class="token operator">=</span><span class="token string">"/path/to/cert.pem"</span></span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_KEY_FILE</span><span class="token operator">=</span><span class="token string">"/path/to/key.pem"</span></span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_CA_FILE</span><span class="token operator">=</span><span class="token string">"/path/to/ca.pem"</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 认证配置</span></span>
<span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_AUTH_TOKEN</span><span class="token operator">=</span><span class="token string">"Bearer token123"</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="配置文件位置" tabindex="-1"><a class="header-anchor" href="#配置文件位置"><span>配置文件位置</span></a></h2>
<p>SDK 按以下顺序查找配置文件：</p>
<ol>
<li>当前目录：<code v-pre>./config.json</code></li>
<li>用户目录：<code v-pre>~/.croupier/config.json</code></li>
<li>系统目录：<code v-pre>/etc/croupier/config.json</code></li>
</ol>
<p>可以通过命令行或代码指定：</p>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token comment">// 指定配置文件</span></span>
<span class="line">ClientConfig config <span class="token operator">=</span> loader<span class="token punctuation">.</span><span class="token function">LoadFromFile</span><span class="token punctuation">(</span><span class="token string">"/path/to/config.json"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="配置验证" tabindex="-1"><a class="header-anchor" href="#配置验证"><span>配置验证</span></a></h2>
<p>配置加载器会自动验证：</p>
<ul>
<li>✅ 必需字段存在</li>
<li>✅ 网络地址格式正确</li>
<li>✅ 文件路径存在</li>
<li>✅ 环境名称有效</li>
<li>✅ 数值范围合理</li>
</ul>
<h3 id="自定义验证" tabindex="-1"><a class="header-anchor" href="#自定义验证"><span>自定义验证</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">class</span> <span class="token class-name">CustomValidator</span> <span class="token punctuation">{</span></span>
<span class="line"><span class="token keyword">public</span><span class="token operator">:</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>vector<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token operator">></span> <span class="token function">Validate</span><span class="token punctuation">(</span><span class="token keyword">const</span> ClientConfig<span class="token operator">&amp;</span> config<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>vector<span class="token operator">&lt;</span>std<span class="token double-colon punctuation">::</span>string<span class="token operator">></span> errors<span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">        <span class="token keyword">if</span> <span class="token punctuation">(</span>config<span class="token punctuation">.</span>game_id<span class="token punctuation">.</span><span class="token function">empty</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">            errors<span class="token punctuation">.</span><span class="token function">push_back</span><span class="token punctuation">(</span><span class="token string">"game_id 不能为空"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">        <span class="token keyword">if</span> <span class="token punctuation">(</span>config<span class="token punctuation">.</span>env <span class="token operator">!=</span> <span class="token string">"production"</span> <span class="token operator">&amp;&amp;</span> config<span class="token punctuation">.</span>env <span class="token operator">!=</span> <span class="token string">"staging"</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">            errors<span class="token punctuation">.</span><span class="token function">push_back</span><span class="token punctuation">(</span><span class="token string">"env 必须是 production 或 staging"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">        <span class="token keyword">if</span> <span class="token punctuation">(</span>config<span class="token punctuation">.</span>timeout_seconds <span class="token operator">&lt;</span> <span class="token number">1</span> <span class="token operator">||</span> config<span class="token punctuation">.</span>timeout_seconds <span class="token operator">></span> <span class="token number">300</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">            errors<span class="token punctuation">.</span><span class="token function">push_back</span><span class="token punctuation">(</span><span class="token string">"timeout_seconds 必须在 1-300 之间"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">        <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">        <span class="token keyword">return</span> errors<span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="下一步" tabindex="-1"><a class="header-anchor" href="#下一步"><span>下一步</span></a></h2>
<ul>
<li><RouteLink to="/configuration/client-config.html">客户端配置详解</RouteLink></li>
<li><RouteLink to="/configuration/environments.html">多环境配置</RouteLink></li>
<li><RouteLink to="/configuration/security.html">安全配置</RouteLink></li>
</ul>
</div></template>


