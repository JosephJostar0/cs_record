# 数学女孩

## 斐波那契通项公式

假定斐波那契数列的第$`i`$项为$`f_i`$

```math
\begin{aligned}
\text{生成函数：} \quad
F(z) &= \sum_{i=0}^{\infty} f_i z^i = 0 + z + z^2 + 2z^3 + \dots \\

\text{我们发现：} \quad
F(z) &= z + z F(z) + z^2 F(z), \\

\text{因此：} \quad
F(z) &= \frac{z}{1 - z - z^2} \\

      &= \frac{z}{\big(1 - \frac{1+\sqrt{5}}{2} z\big)\big(1 - \frac{1-\sqrt{5}}{2} z\big)} \\

      &= \frac{1}{\sqrt{5}} \left( 
          \frac{1}{1 - \frac{1+\sqrt{5}}{2} z} 
          - \frac{1}{1 - \frac{1-\sqrt{5}}{2} z} 
      \right). \\

\text{由于：} \quad
\frac{1}{1-x} &= \sum_{n=0}^{\infty} x^n, \\

\text{所以：} \quad
F(z) &= \frac{1}{\sqrt{5}} \sum_{n=0}^{\infty} 
      \left[ 
          \left(\frac{1+\sqrt{5}}{2}\right)^n 
          - \left(\frac{1-\sqrt{5}}{2}\right)^n
      \right] z^n. \\

\text{于是：} \quad
f_i &= \frac{1}{\sqrt{5}} \left[ 
          \left(\frac{1+\sqrt{5}}{2}\right)^n 
          - \left(\frac{1-\sqrt{5}}{2}\right)^n
      \right].
\end{aligned}
```
