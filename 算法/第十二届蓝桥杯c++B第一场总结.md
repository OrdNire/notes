# 第十二届蓝桥杯c++B组第一场



### A 空间

小蓝准备用 256MB 的内存空间开一个数组，数组的每个元素都是 32 位 二进制整数，如果不考虑程序占用的空间和维护内存需要的辅助空间，请问 256MB 的空间可以存储多少个 32 位二进制整数？

**思路**

$$256 MB = 256 * 1024 KB = 256 * 1024 * 1024 B$$

**答案**

```
67108864
```



### B 卡片

小蓝有很多数字卡片，每张卡片上都是数字 0 到 9。 

小蓝准备用这些卡片来拼一些数，他想从 1 开始拼出正整数，每拼一个， 就保存起来，卡片就不能用来拼其它数了。 

小蓝想知道自己能从 1 拼到多少。 

例如，当小蓝有 30 张卡片，其中 0 到 9 各 3 张，则小蓝可以拼出 1 到 10， 但是拼 11 时卡片 1 已经只有一张了，不够拼出 11。

 现在小蓝手里有 0 到 9 的卡片各 2021 张，共 20210 张，请问小蓝可以从 1 拼到多少？ 提示：建议使用计算机编程解决问题。

**思路**

哈希表存每种卡片的个数，然后枚举每种数字，看是否能凑出来

**答案**

```
3181
```

**代码**

```c++
#include <iostream>
using namespace std;

const int N = 10;
int s[N];

bool check(int x) {
	
	while(x) {
		s[x % 10] --;
		if(s[x % 10] < 0) return false;
		x /= 10;
	}
	return true;
}

int main()
{
	for(int i = 0;i < 10;i ++) s[i] = 2021;
	
	for(int i = 1;i;i ++) {
		if(!check(i)) {
			cout << i - 1 << endl;
			break;
		}
	}
	return 0;
}
```



### C 直线

在平面直角坐标系中，两点可以确定一条直线。如果有多点在一条直线上，那么这些点中任意两点确定的直线是同一条。

给定平面上 2 × 3 个整点 {(x, y)|0 ≤ x < 2, 0 ≤ y < 3, x ∈ Z, y ∈ Z}，即横坐标是 0 到 1 (包含 0 和 1) 之间的整数、纵坐标是 0 到 2 (包含 0 和 2) 之间的整数的点。这些点一共确定了 11 条不同的直线。

给定平面上 2 × 3 个整点 {(x, y)|0 ≤ x < 2, 0 ≤ y < 3, x ∈ Z, y ∈ Z}，即横坐标是 0 到 1 (包含 0 和 1) 之间的整数、纵坐标是 0 到 2 (包含 0 和 2) 之间的整数的点。这些点一共确定了 11 条不同的直线。



**思路**

首先一条直线可以被 $y = kx + b$ 唯一表示，那么我们只需要枚举所有点然后求出 $k$ 和 $b$ 来表示一条直线，最后判断有多少条不同的直线即可。

**但是，因为浮点数有误差，所以需要判断两个值的差是否在  1e-8 范围内，如果在，表示为同一个值。其次，因为斜率可以不存在，那么此时 $k$ 不存在，在枚举的时候先不考虑竖线（即两点横坐标相同），最后答案再加上竖线的条数 20 即可**

**答案**

```
40257
```

**代码**

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 2000000;	// (20 * 20)^2

struct Line {
	double k, b;
	bool operator< (const Line &t) const {
		if(k != t.k) return k < t.k;
		return b < t.b;
	}
}line[N];
int n;

int main()
{
	for(int x1 = 0;x1 < 20;x1 ++)
		for(int y1 = 0;y1 < 21;y1 ++)
			for(int x2 = 0;x2 < 20;x2 ++)
				for(int y2 = 0;y2 < 21;y2 ++)
					if(x1 != x2) {
						double k = (double)(y2 - y1)/(x2 - x1);
						double b = y1 - k * x1;
						line[n ++] = {k, b};
					}
					
	sort(line, line + n);
	int res = 1;
	for(int i = 1;i < n;i ++)
		if(fabs(line[i].k - line[i - 1].k) > 1e-8 || fabs(line[i].b - line[i - 1].b) > 1e-8)
			res ++;
	
	cout << res + 20 << endl;		
	return 0;
}

