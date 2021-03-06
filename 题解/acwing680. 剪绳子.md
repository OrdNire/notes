# acwing680. 剪绳子

有N根绳子，第i根绳子长度为*Li*，现在需要M根等长的绳子，你可以对N根绳子进行任意裁剪（不能拼接），请你帮忙计算出这M根绳子最长的长度是多少。

#### 输入格式

第一行包含2个正整数N、M，表示原始绳子的数量和需求绳子的数量。

第二行包含N个整数，其中第 i 个整数*Li*

表示第 i 根绳子的长度。

#### 输出格式

输出一个数字，表示裁剪后最长的长度，保留两位小数。

#### 数据范围

1≤*N*,*M*≤100000,
0<*Li*<109

#### 输入样例：

```
3 4
3 5 4
```

#### 输出样例：

```
2.50
```

#### 样例解释

第一根和第三根分别裁剪出一根2.50长度的绳子，第二根剪成2根2.50长度的绳子，刚好4根。



**题解**

该题本质上是一道**浮点数二分**的问题



对于能求剪成多少根绳子，如果我们已经知道了需要剪成的绳子的长度，那么判断能不能剪成指定根数的绳子很容易，我们只需要遍历所有的绳子，然后绳子长度除以需要剪成的绳子长度，向下取整即可。

然而本道题是一道最优化问题，我们其实可以用浮点数二分将其转换为判定满足的问题

那么对于二分，check函数就是

- **如果当前mid值能剪成指定根数，那么 l = mid，因为如果能剪成，那么表示还可以试图往更长的长度来探测**
- **如果当前mid值不能剪成指定根数，那么r = mid**



**代码**

```c
#include <iostream>
using namespace std;

const int N = 100010;
int w[N];
int n,m;

bool check(double x){
    int cnt = 0;
    for(int i = 0;i < n;i ++)
        cnt += w[i] / x;
    return cnt >= m;
}

int main()
{
    cin >> n >> m;
    
    for(int i = 0;i < n;i ++) cin >> w[i];
    
    double l = 0, r = 1e9;
    while(r - l > 1e-4){
        double mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }
    
    printf("%.2lf",r);
    return 0;
}
```

