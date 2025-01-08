# 数学女孩

## 斐波那契通项公式

假定斐波那契数列的第$i$项为$f_i$  

```math
\begin{aligned}
生成函数
F(z) &= \sum_{i=0}^{\infty} f_i z^i = 0 + z + z^2 + 2 z^3 + \dots \\

发现 F(z) &= z + z F(z) + z^2 F(z) \\
故 F(z) &= \frac{z}{1 - z - z^2} \\

        &= \frac{z}{(1 - \frac{1+\sqrt{5}}{2} z)(1 - \frac{1-\sqrt{5}}{2} z)} \\

        &= \frac{1}{\sqrt{5}} (\frac{1}{
            1-\frac{1+\sqrt{5}}{2} z
        } - \frac{1}{
            1-\frac{1-\sqrt{5}}{2} z
        }) \\

由于 \frac{1}{1-x} &= \sum_{n=0}^{\infty} x^n \\

故 F(z) &= \frac{1}{\sqrt{5}} \sum_{n=0}^{\infty} \big((\frac{1+\sqrt{5}}{2})^n - (\frac{1-\sqrt{5}}{2})^n\big) z^n \\

则 f_i &= \frac{1}{\sqrt{5}} \big((\frac{1+\sqrt{5}}{2})^n - (\frac{1-\sqrt{5}}{2})^n\big) \\
\end{aligned}
```
