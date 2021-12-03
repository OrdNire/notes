# Offer 59-1.滑动窗口的最大值

```
给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。

示例:

输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7] 
解释: 

  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

 

提示：

你可以假设 k 总是有效的，在输入数组不为空的情况下，1 ≤ k ≤ 输入数组的大小。
```

### 解法

##### 历遍求每一个窗口的最大值

对每一个窗口遍历求除最大值，速度慢，时间复杂度O((n−k+1)k) 约等于O(nk)

##### 双端队列

根据含有min的栈，可以用一个单调队列来记录每一次的最大值，

![image-20200721140854225](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200721140854225.png)

时间复杂度O(n)

空间复杂度O(k)

### 代码

##### 历遍求每一个窗口的最大值

```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int size = nums.size();
        vector<int> res;
        if(size <= 0) return res;
        int max = getMax(nums,0,k-1);
        res.push_back(max);
        for(int i=k;i<size;i++){
            max = getMax(nums,i-k+1,i);
            res.push_back(max);
        }
        return res;
    }

    int getMax(vector<int>& nums,int l,int r){
        int max = 1<<31;
        for(int i=l;i<=r;i++){
            if(nums[i] > max) max = nums[i];
        }
        return max;
    }
};
```

##### 双端队列

```java
class Solution {
    public int[] maxSlidingWindow(int[] nums, int k) {
        if(nums.length <=0 || k == 0) return new int[0];
        Deque<Integer> deque = new LinkedList<>();
        int[] res = new int[nums.length - k + 1];
        for(int i=1-k,j=0;j<nums.length;i++,j++){
            if(i > 0 && deque.peekFirst() == nums[i-1]) deque.removeFirst();
            while(!deque.isEmpty() && deque.peekLast() < nums[j]) deque.removeLast();
            deque.addLast(nums[j]);
            if(i >= 0) res[i] = deque.peekFirst();
        }
        return res;
    }
}
```

