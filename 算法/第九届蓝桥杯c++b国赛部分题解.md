## 调手表

原题链接：[调手表](https://www.lanqiao.cn/problems/230/learning/)

### 题目描述

小明买了块高端大气上档次的电子手表，他正准备调时间呢。

在 M78 星云，时间的计量单位和地球上不同，M78 星云的一个小时有 $n$ 分钟。

大家都知道，手表只有一个按钮可以把当前的数加一。在调分钟的时候，如果当前显示的数是 0 ，那么按一下按钮就会变成 1，再按一次变成 2 。如果当前的数是 $n - 1$，按一次后会变成 0。

作为强迫症患者，小明一定要把手表的时间调对。如果手表上的时间比当前时间多 1，则要按 $n - 1$ 次加一按钮才能调回正确时间。

小明想，如果手表可以再添加一个按钮，表示把当前的数加 $k$ 该多好啊......

他想知道，如果有了这个 $+k$ 按钮，按照最优策略按键，从任意一个分钟数调到另外任意一个分钟数最多要按多少次。

注意，按 $+k$ 按钮时，如果加 k 后数字超过 $n-1$,则会对 $n$ 取模。

比如，$n=10, k=6$ 的时候，假设当前时间是 0，连按 2 次 $+k$ 按钮，则调为 2。

##### 输入格式

一行两个整数 $n, k (0 < k < n <= 10^5)$，意义如题。

##### 输出格式

输出一行一个整数，表示按照最优策略按键，从一个时间调到另一个时间最多要按多少次。

#### 数据范围

$n, k (0 < k < n <= 10^5)$

#### 样例解释

如果时间正确则按 0 次。否则要按的次数和操作系列之间的关系如下：

1：+1

2：+1, +1

3：+3

4：+3, +1

##### 输入样例1：

```
5 3
```

##### 输出样例1：

```
2
```

### 思路

本题的意思就是通过两种走法 $+1$  和 $+k$ ，求 0 到 n - 1 的最短路径，并求到所有点的最短路径的最大值

因为只有两种走法，可以用 dfs 来做，但这样每走一步，就有两种选择，那么时间复杂度必然是指数级别的。

假设 k = 3，那么从 0 到 3 可以走一步 $+k$ 或者走三步 $+1$，那么其实就转化为了图，而 $+1$ 和 $+k$ 就是边，那么求通过最少步数到所有点，就是求到所有点的最短路径

那么可以利用 spfa 来求最短路径

但本题边的权值为 1，所以可以用 bfs 来求到所有点的最短路径

#### 时间复杂度

$O(n)$

#### C++ 代码
```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 100010;
int dist[N];
int n, k;
int res;

void bfs() {
	memset(dist, -1, sizeof dist);
	queue<int> q;
	q.push(0);
	dist[0] = 0;
	
	while(q.size()) {
		auto t = q.front();
		q.pop();
		
		res = max(res, dist[t]);
		
		if(dist[(t + 1) % n] == -1) {
			dist[(t + 1) % n] = dist[t] + 1;
			q.push((t + 1) % n);
		}
		if(dist[(t + k) % n] == -1) {
			dist[(t + k) % n] = dist[t] + 1;
			q.push((t + k) % n);
		}
	}
	
}

int main()
{
	cin >> n >> k;
	bfs();
	cout << res << endl;
	return 0;
} 
```



## 搭积木

原题链接：[搭积木](https://www.lanqiao.cn/problems/225/learning/)

### 题目描述

小明对搭积木非常感兴趣。他的积木都是同样大小的正立方体。

在搭积木时，小明选取 $m$ 块积木作为地基，将他们在桌子上一字排开，中间不留空隙，并称其为第 0 层。

随后，小明可以在上面摆放第 1 层，第 2 层，......，最多摆放至第 $n$ 层。摆放积木必须遵循三条规则：

规则 1：每块积木必须紧挨着放置在某一块积木的正上方，与其下一层的积木对齐；

规则 2：同一层中的积木必须连续摆放，中间不能留有空隙；

规则 3：小明不喜欢的位置不能放置积木。

其中，小明不喜欢的位置都被标在了图纸上。图纸共有 $n$ 行，从下至上的每一行分别对应积木的第 1 层至第 $n$ 层。每一行都有 $m$ 个字符，字符可能是 '.' 或 'X' ，其中 'X' 表示这个位置是小明不喜欢的。

现在，小明想要知道，共有多少种放置积木的方案。他找到了参加蓝桥杯的你来帮他计算这个答案。

由于这个答案可能很大，你只需要回答这个答案对 $10^9 + 7$ 取模后的结果。

注意：地基上什么都不放，也算作是方案之一种。

##### 输入格式

输入格式：

输入数据的第一行有两个正整数 $n,m$ ，表示图纸的大小。

随后 $n$ 行，每行有 $m$ 个字符，用来描述图纸。每个字符只可能是 '.' 或 'X' 。

##### 输出格式

输出一个整数，表示答案对 $10^9 + 7$ 取模后的结果。

#### 数据范围

$n≤100，m≤100$

##### 输入样例1：

```
2 3
..X
.X.
```

##### 输出样例1：

```
4
```



### 思路

本题有一个关键一点，就是每一层能摆放必须是连续的摆放，中间不能断

#### 暴搜

因为每一层是连续摆放，且下一层都是基于上一层连续摆放的位置，再枚举连续摆放的位置，所以可以直接 dfs 

但这种方式时间复杂度太大，每一层需要两层循环枚举连续摆放区间，那么是 $O(m^2)$，加上有 m 层，那么总时间复杂度就是 $O((m^2)^n)$，必定超时

#### 时间复杂度

$O((m^2)^n)$

#### 代码

```c++
#include <iostream>
#include <cstdio>
using namespace std;

const int N = 110, mod = 1e9 + 7;
char w[N][N];
int ck[N][N];	// 每一层含有 X 的前缀和 
int n, m;
int ans = 1;	// 不放也为一种 

void dfs(int h,int l,int r) {
	if(h <= 0) return;
	for(int i = l;i <= r;i ++)
		for(int j = i;j <= r;j ++)
			if(ck[h][j] - ck[h][i - 1] == 0) {
				ans = (ans + 1) % mod;
				dfs(h - 1, i, j);
			}
	
	
} 

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i ++) scanf("%s", w[i] + 1);
	
	// 预处理每一层区间内是否合法，利用前缀和
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= m;j ++)
			if(w[i][j] == 'X')
				ck[i][j] = ck[i][j - 1] + 1;
			else
				ck[i][j] = ck[i][j - 1];
	
	for(int l = 1;l <= m;l ++)
		for(int r = l;r <= m;r ++)
			if(ck[n][r] - ck[n][l - 1] == 0) {	// 判断是否满足可连续摆放，即区间内 x 为 0 
				ans ++;
				dfs(n - 1, l, r);
			}
	
	printf("%d\n", ans);
	return 0;
}
```

#### 记忆化搜索

可以看出来，dfs搜索过程中会有很多区间重复，那么可以利用记忆化，开一个二维数组，记录每一层每个区间的方案数，剪枝来降低搜索次数

其实，记忆化搜索就是动态规划的递归版本

#### 代码

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;

const int N = 110, mod = 1e9 + 7;
char w[N][N];
int mem[N][N][N];
int ck[N][N];	// 每一层含有 X 的前缀和 
int n, m;
int ans = 1;	// 不放也为一种 

bool check(int h,int l,int r) {
	return ck[h][r] - ck[h][l - 1];
}

int dfs(int h,int l,int r) {
	if(h <= 0 || check(h, l, r)) return 0;
	
	int res = 1;
	
	for(int i = l;i <= r;i ++)
		for(int j = i;j <= r;j ++)
			if(mem[h - 1][i][j] != -1) {
				res = (res + mem[h - 1][i][j]) % mod;
			}else {
				res = (res + dfs(h - 1, i, j)) % mod;
			}
			
	mem[h][l][r] = res;
	return res;
} 

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i ++) scanf("%s", w[i] + 1);
	
	// 预处理每一层区间内是否合法，利用前缀和
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= m;j ++)
			if(w[i][j] == 'X')
				ck[i][j] = ck[i][j - 1] + 1;
			else
				ck[i][j] = ck[i][j - 1];
	
	memset(mem, -1, sizeof mem);
		
	for(int l = 1;l <= m;l ++)
		for(int r = l;r <= m;r ++)
			ans = (ans + dfs(n, l, r)) % mod;
	
	printf("%d\n", ans);
	return 0;
}
```



/usr/lib/openssh/sftp-server