```



### D 货物摆放

小蓝有一个超大的仓库，可以摆放很多货物。

现在，小蓝有 $n$ 箱货物要摆放在仓库，每箱货物都是规则的正方体。小蓝 规定了长、宽、高三个互相垂直的方向，每箱货物的边都必须严格平行于长、 宽、高。

小蓝希望所有的货物最终摆成一个大的立方体。即在长、宽、高的方向上 分别堆 $L,W,H$ 的货物，满足 $n = L × W × H。$

给定 $n$，请问有多少种堆放货物的方案满足要求。

例如，当 $n$ = 4 时，有以下 6 种方案：1×1×4、1×2×2、1×4×1、2×1×2、 2 × 2 × 1、4 × 1 × 1。

请问，当 n = 2021041820210418 （注意有 16 位数字）时，总共有多少种 方案？

**思路**

如果直接枚举，那么时间复杂度过大，必然枚举不出来，可以发现 n 必然是由它的约数的不同组合构成，所以我们可以先求出 n 的所有约数，然后枚举约数。约数个数大概是 $logn$ 级别，所以有限时间内可以枚举出来答案

**答案**

```
2430
```

**代码**

```c++
#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;

int main()
{
	LL n;
	cin >> n;
	vector<LL> d;
	
	for(LL i = 1;i * i <= n;i ++) {
		if(n % i == 0) {
			d.push_back(i);
			if(n / i != i) d.push_back(n / i);
		}
	}
	
	int res = 0;
	for(auto a : d)
		for(auto b : d)
			for(auto c : d)
				if(a * b * c == n)
					res ++;
	
	cout << res << endl;
	
	return 0;
}
```



### E 路径

小蓝学习了最短路径之后特别高兴，他定义了一个特别的图，希望找到图 中的最短路径。

小蓝的图由 2021 个结点组成，依次编号 1 至 2021。

对于两个不同的结点 a, b，如果 a 和 b 的差的绝对值大于 21，则两个结点 之间没有边相连；如果 a 和 b 的差的绝对值小于等于 21，则两个点之间有一条 长度为 a 和 b 的最小公倍数的无向边相连。

例如：结点 1 和结点 23 之间没有边相连；结点 3 和结点 24 之间有一条无 向边，长度为 24；结点 15 和结点 25 之间有一条无向边，长度为 75。

请计算，结点 1 和结点 2021 之间的最短路径长度是多少。

**思路**

一道最短路板子题，可以用各种最短路算法做，这里用spfa

**答案**

```
10266837
```

**代码**

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 2200, M = N * N;
int h[N], ne[M], e[M], w[M], idx;
int dist[N];
bool st[N];
int n;

void add(int a, int b, int c) {
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}


void spfa() {
	
	memset(dist, 0x3f, sizeof dist);
	dist[1] = 0;
	
	queue<int> q;
	q.push(1);
	st[1] = 1;
	
	while(q.size()) {
		
		int t = q.front();
		q.pop();
		
		st[t] = 0;
		
		for(int i = h[t];i != -1;i = ne[i]) {
			int j = e[i];
			if(dist[j] > dist[t] + w[i]) {
				dist[j] = dist[t] + w[i];
				if(!st[j]) {
					q.push(j);
					st[j] = 1;
				}
			}
		}
	}
	

}


int main()
{
	n = 2021;
	memset(h, -1, sizeof h);
	for(int i = 1;i <= n;i ++)
		for(int j = 1; j <= n;j ++)
			if(i != j) {
				if(abs(i - j) <= 21) {
					int d = gcd(i, j);
					add(i, j, i * j / d);
					add(j, i, i * j / d);
				}
			}
				
	spfa();
	cout << dist[n] << endl;
	return 0;
}
```



### F 时间显示

