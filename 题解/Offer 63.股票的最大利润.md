# Offer 63.股票的最大利润

```
假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？

 

示例 1:

输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。

示例 2:

输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。

 

限制：

0 <= 数组长度 <= 10^5
```

### 题解

##### 历遍寻找差最小

因为只能出现最大值在最小值后面，所以以一个变量记录最小值，再从其后找到所有比它大的值

时间复杂度O(n)

##### 动态规划

![image-20200728145137733](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200728145137733.png)



![image-20200728145155290](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200728145155290.png)

### 代码

##### 历遍寻找差最小

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxInt = 0;
        int minInt = 99999999;
        int index = -1;
        for(int i=0;i<prices.size();i++){
            if(prices[i] < minInt){
                minInt = prices[i];
            }
            if(prices[i] - minInt > maxInt){
                maxInt = prices[i] - minInt;
            }
        }
        return maxInt;
    }
};
```

##### 动态规划

```java
class Solution {
    public int maxProfit(int[] prices) {
        int cost = Integer.MAX_VALUE,profit = 0;
        for(int price : prices){
            cost = Math.min(cost,price);
            profit = Math.max(profit,price-cost);
        }
        return profit;
    }
}
```

