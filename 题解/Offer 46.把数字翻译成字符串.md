# Offer 46.把数字翻译成字符串

```
给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

 

示例 1:

输入: 12258
输出: 5
解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"

 

提示：

    0 <= num < 231
```

### 题解

##### 动态规划

根据题目，翻译有两种情况，一个数字可以翻译一种，两个数字在范围你也能翻译一种

从左到右看数字，当我们看到最后一个数字的时候。

整个数字的翻译结果数 = 除去最后一位的部分的翻译结果 * 1;

当我们看到两位数字的时候：

整个数字的翻译结果数 = 除去最后两位的部分的翻译结果  * 1;

所以易得状态转移方程

dp[i] = dp[i-1] + dp[i-2] (数字在10到25之间)

### 代码

##### 动态规划

```java
class Solution {
    public int translateNum(int num) {
    	String s = String.valueOf(num);
    	char[] arr = s.toCharArray();
    	int size = arr.length;
    	
    	if(size < 2) return size;
    	
    	int[] dp = new int[size];
    	dp[0] = 1;
    	for(int i=1;i<size;i++) {
    		dp[i] += dp[i-1];
    		int currentNum = 10*(arr[i-1]-'0') + (arr[i]-'0');
    		if(currentNum >= 10 && currentNum <= 25) {
    			if(i < 2) {
    				dp[i] ++;
    			}else {
    				dp[i] += dp[i-2];
    			}
    		}
    	}
    	return dp[size-1];
    }

}
```

