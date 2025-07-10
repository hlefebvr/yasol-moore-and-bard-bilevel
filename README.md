# Solving a Bilevel Problem with Yasol

This repo contains an example of how to use the [Yasol solver](https://tm-vm-2.wiwi.uni-siegen.de/about-yasol.html) for
quantified integer programming (QIP) to solve a bilevel problem.

We consider the famous Moore and bard example, given as follows.

$$
\begin{align*}
\min_{x,y} \quad & -x - 10y \\
\text{s.t.} \quad & y\in
\begin{array}[t]{rl}
\text{argmin}_{\bar{y}} \quad & \bar{y} \\
\text{s.t.} \quad & -25x + 20\bar{y} \le 30, \\
& x + 2 \bar{y} \le 10, \\
& 2 x - \bar{y} \le 15, \\
& 2 x + 10 \bar{y} \ge 15
\end{array}
\end{align*}
$$

We can formulate this problem as a QIP problem using the extended single-level formulation. 

$$
\begin{align*}
\min_{x,y} \quad & -x - 10y \\
\text{s.t.} \quad & -25x + 20y \le 30, \\
& x + 2 y \le 10, \\
& 2 x - y \le 15, \\
& 2 x + 10 y \ge 15, \\
& y \le \bar{y} \quad \text{for all } \bar{y}\in Y(x).
\end{align*}
$$

Here, $Y(x)$ is given by 
$$
Y(x) := \left\{
\bar{y} :
\begin{array}{l}
-25x + 20\bar{y} \le 30, \\
x + 2 \bar{y} \le 10, \\
2 x - \bar{y} \le 15, \\
2 x + 10 \bar{y} \ge 15
\end{array}
\right\}.
$$