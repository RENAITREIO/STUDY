# Signals and Systems

continuous-time signal, discrete-time signal  
n-dimensional signal  
$x(t)/x[n]$ -> System -> $y(t)/y[n]$    
linear/non-linear  
time-invariant/time-varing  
Linear Time-Invariant(LTI)  
series, parallel and feedback interconnection  
time domain, frequency domain
- Fourier transform
- Laplace transform
- Z-Transform

time shift <=> phase change(continuous)  
time shift => phase change(discrete)  
${cos[Ωt+φ]=cos[(Ω+2πm)t+φ]}$ (discrete)  
if ${Ce^{jΩ_0n}}$ is periodic depends on $Ω_0$

$δ[n]=u[n]-u[n-1]$  
$u[n]=\sum_{m=-∞}^n δ[m]$

$δ(t)=\frac{du(t)}{dt}$  
$u(t)=\int_{-∞}^t δ(τ)\ dτ$

system properties: memoryless, invertability, causality, stability, time invariant, linearity

LTS system:  
delayed impulses <=> convolution  
complex exponentials <=> Fourier analysis

convolution:  
$x[t]=\sum_{k=-∞}^{+∞} x[k]\ δ[t-k]$  
$δ[t]$ -> LTI System -> $h[t]$  
$y[n]=\sum_{k=-∞}^{+∞} x[k]\ h[n-k]$

$x(t)=\int_{-∞}^{+∞} x(τ)\ δ(t-τ)\ dτ$  
$δ(t)$ -> LTI System -> $h(t)$  
$y(t)=\int_{-∞}^{+∞} x(τ)\ h(t-τ)\ dτ$

$x(t)*h(t)=\int_{-∞}^{+∞} x(τ)\ h(t-τ)\ dτ$  
commutative, associative, distributive

memoryless => $h(t)=kδ(t)$ / $h[n]=kδ[n]$ => $y(t)=kx(t)$ / $y[n]=kδ[n]$  
invertibility: $y=x*(h*h^{-1})=x$, only need $h*h^{-1}=δ$  
stability => $\sum_{k=-∞}^{+∞} |h[x]|<∞$ / $\int_{-∞}^{+∞} |h(τ)|\ dτ<∞$  
zero input response: $x(t)=0$ => $y(t)=0$  
causality: if linear system, $x(t)=0(t<t_0)$,then $y(t)=0(t<t_0)$  
if LTI system, causality(initial rest) <=> $h(t)=0(t<0)$ -> $y(t)=\int_{-∞}^t x(τ)\ h(t-τ)\ dτ$

singularity functions defination: $δ(t)$ -> $\int$-> ... -> $\int$ -> $u_m(t)$, then $x(t)*u_m(t)=\frac{d^mδ(t)}{dt^m}$

$u(t) => s(t)$, then $h(t)=\frac{ds(t)}{dt}$  
$y[t]=bx[t]+\sum_{k=1}^m b_mx[n-k]-\sum_{k=1}^n a_ky[n-k]$, then two system exchange, merge two delay components(for continuous time, components are $\int$)  

eigenfunction means that if put it in system, its change only in amplitude, the changing amplitude being the eigenvalue

Fourier series: $x(t)=\sum_{k=-∞}^{+∞} a_ke^{jkω_0t}$, $a_k=\frac{1}{T_0}\int_{T_0}x(t)e^{-jkω_0t}$  
Fourier transform: $x(t)=\int_{-∞}^{+∞}X(ω)e^{jωt}\ dω$, $X(ω)=\frac{1}{2π}\int_{-∞}^{+∞}x(t)e^{-jωt}\ dt$  
$e^{-at}u(t)$ <-> $\frac{1}{a+jω}(a>0)$  
Fourier series are samples in Fourier transform($T_0a_k=X(ω)|_{ω=kω_0}$)

properties:  
$x(t)$ real => $X(-ω) = X^*(ω)$, even function: $Re\ X(ω)$, $|X(ω)|$, odd function: $Im\ X(ω)$, $φ(θ)$  
$x(at)$ <-> $\frac{1}{|a|}X(\frac{ω}{a})$  
$x(t)$ <-> $X(ω)$ <=> $X(t)$ <-> $2πx(- ω)$  
Parseval's relation: $\int_{-∞}^{+∞}|x(t)|^2\ dt=\frac{1}{2π}\int_{-∞}^{+∞}|X(ω)|^2\ dω$  
$\frac{1}{T_0}\int_{T_0}|\widetilde{x}(t)|^2\ dt=\sum_{k=-∞}^{+∞}|a_k|^2$  
time shifting: $x(t-t_0)$ <-> $X(ω)e^{-jωt_0}$  
differentiation: $\frac{dx(t)}{dt}$ <-> $jωX(ω)$  
integration: $\int_{-∞}^tx(τ)\ dτ$ <-> $\frac{1}{jω}X(ω)+πX(0)δ(ω)$  
linearity: $ax_1(t)+bx_2(t)$ <-> $aX_1(ω)+bX_2(ω)$

convolution: $x(t)*h(t)$ <-> $X(ω)H(ω)$  
modulation: $s(t)p(t)$ <-> $\frac{1}{2π}S(ω)*P(ω)$

$e^{jω_0t}$ -> LTI system(H(ω)) -> $e^{jω_0t}H(ω_0)$(H(ω) is frequency response)  
filtering: ideal lowpass filter, differentiator

$e^{jkΩ_0n}=e^{j(k+N)Ω_0n}, Ω_0=\frac{2π}{N}$  
$x[n]=\sum_{k=<N>}a_ke^{jkΩ_0n}, k=0,1,...,N-1$  
$a_k=\frac{1}{N}\sum_{k=<N>}x[n]e^{-jkΩ_0n}$  
$x[n]$ periodic in n(or t), $e^{j(k+N)Ω_0n}$ periodic in n(or t)  
$e^{j(k+N)Ω_0n}$ periodic in k, $a_k$ periodic in k  
Fourier transform: $x[n]=\frac{1}{2π}\int_{2π}X(Ω)e^{jΩn}\ dΩ$, $X(Ω)=\sum_{n=-∞}^{+∞}x[n]e^{-jΩn}$  
properties:  
periodic: $X[Ω]=X(Ω+2πm)$  
symmetry: $x[n]$ real => $X(-Ω)=X^*(Ω)$, even function: $Re\ X(Ω)$, $|X(Ω)|$, odd function: $Im\ X(Ω)$, $φ(Ω)$  
time shifting: $x[n-n_0]$ <-> $X(Ω)e^{-jΩn_0}$  
frequency shifting: $e^{jΩ_0n}x[n]$ <-> $X(Ω-Ω_0)$  
linearity: $ax_1[n]+bx_2[n]$ <-> $aX_1(Ω)+bX_2(Ω)$  
Parseval's relation: $\sum_{n=-∞}^{+∞}|x[n]|^2=\frac{1}{2π}\int_{2π}|X(Ω)|^2\ dΩ$  
convolution: $x[n]*h[n]$ <-> $X(Ω)H(Ω)$  
modulation: $s[n]p[n]$ <-> $\frac{1}{2π}S(Ω)*P(Ω)$  
$x[n](-1)^n$ => $X(Ω-π)$ ($(-1)^n=e^{jπn}$)  

non-recursive filters  
three-point moving average: $y[n]=\frac{1}{3}\{x[n-1]+x[n]+x[n+1]\}$   
recursive discrete-time filters  
$\sum_{k=0}^Na_k\ y[n-k]=\sum_{k=0}^Na_k\ x[n-k]$  
first order: $y[n]-ay[n-1]=x[n]$  
