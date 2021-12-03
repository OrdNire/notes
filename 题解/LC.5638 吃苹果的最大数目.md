# LC.5638 吃苹果的最大数目

链接：https://leetcode-cn.com/problems/maximum-number-of-eaten-apples/



**题解**

该题是一个经典的贪心问题，我们每天只需要吃掉当前所有苹果中，过期时间最短的苹果即可

**所以我们可以考虑使用堆来维护一个过期时间最短的苹果的小根堆**



**代码**

```c
class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        typedef pair<int,int> PII;
        priority_queue<PII, vector<PII>, greater<PII>> heap;
        int n = apples.size();
        int res = 0;
        for(int i = 0; i < 40000;i ++){
            if(i < n && apples[i] > 0)
                heap.push({i + days[i] - 1,apples[i]});
            while(heap.size() && heap.top().first < i) heap.pop();
            if(heap.empty()) continue;
            auto t = heap.top();
            heap.pop();
            res ++;
            if(-- t.second) heap.push(t);
        }

        return res;
    }
};
```

