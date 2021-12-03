# Offer 56-2.数组中数字出现的次数2

```
在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。

 

示例 1：

输入：nums = [3,4,3,3]
输出：4

示例 2：

输入：nums = [9,1,7,9,7,9,7]
输出：1

 

限制：

    1 <= nums.length <= 10000
    1 <= nums[i] < 2^31
```

### 思路

##### 逐位统计1的个数

诸位统计数组中每一个数每一位1的个数，然后数组中重复多少个数，则将最终统计的每一位余上多少，剩下的则为最终结果

![Picture1.png](https://pic.leetcode-cn.com/28f2379be5beccb877c8f1586d8673a256594e0fc45422b03773b8d4c8418825-Picture1.png)

![image-20200716213148004](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200716213148004.png)

![image-20200716213156852](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200716213156852.png)

### 代码

```java
class Solution {
    public int singleNumber(int[] nums) {
        int[] count = new int[32];
        for(int i=0;i<nums.length;i++){
            for(int j=0;j<32;j++){
                count[j] += nums[i] & 1;
                nums[i] >>>= 1;
            }
        }
        int res = 0,m = 3;
        for(int i=0;i<32;i++){
            res <<= 1;
            res |= count[31-i] % m;
        }
        return res;
    }
}
```

