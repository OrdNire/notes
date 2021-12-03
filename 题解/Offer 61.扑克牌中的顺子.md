# Offer 61.扑克牌中的顺子

```
从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以看成任意数字。A 不能视为 14。

 

示例 1:

输入: [1,2,3,4,5]
输出: True

 

示例 2:

输入: [0,0,1,2,5]
输出: True

 

限制：

数组长度为 5 

数组的数取值为 [0, 13] .
```

### 题解

##### ![Picture1.png](https://pic.leetcode-cn.com/df03847e2d04a3fcb5649541d4b6733fb2cb0d9293c3433823e04935826c33ef-Picture1.png)

##### 利用set

![image-20200721151435364](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200721151435364.png)

##### 排序

将数组排序，如果nums[i] = nums[i+1]则有重复

最大值为数组nums[4],最小值为nums[joker],其中joker为0的数量

时间复杂度O(NlogN)

空间复杂度O(1)

### 代码

##### set

```java
class Solution {
    public boolean isStraight(int[] nums) {
        Set<Integer> set = new HashSet<>();
        int max = 0,min = 14;
        for(int n:nums){
            if(n == 0) continue;
            max = Math.max(max,n);
            min = Math.min(min,n);
            if(set.contains(n)){
                return false;
            }
            set.add(n);
        }
        return max - min < 5;
    }
}
```

##### 排序

```java
class Solution {
    public boolean isStraight(int[] nums) {
        int joker = 0;
        Arrays.sort(nums); // 数组排序
        for(int i = 0; i < 4; i++) {
            if(nums[i] == 0) joker++; // 统计大小王数量
            else if(nums[i] == nums[i + 1]) return false; // 若有重复，提前返回 false
        }
        return nums[4] - nums[joker] < 5; // 最大牌 - 最小牌 < 5 则可构成顺子
    }
}
```

