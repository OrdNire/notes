# Offer 57-2.和为s的连续正数序列

```
输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。

序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

 

示例 1：

输入：target = 9
输出：[[2,3,4],[4,5]]

示例 2：

输入：target = 15
输出：[[1,2,3,4,5],[4,5,6],[7,8]]

 

限制：

    1 <= target <= 10^5
```

### 解法

##### 枚举

利用队列，将每个递增数存入队列中，若队列中数的和大于目标值，队列头出队，若小于目标值则对立尾继续进入递增的数，若该队列数的和等于目标队列，则将其添加进list<int[]>中存放

缺点：时间复杂度高

##### 双指针

![image-20200720141050570](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200720141050570.png)

此方法时间复杂度O(target),空间复杂度O(1)

### 代码

##### 枚举

```java
class Solution {
    public int[][] findContinuousSequence(int target) {
    	LinkedList<Integer> que = new LinkedList<>();
    	List<int[]> arr = new ArrayList<>();
    	int sum = 0;
    	int i = 1;
    	while(sum < target) {
    		sum += i;
    		que.addLast(i++);
    	}
    	if(sum == target) {
    		arr.add(getArr(que));
    		sum += i;
    		que.addLast(i++);
    	}
    	while(que.getFirst() < target) {
    		if(sum > target) {
    			sum -= que.removeFirst();
    		}else if(sum < target) {
    			sum += i;
    			que.addLast(i++);
    		}else {
    			arr.add(getArr(que));
    			sum += i;
    			que.addLast(i++);
    		}
    	}
    	int size = arr.size();
    	int[][] res = new int[size][];
    	for(int j=0;j<size;j++) {
    		res[j] = arr.get(j);
    	}
    	return res;
    }
    
    private int[] getArr(LinkedList<Integer> que) {
    	int size = que.size();
    	int[] arr = new int[size];
    	for(int i=0;i<size;i++) {
    		arr[i] = que.get(i);
    	}
    	return arr;
    }
}
```

##### 双指针

```c++
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> vec;
        vector<int> res;
        int sum = 0;
        for(int l=1,r=2;l<r;){
            sum = (l+r)*(r-l+1)/2;
            if(sum == target){
                res.clear();
                for(int i=l;i<=r;i++){
                    res.push_back(i);
                }
                vec.push_back(res);
                l++;
            }else if(sum > target){
                l++;
            }else{
                r++;
            }
        }
        return vec;
    }
};
```

