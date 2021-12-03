# Offer 42.连续子数组的最大和

```
输入一个整型数组，数组里有正数也有负数。数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。

要求时间复杂度为O(n)。

 

示例1:

输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

 

提示：

    1 <= arr.length <= 10^5
    -100 <= arr[i] <= 100
```

### 思路

##### 动态规划问题

设动态规划列表dp,dp[i]代表以元素nums[i]为结尾的连续子数组最大和

分析题目，将问题分解至连续两个数相加。

若dp[i-1]<=0，dp[i-1]对dp[i]产生负影响，即nums[i]>dp[i-1]+nums[i]

1. if dp[i-1]>0 dp[i] = dp[i-1]+nums[i];
2. if dp[i-1]<=0 dp[i] = nums[i];

最后返回dp列表中的最大值，即为结果

![Picture1.png](https://pic.leetcode-cn.com/8fec91e89a69d8695be2974de14b74905fcd60393921492bbe0338b0a628fd9a-Picture1.png)

**空间优化**

dp[i]至于dp[i-1]相关，即可直接在原数组上存储每一步的值，减少空间。

### 代码

```java
class Solution {
    public int maxSubArray(int[] nums) {
        int res = nums[0];
        for(int i = 1; i < nums.length; i++) {
            nums[i] += Math.max(nums[i - 1], 0);
            res = Math.max(res, nums[i]);
        }
        return res;
    }
}
```

