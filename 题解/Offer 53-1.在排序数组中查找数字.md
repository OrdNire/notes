# Offer 53-1.在排序数组中查找数字

```
统计一个数字在排序数组中出现的次数。

 

示例 1:

输入: nums = [5,7,7,8,8,10], target = 8
输出: 2

示例 2:

输入: nums = [5,7,7,8,8,10], target = 6
输出: 0

 

限制：

0 <= 数组长度 <= 50000
```

### 解法

##### 暴力

​	直接遍历数组统计出现个数

##### 二分

​	用二分法找到target的右边界和target-1的右边界，相减

### 代码

##### 暴力

```java
class Solution {
    public int search(int[] nums, int target) {
        int count=0;
        for(int n:nums){
            if(n == target){
                count++;
            }
        }
        return count;
    }
}
```

##### 二分

```java
class Solution {
    public int search(int[] nums, int target) {
        return find(nums,target)-find(nums,target-1);
    }

    int find(int[] nums,int target){
        int f=0,l=nums.length-1;
        int mid;
        while(f<=l){
            mid = (f+l)/2;
            if(nums[mid]<=target){
                f = mid + 1;
            }else{
                l = mid - 1;
            }
        }
        return f;
    }
}
```

