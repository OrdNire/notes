# Offer 58-1.翻转单词顺序

```
输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "，则输出"student. a am I"。

 

示例 1：

输入: "the sky is blue"
输出: "blue is sky the"

示例 2：

输入: "  hello world!  "
输出: "world! hello"
解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。

示例 3：

输入: "a good   example"
输出: "example good a"
解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

 

说明：

    无空格字符构成一个单词。
    输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
    如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
```

### 题解

##### 利用java的trim()以及split()函数

split()函数根据传入的参数进行字符串拆分

trim()函数对字符串消除首尾空格

可以对字符串按空格拆分，如果中间有多余空格，则是“”空字符串

再除了空字符串外倒叙存入StringBuilder中，最后返回消除首尾空格的结果

![image-20200720144517353](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200720144517353.png)

### 代码

##### 利用java的trim()以及split()函数

```java
class Solution {
    public String reverseWords(String s) {
        String[] strs = s.trim().split(" ");
        StringBuilder res = new StringBuilder();
        for(int i=strs.length-1;i>=0;i--){
            if(!"".equals(strs[i])){
                res.append(strs[i]+" ");
            }
        }
        return res.toString().trim();
    }
}
```

