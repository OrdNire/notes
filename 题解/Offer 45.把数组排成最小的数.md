# Offer 45.把数组排成最小的数

```
输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

 

示例 1:

输入: [10,2]
输出: "102"

示例 2:

输入: [3,30,34,5,9]
输出: "3033459"

 

提示:

    0 < nums.length <= 100

说明:

    输出结果可能非常大，所以你需要返回一个字符串而不是整数
    拼接起来的数字可能会有前导 0，最后结果不需要去掉前导 0
```

### 题解

##### 自定义排序

本质上是排序，但此排序是将两个数不同顺序的组合成字符串

### 代码

##### 自定义排序

```java
class Solution {
   public String minNumber(int[] nums) {
    	int size = nums.length;
        for(int i=0;i<size-1;i++) {
        	int index = i;
        	for(int j=i+1;j<size;j++) {
        		if(compare(nums[index],nums[j]) > 0) {
        			index = j;
        		}
        	}
        	int temp = nums[index];
        	nums[index] = nums[i];
        	nums[i] = temp;
        }
        StringBuilder sb = new StringBuilder();
        for(int n:nums) {
        	sb.append(n);
        }
        return sb.toString();
    }
    
    private int compare(int a,int b) {
    	String aStr = Integer.toString(a) + Integer.toString(b);
    	String bStr = Integer.toString(b) + Integer.toString(a);
    	return aStr.compareTo(bStr);
    }
}
```

