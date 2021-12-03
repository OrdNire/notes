# Offer 56-1.数组中数字出现的次数

```
一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。

 

示例 1：

输入：nums = [4,1,4,6]
输出：[1,6] 或 [6,1]

示例 2：

输入：nums = [1,2,10,4,1,4,3,3]
输出：[2,10] 或 [10,2]

 

限制：

    2 <= nums.length <= 10000
```

### 解法

##### 哈希表

历遍数组，若哈希表中没有该元素则存入，若有则删除该元素，用时特别慢

##### 位运算

全员进行异或操作即可。考虑异或操作的性质：对于两个操作数的每一位，相同结果为 0，不同结果为 1。那么在计算过程中，成对出现的数字的所有位会两两抵消为 0，最终得到的结果就是那个出现了一次的数字。

那么这一方法如何扩展到找出**两个**出现一次的数字呢？

如果我们可以把所有数字分成两组，使得：

1. 两个只出现一次的数字在不同的组中
2. 相同的数字会被分到相同的组中

那么对两个组分别进行异或操作，即可得到答案的两个数字。**这是解决这个问题的关键。**

那么如何实现这样的分组呢？

![image-20200716200257459](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200716200257459.png)

### 代码

##### 哈希表

```java
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

class Solution {
    public int[] singleNumbers(int[] nums) {
    	Map<Integer,Integer> map = new HashMap<>();
    	for(int i=0;i<nums.length;i++) {
    		if(map.containsKey(nums[i])) {
    			map.remove(nums[i]);
    		}else {
    			map.put(nums[i], nums[i]);
    		}
    	}
    	int size = map.size();
    	int[] arr = new int[size];
    	Set<Entry<Integer, Integer>> entrySet = map.entrySet();
    	int i=0;
    	for(Entry<Integer, Integer> e:entrySet) {
    		arr[i++] = e.getKey();
    	}	
    	return arr;
    }
}
```

##### 位运算（利用异或）

```c++
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int ret = 0;
        for(int n:nums){
            ret ^= n;
        }
        int res = 1;
        while((res & ret)==0){
            res <<= 1;
        }
        int a=0,b=0;
        for(int n:nums){
            if(res & n){
                a ^= n;
            }else{
                b ^= n;
            }
        }
        return vector<int>{a,b};
    }
};
```

