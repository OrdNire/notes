# KMP

kmp是字符串匹配算法

按照朴素的做法，如果两个字符串未匹配成功，那么模板字符串需要移位回去到主字符串的当前匹配起始位置的下一个位置。

**kmp算法就是一种不需要回溯移位的字符串匹配算法**



**kmp数组中next[]的含义**

![Kmp中next含义](D:\个人资料\Notes\算法\images\Kmp中next含义.png)



**kmp的匹配过程**

```c
// 匹配过程
for(int i = 1,j = 0;i <= m;i ++){

    while(j && s[i] != p[j + 1]) j = ne[j];
    if(s[i] == p[j + 1]) j ++;
    if(j == n){
		// 匹配成功
    }
}
```

**next数组的处理过程**

和匹配过程类似，不过就是模板匹配模板

```c
// 求next数组(与匹配过程类似)
for(int i = 2,j = 0;i <= n;i ++){
    while(j && p[i] != p[j + 1]) j = ne[j];
    if(p[i] == p[j + 1]) j ++;
    ne[i] = j;
}
```

