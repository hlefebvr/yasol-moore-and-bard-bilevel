# Solving a Bilevel Problem with Yasol

This repo contains an example of how to use the [Yasol solver](https://tm-vm-2.wiwi.uni-siegen.de/about-yasol.html) for
quantified integer programming (QIP) to solve a bilevel problem.

We consider the famous Moore and Bard example, given as follows.

$$
\begin{align*}
\min_{x,y} \quad & -x - 10y \\
\text{s.t.} \quad & y\in
\begin{array}{rl}
\text{argmin}_{\Bar{y}} \quad & y \\
-25x + 20\Bar{y} \le 30, \\
x + 2 \Bar{y} \le 10, \\
2 x - \Bar{y} \le 15, \\
2 x + 10 \Bar{y} \ge 15
\end{array}
\end{align*}
$$