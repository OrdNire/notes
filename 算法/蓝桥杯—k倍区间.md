原题链接：[k倍区间](https://www.acwing.com/problem/content/1232/)

### 题目描述

给定一个长度为 $N$ 的数列，$A_1,A_2,…A_N$，如果其中一段连续的子序列 $A_i,A_{i+1},…A_j$ 之和是 $K$ 的倍数，我们就称这个区间 $[i,j]$ 是 $K$倍区间。  

你能求出数列中总共有多少个 $K$ 倍区间吗？  

##### 输入格式

第一行包含两个整数 $N$ 和 $K$

以下 $N$ 行每行包含一个整数 $A_i$。

##### 输出格式

输出一个整数，代表 $K$ 倍区间的数目。

#### 数据范围

$1≤N,K≤100000$,
$1≤A_i≤100000$

##### 输入样例1：

```
5 2
1
2
3
4
5
```

##### 输出样例1：

```
6
```



### 思路

按照朴素的做法，我们需要枚举区间端点，这个的复杂度是$O(n^2)$。然后再用$O(n)$ 的复杂度求出区间的总和，看看其是否是$k$的倍数。此时必定超时。

可以看出，求区间总和我们可以利用前缀和将复杂度降到$O(1)$，那么总的复杂度就会降到$O(n^2)$，但是仍然会超时，所以我们需要想更优化的方案

我们在枚举左端点的时候，其实可以先枚举右端点，`(s[r] - s[l - 1]) % k == 0` ，所以如果对于`0 ~ r - 1`，我们只需要知道`s[l]与 s[r]`模k同余的个数，所以我们可以利用`cnt`数组来记录每一个`r % k`的值，然后对于枚举每一`r`，结果加上`cnt[s[r] % k]`的个数即可

### 前缀和同余优化

#### 时间复杂度

$O(n)$

#### C++ 代码
```c
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 100010;

LL cnt[N], s[N];
int n, k;

int main()
{
    cin >> n >> k;
    
    for(int i = 1;i <= n;i ++) {
        int x;
        scanf("%d",&x);
        s[i] = s[i - 1] + x;
    }
    
    LL res = 0;
    cnt[0] ++;  // s[0] = 0,0 % k = 0;
    for(int r = 1;r <= n;r ++) {
        res += cnt[s[r] % k];
        cnt[s[r] % k] ++;
    }
    
    cout << res << endl;
    return 0;
}
```

----------