# Offer 38.字符串的排序

```
输入一个字符串，打印出该字符串中字符的所有排列。

 

你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

 

示例:

输入：s = "abc"
输出：["abc","acb","bac","bca","cab","cba"]

 

限制：

1 <= s 的长度 <= 8

```

### 题解

##### DFS+剪枝

![image-20200731151427565](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200731151427565.png)

![Picture1.png](https://pic.leetcode-cn.com/dc4659dbda6d54f50a8c897647fb7c52e2b8200e741c4d6e25306dfe51f93bb6-Picture1.png)



![image-20200731151513172](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200731151513172.png)



![Picture2.png](https://pic.leetcode-cn.com/edbbe4db611791ca63e582e8b0c754261e8d7464edace38420ce3087eb96d9a5-Picture2.png)



![image-20200731151550087](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200731151550087.png)



### 代码

##### DFS+剪枝

```java
class Solution {
    private List<String> a = new ArrayList<>();
    private int len;
    private char[] c;
    public String[] permutation(String s) {
    	c = s.toCharArray();
    	len = s.length();
    	dfs(0);
    	return a.toArray(new String[len]);
    }

    private void dfs(int step){
        if(step == len-1) {
        	a.add(String.valueOf(c));
        }
        HashSet<Character> set = new HashSet<>();
        for(int i=step;i<len;i++) {
            if(set.contains(c[i])) continue;
            set.add(c[i]);
            swap(i,step);
            dfs(step+1);
            swap(i,step);
        }
    }
    
    private void swap(int a, int b) {
        char tmp = c[a];
        c[a] = c[b];
        c[b] = tmp;
    }
}
```

