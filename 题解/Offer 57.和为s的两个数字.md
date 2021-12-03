# Offer 57.和为s的两个数字

```
输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。如果有多对数字的和等于s，则输出任意一对即可。

 

示例 1：

输入：nums = [2,7,11,15], target = 9
输出：[2,7] 或者 [7,2]

示例 2：

输入：nums = [10,26,30,31,47,60], target = 40
输出：[10,30] 或者 [30,10]

 

限制：

    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6
```

### 思路

##### 双指针对撞法

双指针分别指向头和尾，

若当前两个指针所指的值的和大于目标值，由于原数组是递增数组，则需要右右指针往左移动，减小和的值大小。

若当前两个指针所指的值的和小于目标值，则需要左指针往右移动，增大 和的值的大小。

相等则返回

### 代码

```java
class Solution {
    public int[] twoSum(int[] nums, int target) {
        int left = 0,right = nums.length-1;
        while(left<right){
            if(nums[left] + nums[right] > target){
                right --;
            }else if(nums[left] + nums[right] < target){
                left ++;
            }else{
                return new int[]{nums[left],nums[right]};
            }
        }
        return null;
    }
}
```

