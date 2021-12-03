# Offer 03.数组中重复的数字

```
在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

示例 1：

输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 
```

## 思路

哈希表，判断是否存在key-value，不存在就把该数存入，存在返回该数。

## 代码

```java
public int findRepeatNumber(int[] nums) {
    Map<Integer,Integer> map = new HashMap<>();
    for(int i=0;i<nums.length;i++) {
        if(map.containsKey(nums[i])) {
            return nums[i];
        }else {
            map.put(nums[i], i);
        }
    }
    return -1;
}
```

