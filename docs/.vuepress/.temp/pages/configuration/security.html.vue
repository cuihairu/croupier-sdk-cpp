<template><div><h1 id="安全配置" tabindex="-1"><a class="header-anchor" href="#安全配置"><span>安全配置</span></a></h1>
<p>本指南介绍 TLS、认证和其他安全相关的配置。</p>
<h2 id="tls-配置" tabindex="-1"><a class="header-anchor" href="#tls-配置"><span>TLS 配置</span></a></h2>
<h3 id="基础-tls" tabindex="-1"><a class="header-anchor" href="#基础-tls"><span>基础 TLS</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">ClientConfig config<span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>insecure <span class="token operator">=</span> <span class="token boolean">false</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>cert_file <span class="token operator">=</span> <span class="token string">"/etc/tls/client.crt"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>key_file <span class="token operator">=</span> <span class="token string">"/etc/tls/client.key"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>ca_file <span class="token operator">=</span> <span class="token string">"/etc/tls/ca.crt"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>server_name <span class="token operator">=</span> <span class="token string">"croupier.internal"</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="配置文件" tabindex="-1"><a class="header-anchor" href="#配置文件"><span>配置文件</span></a></h3>
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
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="证书生成" tabindex="-1"><a class="header-anchor" href="#证书生成"><span>证书生成</span></a></h2>
<h3 id="生成-ca-证书" tabindex="-1"><a class="header-anchor" href="#生成-ca-证书"><span>生成 CA 证书</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 生成 CA 私钥</span></span>
<span class="line">openssl genrsa <span class="token parameter variable">-out</span> ca.key <span class="token number">4096</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 生成 CA 证书</span></span>
<span class="line">openssl req <span class="token parameter variable">-new</span> <span class="token parameter variable">-x509</span> <span class="token parameter variable">-days</span> <span class="token number">365</span> <span class="token parameter variable">-key</span> ca.key <span class="token parameter variable">-out</span> ca.crt <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-subj</span> <span class="token string">"/C=CN/ST=Beijing/L=Beijing/O=Croupier/CN=CroupierCA"</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="生成服务器证书" tabindex="-1"><a class="header-anchor" href="#生成服务器证书"><span>生成服务器证书</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 生成私钥</span></span>
<span class="line">openssl genrsa <span class="token parameter variable">-out</span> server.key <span class="token number">4096</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 生成 CSR</span></span>
<span class="line">openssl req <span class="token parameter variable">-new</span> <span class="token parameter variable">-key</span> server.key <span class="token parameter variable">-out</span> server.csr <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-subj</span> <span class="token string">"/C=CN/ST=Beijing/L=Beijing/O=Croupier/CN=croupier-agent.internal"</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 用 CA 签名</span></span>
<span class="line">openssl x509 <span class="token parameter variable">-req</span> <span class="token parameter variable">-days</span> <span class="token number">365</span> <span class="token parameter variable">-in</span> server.csr <span class="token parameter variable">-CA</span> ca.crt <span class="token parameter variable">-CAkey</span> ca.key <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-CAcreateserial</span> <span class="token parameter variable">-out</span> server.crt</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="生成客户端证书" tabindex="-1"><a class="header-anchor" href="#生成客户端证书"><span>生成客户端证书</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 生成私钥</span></span>
<span class="line">openssl genrsa <span class="token parameter variable">-out</span> client.key <span class="token number">4096</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 生成 CSR</span></span>
<span class="line">openssl req <span class="token parameter variable">-new</span> <span class="token parameter variable">-key</span> client.key <span class="token parameter variable">-out</span> client.csr <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-subj</span> <span class="token string">"/C=CN/ST=Beijing/L=Beijing/O=Croupier/CN=game-server"</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 用 CA 签名</span></span>
<span class="line">openssl x509 <span class="token parameter variable">-req</span> <span class="token parameter variable">-days</span> <span class="token number">365</span> <span class="token parameter variable">-in</span> client.csr <span class="token parameter variable">-CA</span> ca.crt <span class="token parameter variable">-CAkey</span> ca.key <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-CAcreateserial</span> <span class="token parameter variable">-out</span> client.crt</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="认证配置" tabindex="-1"><a class="header-anchor" href="#认证配置"><span>认证配置</span></a></h2>
<h3 id="jwt-token" tabindex="-1"><a class="header-anchor" href="#jwt-token"><span>JWT Token</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line">config<span class="token punctuation">.</span>auth<span class="token punctuation">.</span>token <span class="token operator">=</span> <span class="token string">"Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><h3 id="使用环境变量" tabindex="-1"><a class="header-anchor" href="#使用环境变量"><span>使用环境变量</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token builtin class-name">export</span> <span class="token assign-left variable">CROUPIER_AUTH_TOKEN</span><span class="token operator">=</span><span class="token string">"Bearer <span class="token variable">${JWT_TOKEN}</span>"</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><h3 id="配置文件-1" tabindex="-1"><a class="header-anchor" href="#配置文件-1"><span>配置文件</span></a></h3>
<div class="language-json line-numbers-mode" data-highlighter="prismjs" data-ext="json"><pre v-pre><code class="language-json"><span class="line"><span class="token punctuation">{</span></span>
<span class="line">  <span class="token property">"auth"</span><span class="token operator">:</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token property">"token"</span><span class="token operator">:</span> <span class="token string">"Bearer ${JWT_TOKEN}"</span><span class="token punctuation">,</span></span>
<span class="line">    <span class="token property">"headers"</span><span class="token operator">:</span> <span class="token punctuation">{</span></span>
<span class="line">      <span class="token property">"X-Game-ID"</span><span class="token operator">:</span> <span class="token string">"${GAME_ID}"</span><span class="token punctuation">,</span></span>
<span class="line">      <span class="token property">"X-Service-Region"</span><span class="token operator">:</span> <span class="token string">"us-west-2"</span><span class="token punctuation">,</span></span>
<span class="line">      <span class="token property">"X-Cluster"</span><span class="token operator">:</span> <span class="token string">"production-01"</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line">  <span class="token punctuation">}</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="kubernetes-secrets" tabindex="-1"><a class="header-anchor" href="#kubernetes-secrets"><span>Kubernetes Secrets</span></a></h2>
<h3 id="创建-tls-secret" tabindex="-1"><a class="header-anchor" href="#创建-tls-secret"><span>创建 TLS Secret</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line">kubectl create secret tls croupier-tls <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">--cert</span><span class="token operator">=</span>/path/to/client.crt <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">--key</span><span class="token operator">=</span>/path/to/client.key <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-n</span> game</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="创建-token-secret" tabindex="-1"><a class="header-anchor" href="#创建-token-secret"><span>创建 Token Secret</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line">kubectl create secret generic croupier-auth <span class="token punctuation">\</span></span>
<span class="line">  --from-literal<span class="token operator">=</span>jwt-token<span class="token operator">=</span><span class="token string">'your-jwt-token'</span> <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">-n</span> game</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="pod-中使用" tabindex="-1"><a class="header-anchor" href="#pod-中使用"><span>Pod 中使用</span></a></h3>
<div class="language-yaml line-numbers-mode" data-highlighter="prismjs" data-ext="yml"><pre v-pre><code class="language-yaml"><span class="line"><span class="token key atrule">apiVersion</span><span class="token punctuation">:</span> v1</span>
<span class="line"><span class="token key atrule">kind</span><span class="token punctuation">:</span> Pod</span>
<span class="line"><span class="token key atrule">metadata</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">name</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>server</span>
<span class="line"><span class="token key atrule">spec</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token key atrule">containers</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>server</span>
<span class="line">    <span class="token key atrule">image</span><span class="token punctuation">:</span> game<span class="token punctuation">-</span>server<span class="token punctuation">:</span>latest</span>
<span class="line">    <span class="token key atrule">env</span><span class="token punctuation">:</span></span>
<span class="line">    <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> CROUPIER_AUTH_TOKEN</span>
<span class="line">      <span class="token key atrule">valueFrom</span><span class="token punctuation">:</span></span>
<span class="line">        <span class="token key atrule">secretKeyRef</span><span class="token punctuation">:</span></span>
<span class="line">          <span class="token key atrule">name</span><span class="token punctuation">:</span> croupier<span class="token punctuation">-</span>auth</span>
<span class="line">          <span class="token key atrule">key</span><span class="token punctuation">:</span> jwt<span class="token punctuation">-</span>token</span>
<span class="line">    <span class="token key atrule">volumeMounts</span><span class="token punctuation">:</span></span>
<span class="line">    <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> tls<span class="token punctuation">-</span>certs</span>
<span class="line">      <span class="token key atrule">mountPath</span><span class="token punctuation">:</span> /etc/tls</span>
<span class="line">      <span class="token key atrule">readOnly</span><span class="token punctuation">:</span> <span class="token boolean important">true</span></span>
<span class="line">  <span class="token key atrule">volumes</span><span class="token punctuation">:</span></span>
<span class="line">  <span class="token punctuation">-</span> <span class="token key atrule">name</span><span class="token punctuation">:</span> tls<span class="token punctuation">-</span>certs</span>
<span class="line">    <span class="token key atrule">secret</span><span class="token punctuation">:</span></span>
<span class="line">      <span class="token key atrule">secretName</span><span class="token punctuation">:</span> croupier<span class="token punctuation">-</span>tls</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="证书验证" tabindex="-1"><a class="header-anchor" href="#证书验证"><span>证书验证</span></a></h2>
<h3 id="验证证书文件存在" tabindex="-1"><a class="header-anchor" href="#验证证书文件存在"><span>验证证书文件存在</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token keyword">bool</span> <span class="token function">ValidateCertFiles</span><span class="token punctuation">(</span><span class="token keyword">const</span> ClientConfig<span class="token operator">&amp;</span> config<span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>ifstream <span class="token function">cert</span><span class="token punctuation">(</span>config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>cert_file<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>ifstream <span class="token function">key</span><span class="token punctuation">(</span>config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>key_file<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    std<span class="token double-colon punctuation">::</span>ifstream <span class="token function">ca</span><span class="token punctuation">(</span>config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>ca_file<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token operator">!</span>cert<span class="token punctuation">.</span><span class="token function">good</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>cerr <span class="token operator">&lt;&lt;</span> <span class="token string">"证书文件不存在: "</span> <span class="token operator">&lt;&lt;</span> config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>cert_file <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">        <span class="token keyword">return</span> <span class="token boolean">false</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line">    <span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token operator">!</span>key<span class="token punctuation">.</span><span class="token function">good</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>cerr <span class="token operator">&lt;&lt;</span> <span class="token string">"私钥文件不存在: "</span> <span class="token operator">&lt;&lt;</span> config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>key_file <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">        <span class="token keyword">return</span> <span class="token boolean">false</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line">    <span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token operator">!</span>ca<span class="token punctuation">.</span><span class="token function">good</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">        std<span class="token double-colon punctuation">::</span>cerr <span class="token operator">&lt;&lt;</span> <span class="token string">"CA 文件不存在: "</span> <span class="token operator">&lt;&lt;</span> config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>ca_file <span class="token operator">&lt;&lt;</span> std<span class="token double-colon punctuation">::</span>endl<span class="token punctuation">;</span></span>
<span class="line">        <span class="token keyword">return</span> <span class="token boolean">false</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token punctuation">}</span></span>
<span class="line"></span>
<span class="line">    <span class="token keyword">return</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="验证证书有效期" tabindex="-1"><a class="header-anchor" href="#验证证书有效期"><span>验证证书有效期</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 检查证书有效期</span></span>
<span class="line">openssl x509 <span class="token parameter variable">-in</span> /etc/tls/client.crt <span class="token parameter variable">-noout</span> <span class="token parameter variable">-dates</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 输出示例:</span></span>
<span class="line"><span class="token comment"># notBefore=Jan  1 00:00:00 2024 GMT</span></span>
<span class="line"><span class="token comment"># notAfter=Dec 31 23:59:59 2024 GMT</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="最佳实践" tabindex="-1"><a class="header-anchor" href="#最佳实践"><span>最佳实践</span></a></h2>
<h3 id="_1-永不在生产环境使用-insecure-true" tabindex="-1"><a class="header-anchor" href="#_1-永不在生产环境使用-insecure-true"><span>1. 永不在生产环境使用 <code v-pre>insecure: true</code></span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token comment">// 开发环境</span></span>
<span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">ifdef</span> <span class="token expression">DEBUG</span></span></span>
<span class="line">config<span class="token punctuation">.</span>insecure <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">else</span></span></span>
<span class="line">config<span class="token punctuation">.</span>insecure <span class="token operator">=</span> <span class="token boolean">false</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token macro property"><span class="token directive-hash">#</span><span class="token directive keyword">endif</span></span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="_2-使用密钥管理系统" tabindex="-1"><a class="header-anchor" href="#_2-使用密钥管理系统"><span>2. 使用密钥管理系统</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token comment">// 从 Vault 获取证书</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>string cert <span class="token operator">=</span> vault<span class="token double-colon punctuation">::</span><span class="token function">GetSecret</span><span class="token punctuation">(</span><span class="token string">"croupier/tls/client.crt"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">std<span class="token double-colon punctuation">::</span>string key <span class="token operator">=</span> vault<span class="token double-colon punctuation">::</span><span class="token function">GetSecret</span><span class="token punctuation">(</span><span class="token string">"croupier/tls/client.key"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line"><span class="token comment">// 写入临时文件</span></span>
<span class="line"><span class="token function">WriteTempFile</span><span class="token punctuation">(</span><span class="token string">"/tmp/client.crt"</span><span class="token punctuation">,</span> cert<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"><span class="token function">WriteTempFile</span><span class="token punctuation">(</span><span class="token string">"/tmp/client.key"</span><span class="token punctuation">,</span> key<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>cert_file <span class="token operator">=</span> <span class="token string">"/tmp/client.crt"</span><span class="token punctuation">;</span></span>
<span class="line">config<span class="token punctuation">.</span>security<span class="token punctuation">.</span>key_file <span class="token operator">=</span> <span class="token string">"/tmp/client.key"</span><span class="token punctuation">;</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="_3-定期轮换证书" tabindex="-1"><a class="header-anchor" href="#_3-定期轮换证书"><span>3. 定期轮换证书</span></a></h3>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 证书轮换脚本</span></span>
<span class="line"><span class="token comment">#!/bin/bash</span></span>
<span class="line"><span class="token comment"># rotate-certs.sh</span></span>
<span class="line"></span>
<span class="line"><span class="token comment"># 1. 生成新证书</span></span>
<span class="line"><span class="token comment"># 2. 更新 Kubernetes Secret</span></span>
<span class="line"><span class="token comment"># 3. 重启 Pod（逐步滚动更新）</span></span>
<span class="line"></span>
<span class="line">kubectl create secret tls croupier-tls-new <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">--cert</span><span class="token operator">=</span>/path/to/new-client.crt <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">--key</span><span class="token operator">=</span>/path/to/new-client.key</span>
<span class="line"></span>
<span class="line">kubectl rolling-update game-server <span class="token punctuation">\</span></span>
<span class="line">  <span class="token parameter variable">--image</span><span class="token operator">=</span>game-server:new-version</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="_4-证书监控" tabindex="-1"><a class="header-anchor" href="#_4-证书监控"><span>4. 证书监控</span></a></h3>
<div class="language-cpp line-numbers-mode" data-highlighter="prismjs" data-ext="cpp"><pre v-pre><code class="language-cpp"><span class="line"><span class="token comment">// 检查证书是否即将过期</span></span>
<span class="line"><span class="token keyword">bool</span> <span class="token function">CheckCertExpiry</span><span class="token punctuation">(</span><span class="token keyword">const</span> std<span class="token double-colon punctuation">::</span>string<span class="token operator">&amp;</span> cert_file<span class="token punctuation">,</span> <span class="token keyword">int</span> days_before <span class="token operator">=</span> <span class="token number">30</span><span class="token punctuation">)</span> <span class="token punctuation">{</span></span>
<span class="line">    <span class="token comment">// 读取证书</span></span>
<span class="line">    FILE<span class="token operator">*</span> fp <span class="token operator">=</span> <span class="token function">fopen</span><span class="token punctuation">(</span>cert_file<span class="token punctuation">.</span><span class="token function">c_str</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">,</span> <span class="token string">"r"</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    X509<span class="token operator">*</span> cert <span class="token operator">=</span> <span class="token function">PEM_read_X509</span><span class="token punctuation">(</span>fp<span class="token punctuation">,</span> <span class="token keyword">nullptr</span><span class="token punctuation">,</span> <span class="token keyword">nullptr</span><span class="token punctuation">,</span> <span class="token keyword">nullptr</span><span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token function">fclose</span><span class="token punctuation">(</span>fp<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line"></span>
<span class="line">    <span class="token comment">// 检查有效期</span></span>
<span class="line">    ASN1_TIME<span class="token operator">*</span> notAfter <span class="token operator">=</span> <span class="token function">X509_get0_notAfter</span><span class="token punctuation">(</span>cert<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token comment">// ... 解析并比较日期</span></span>
<span class="line"></span>
<span class="line">    <span class="token function">X509_free</span><span class="token punctuation">(</span>cert<span class="token punctuation">)</span><span class="token punctuation">;</span></span>
<span class="line">    <span class="token keyword">return</span> is_expiring_soon<span class="token punctuation">;</span></span>
<span class="line"><span class="token punctuation">}</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h2 id="故障排查" tabindex="-1"><a class="header-anchor" href="#故障排查"><span>故障排查</span></a></h2>
<h3 id="证书验证失败" tabindex="-1"><a class="header-anchor" href="#证书验证失败"><span>证书验证失败</span></a></h3>
<div class="language-text line-numbers-mode" data-highlighter="prismjs" data-ext="text"><pre v-pre><code class="language-text"><span class="line">错误: SSL verification failed</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>解决方案：</strong></p>
<ol>
<li>检查 CA 文件路径</li>
<li>确认 <code v-pre>server_name</code> 与证书 CN 匹配</li>
<li>验证证书未过期</li>
</ol>
<h3 id="私钥不匹配" tabindex="-1"><a class="header-anchor" href="#私钥不匹配"><span>私钥不匹配</span></a></h3>
<div class="language-text line-numbers-mode" data-highlighter="prismjs" data-ext="text"><pre v-pre><code class="language-text"><span class="line">错误: Private key does not match certificate</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>解决方案：</strong></p>
<div class="language-bash line-numbers-mode" data-highlighter="prismjs" data-ext="sh"><pre v-pre><code class="language-bash"><span class="line"><span class="token comment"># 验证私钥和证书匹配</span></span>
<span class="line">openssl x509 <span class="token parameter variable">-noout</span> <span class="token parameter variable">-modulus</span> <span class="token parameter variable">-in</span> client.crt <span class="token operator">|</span> openssl md5</span>
<span class="line">openssl rsa <span class="token parameter variable">-noout</span> <span class="token parameter variable">-modulus</span> <span class="token parameter variable">-in</span> client.key <span class="token operator">|</span> openssl md5</span>
<span class="line"></span>
<span class="line"><span class="token comment"># 两个输出应该相同</span></span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div><div class="line-number"></div></div></div><h3 id="连接超时" tabindex="-1"><a class="header-anchor" href="#连接超时"><span>连接超时</span></a></h3>
<div class="language-text line-numbers-mode" data-highlighter="prismjs" data-ext="text"><pre v-pre><code class="language-text"><span class="line">错误: Connection timeout</span>
<span class="line"></span></code></pre>
<div class="line-numbers" aria-hidden="true" style="counter-reset:line-number 0"><div class="line-number"></div></div></div><p><strong>解决方案：</strong></p>
<ol>
<li>检查网络连接</li>
<li>确认 Agent 地址正确</li>
<li>检查防火墙规则</li>
<li>验证 <code v-pre>server_name</code> 可解析</li>
</ol>
</div></template>