[原题链接](https://www.acwing.com/problem/content/3419/)

小蓝要和朋友合作开发一个时间显示的网站。

在服务器上，朋友已经获取了当前的时间，用一个整数表示，值为从 1970 年 1 月 1 日 00:00:00 到当前时刻经过的毫秒数。

现在，小蓝要在客户端显示出这个时间。

小蓝不用显示出年月日，只需要显示出时分秒即可，毫秒也不用显示，直接舍去即可。

给定一个用整数表示的时间，请将这个时间对应的时分秒输出。

**输入格式**

输入一行包含一个整数，表示时间。

**输出格式**

输出时分秒表示的当前时间，格式形如 `HH:MM:SS`，其中 `HH` 表示时，值为 0 到 23，`MM` 表示分，值为 0 到 59，`SS` 表示秒，值为 0 到 59。

时、分、秒不足两位时补前导 0。

**数据范围**

对于所有评测用例，给定的时间为不超过 $$10^18$$ 的正整数。

**输入样例1：**

```
46800999
```

**输出样例1：**

```
13:00:00
```

**输入样例2：**

```
1618708103123
```

**输出样例2：**

```
01:08:23
```



**思路**

首先转换为秒，$$n = n / 1000$$。

因为只需要输出时分秒，所以可以去掉日期的描述，余下的值就是当前日期的描述，$$n = n \% (24 * 60 * 60)$$。

所以小时为 $$h = n / (60 * 60)$$。

然后去掉小时，余下的值就为分钟和秒总共的秒数，$$n = n \% (60 * 60)$$。

所以分钟为 $$m = n / 60$$。

去掉分钟的秒数，$$n = n % 60$$。

所以秒数为 $$n$$。

**代码**

```c++
#include <iostream>
using namespace std;

typedef long long LL;

LL n;

int main()
{
	cin >> n;
	// 1s = 1000ms, 1 minus = 60s, 1 hour = 60 minus, 1 day = 24 hour
	
	n = n / 1000;	// 秒  
	n = n % (24 * 60 * 60);	// 去掉日期， 只留当前天的秒 
	
	int h = n / (60 * 60);
	
	n = n % (60 * 60);	// 去掉小时的整秒数 
	
	int m = n / 60;	// 分钟
	
	n = n % 60;		// 去掉整分钟 
	
	int s = n;
	
	printf("%02d:%02d:%02d\n", h, m, s);
	return 0;
}
```



### G 砝码称重

[原题链接](https://www.acwing.com/problem/content/3420/)

你有一架天平和 $N$ 个砝码，这 $N$ 个砝码重量依次是 $W_1,W_2,⋅⋅⋅,W_N。$

请你计算一共可以称出多少种不同的正整数重量？

注意砝码可以放在天平两边。

**输入格式**

输入的第一行包含一个整数 $N。$

第二行包含 $N$ 个整数：$W_1,W_2,W_3,⋅⋅⋅,W_N。$

**输出格式**

输出一个整数代表答案。

**数据范围**

对于 $50\%$ 的评测用例，$1≤N≤15。$

对于所有评测用例，$1≤N≤100，N$ 个砝码总重不超过 $105。$

**输入样例1：**

```
3
1 4 6
```

**输出样例1：**

```
10
```

**样例说明：**

能称出的 10 种重量是：1、2、3、4、5、6、7、9、10、11。
```
1 = 1；
2 = 6 − 4 (天平一边放 6，另一边放 4)；
3 = 4 − 1；
4 = 4；
5 = 6 − 1；
6 = 6；
7 = 1 + 6；
9 = 4 + 6 − 1；
10 = 4 + 6；
11 = 1 + 4 + 6。
```

**思路**

因为砝码可以放左边，右边，和不放三种状态，但是最终结果是两边的差值，所以我们可以用正数代表放左边，负数代表放右边，0代表不放，那么对于每一种砝码都是有这三种，**问题化归到有限的选择问题，即背包问题**

状态表示：$F_{i,j}$ 表示从前 $i$ 个物品中选，重量为 $j$ 的方案

属性：bool 值，表示是否存在该方案

状态转移分析

首先找最后一个不同点，那么 $F_{i,j}$ 最后的不同点在于选第 $i$ 个物品的方式，又上述可知，有三种，所以得出

对于不选第 $i$ 类物品：$F_{i-1,j}$

选第 $i$ 类物品且放左边：$F_{i - 1, j - w_i}$，因为放左边表示该值是正数，需要去掉该值由前面的状态转移而来

选第 $i$ 类物品且放右边：$F_{i - 1, j + w_i}$，因为放右边，该值为负数

注意：选第 $i$ 类放左边需要满足 $j >= w_i$，同理右边 $j >= -w_i$

那么就可以上代码实现，注意一点，因为数组下标只能用正数，而 $j$ 的范围在 $[-m, m](m 为砝码总重)$ ，所以可以加一个偏移量，使之全落到正区间上

**代码**

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 110, M = 200010, B = M / 2;
bool f[N][M];
int w[N];
int n, m;

int main()
{
    cin >> n;
    for(int i = 1;i <= n;i ++) cin >> w[i], m += w[i];
    
    f[0][B] = 1;
    for(int i = 1;i <= n;i ++) 
        for(int j = -m;j <= m;j ++) {
            f[i][j + B] = f[i - 1][j + B];
            if(j - w[i] >= -m) f[i][j + B] |= f[i - 1][j - w[i] + B];
            if(j + w[i] <= m) f[i][j + B] |= f[i - 1][j + w[i] + B];
        }
        
    int res = 0;
    for(int i = 1;i <= m;i ++)
        if(f[n][i + B])
            res ++;
    
    cout << res << endl;
    return 0;
}
```

 

### H 杨辉三角形

[原题链接](https://www.acwing.com/problem/content/3421/)

下面的图形是著名的杨辉三角形：

![QQ截图20210423150438.png](https://cdn.acwing.com/media/article/image/2021/04/23/19_34bec150a4-QQ截图20210423150438.png) 

如果我们按从上到下、从左到右的顺序把所有数排成一列，可以得到如下数列：

```
1, 1, 1, 1, 2, 1, 1, 3, 3, 1, 1, 4, 6, 4, 1, ...
```

给定一个正整数 $N$，请你输出数列中第一次出现 $N$ 是在第几个数？

**输入格式**

输入一个整数 $N。$

**输出格式**

输出一个整数代表答案。

**数据范围**

对于$20\%$ 的评测用例，$1≤N≤10；$

对于所有评测用例，$1≤N≤109。$

**输入样例1：**

```
6
```

**输出样例1：**

```
13
```

**思路**

![蓝桥杯12cb-img01](D:\个人资料\Notes\算法\images\蓝桥杯12cb-img01.png)

因为杨辉三角就是组合数，所以看一看如上图找出规律，然后二分每一个竖线里面的找到是否有 n 即可，如果没有 k - 1

**代码**

```c++
#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;
int n;

LL C(int a, int b) {
    
    LL res = 1;
    for(int i = a, j = 1;j <= b;i --,j ++) {
        res = res * i / j;
        if(res > n) return res;
    }
    return res;
}

bool check(int k) {
    LL l = 2 * k, r = max((LL)n, l);
    while(l < r) {
        LL mid = l + r >> 1;
        if(C(mid, k) >= n) r = mid;
        else l = mid + 1;
    }
    if(C(r, k) != n) return false;
    
    cout << r * (r + 1) / 2 + k + 1 << endl;
    
    return true;
}

int main()
{
    cin >> n;
    
    for(int k = 16;;k --)
        if(check(k))
            break;
    
    return 0;
}
```



### I 双向排序

[原题链接](https://www.acwing.com/problem/content/3422/)

给定序列 $(a_1,a_2,⋅⋅⋅,a_n)=(1,2,⋅⋅⋅,n)，$即 $a_i=i。$

小蓝将对这个序列进行 $m$ 次操作，每次可能是将 $a_1,a_2,⋅⋅⋅,a_qi$ 降序排列，或者将 $a_qi,a_{qi+1},⋅⋅⋅,a_n$ 升序排列。

请求出操作完成后的序列。


**输入格式**

输入的第一行包含两个整数 $n,m，$分别表示序列的长度和操作次数。

接下来 $m$ 行描述对序列的操作，其中第 $i$ 行包含两个整数 $p_i,q_i$ 表示操作类型和参数。当 $p_i=0$ 时，表示将 $a_1,a_2,⋅⋅⋅,a_qi$ 降序排列；当 $p_i=1$ 时，表示将 $a_qi,a_{qi+1},⋅⋅⋅,a_n$ 升序排列。

**输出格式**

输出一行，包含 $n$ 个整数，相邻的整数之间使用一个空格分隔，表示操作完成后的序列。

**数据范围**

对于 $30\%$ 的评测用例，$n,m≤1000；$
对于 $60\%$ 的评测用例，$n,m≤5000；$
对于所有评测用例，$1≤n,m≤105，0≤pi≤1，1≤qi≤n。$

**输入样例1：**

```
3 3
0 3
1 2
0 2
```

**输出样例1：**

```
3 1 2
```

**样例解释**

原数列为 (1,2,3)。

第 1步后为 (3,2,1。

第 2步后为 (3,1,2)。

第 3步后为 (3,1,2)。与第 2 步操作后相同，因为前两个数已经是降序了。



**题解**

可看这篇[题解](https://www.acwing.com/solution/content/48049/)

**代码**

```c++
#include <iostream>
#include <cstdio>
using namespace std;

#define x first
#define y second

typedef pair<int,int> PII;

const int N = 100010;
PII stk[N];
int ans[N];
int top;
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    while(m --) {
        int p, q;
        scanf("%d%d", &p, &q);
        if(!p) {
            while(top && stk[top].x == 0) q = max(q, stk[top --].y);
            while(top >= 2 && stk[top - 1].y <= q) top -= 2;
            stk[++ top] = {0, q};
        }else if(top) {
            while(top && stk[top].x == 1) q = min(q, stk[top --].y);
            while(top >= 2 && stk[top - 1].y >= q) top -= 2;
            stk[++ top] = {1, q};
        }
    }
    int k = n, l = 1, r = n;
    for(int i = 1;i <= top;i ++) {
        if(stk[i].x == 0)
            while(r > stk[i].y && l <= r) ans[r --] = k --;
        else
            while(l < stk[i].y && l <= r) ans[l ++] = k --;
        if(l > r)
            break;
    }
    if(top % 2)
        while(l <= r) ans[l ++] = k --;
    else
        while(l <= r) ans[r --] = k --;
        
    for(int i = 1;i <= n;i ++)
        printf("%d ", ans[i]);
    return 0;
}
```



