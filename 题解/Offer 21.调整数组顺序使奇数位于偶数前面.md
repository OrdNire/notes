# Offer 21.调整数组顺序使奇数位于偶数前面

```
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。

 

示例：

输入：nums = [1,2,3,4]
输出：[1,3,2,4] 
注：[3,1,2,4] 也是正确的答案之一。

 

提示：

    1 <= nums.length <= 50000
    1 <= nums[i] <= 10000
```

### 解法

##### 	快慢双指针

​	一个指针记录下一个奇数置换到的位置，一个指针一直往右走，看到奇数就置换

##### 	双指针

​	首位双指针，左指针往右直到偶数，右指针往左直到奇数。再置换

### 代码

##### 	快慢双指针

```java
class Solution {
    public int[] exchange(int[] nums) {
        int index = 0;
        int temp;
        for(int i=0;i<nums.length;i++){
            if(nums[i]%2!=0){
                temp = nums[i];
                nums[i] = nums[index];
                nums[index] = temp;
                index++;
            }
        }
        return nums;
    }
}
```

##### 	双指针

```java
class Solution {
    public int[] exchange(int[] nums) {
        int f=0,l=nums.length-1;
        int temp;
        while(f<l){
            if(nums[f]%2!=0){
                f++;
                continue;
            }
            if(nums[l]%2==0){
                l--;
                continue;
            }
            temp = nums[f];
            nums[f] = nums[l];
            nums[l] = temp;
        }
        return nums;
    }
}
```

