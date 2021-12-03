# Offer 48.最长不含重复字段的子字符串

```
请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

 

示例 1:

输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

示例 2:

输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:

输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

 

提示：

    s.length <= 40000
```

### 题解

##### 动态规划

![image-20200730150215858](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200730150215858.png)

![Picture1.png](https://pic.leetcode-cn.com/c576757494724070d0c40cd192352ef9f48c42e14af09a1333972b9d843624a3-Picture1.png)

![image-20200730150233535](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200730150233535.png)

##### 动态规划+哈希表

![image-20200730150300549](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200730150300549.png)

### 代码

##### 动态规划+哈希表

```java
class Solution {
    public int lengthOfLongestSubstring(String s) {
        Map<Character,Integer> dic  = new HashMap<>();
        int temp = 0,res = 0;
        for(int i=0;i<s.length();i++){
            int index = dic.getOrDefault(s.charAt(i),-1);
            dic.put(s.charAt(i),i);
            temp = temp < i-index ? temp + 1 : i-index;
            res = Math.max(res,temp);
        }
        return res;
    }
}
```

