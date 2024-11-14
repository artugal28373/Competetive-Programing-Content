# [[Tutorial] Zeta, Mobius Transform to AND, OR, GCD Convolution](https://codeforces.com/blog/entry/119082)

![image](https://github.com/user-attachments/assets/d3af1634-51b9-4b63-9686-d686dce04d7d)

# superset and subset sum

Using the definition of $μ(s, t)$, for $s⊆t$, $μ(s,t)$ is $(-1)^{|t \setminus s|}$.

$g(t) = \sum_{s \subseteq t}{f(s)}$ <br>
$f(t) = \sum_{s \subseteq t}{(-1)^{|t \setminus s|}g(s)}$<br>


<br><br>
# When $S$ is $N$(natural numbers) and $≤$ is the divisor relation<br>
In this case, when $d|n$, $μ(d,n$) is equal to $μ(n/d)$. Here, $μ(x)$ is the Mobius function in number theory. If $x$ has no square factors, then $μ(x)$ is equal to $(−1)^k$, where $k$ is the number of prime factors of $x$. Otherwise, $μ(x)$ is $0$.<br>
$g(n) = \sum_{d | n}{f(d)}$<br>
$f(n) = \sum_{d | n}{μ(n / d)g(d)}$
<br>
# When $S$ is $N$(natural numbers) and $≤$ is the multiple relation<br>
$g(n) = \sum_{n | m}{f(m)}$<br>
$f(n) = \sum_{n | m}{μ(m / n)g(m)}$
