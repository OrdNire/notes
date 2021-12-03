# Offer 20.表示数值的字符串

```c++
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100"、"5e2"、"-123"、"3.1416"、"0123"都表示数值，但"12e"、"1a3.14"、"1.2.3"、"+-5"、"-1E-16"及"12e+5.4"都不是。
```

### 题解

##### 分情况讨论

### 代码

##### 分情况讨论

```c++
class Solution {
public:
    bool isNumber(string s) {
        if(s.size() == 0) return false;
        trim(s);
        bool isNum = false,ise_orE = false,isDot = false,isFlag = false;
        for(int i=0;i<s.size();i++){
            if(s[i] >= '0' && s[i] <= '9') isNum = true;
            else if(s[i] == '.'){
                if(isDot || ise_orE){
                    return false;
                }else{
                    isDot = true;
                }
            }else if(s[i] == 'e' || s[i] == 'E'){
                if(!isNum || ise_orE){
                    return false;
                }else{
                    ise_orE = true;
                    isNum = false;
                }
            }else if(s[i] == '-' || s[i] == '+'){
                if(i != 0 && s[i-1] != 'e' && s[i-1] != 'E'){
                    return false;
                }
            }else return false;
        }
        return isNum;
    }

    void trim(string &s){
        if(!s.empty()){
            s.erase(0,s.find_first_not_of(" "));
            s.erase(s.find_last_not_of(" ")+1);
        }
    }
};
```

