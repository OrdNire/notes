# 对象

```javascript
var obj = new Object();
```

##### JavaScript中可以使用特殊的属性名

```javascript
//例如123等属性名
obj["123"] = 789;
//取得时候也需要"[]"
console.log(obj["123"]);
//"[]"中可以传递变量

var n = "123";
//一样
console.log(obj[n]);
console.log(obj["123"]);
```



JS对象属性值可以是任何类型



##### **in运算符**

通过该运算符可以检测对象中是否有该对象值

```javascript
console.log("text" in obj); //false
console.log("123" in obj);	//true
```



##### **使用对象字面量创建对象**

```js
//使用{}和new 本质一样
var obj = {};

//使用对象字面量在创建时可以直接指定属性名
//最后一个属性不能加逗号
var obj2 = {
    name:"猪八戒",
	"age":18
};
```



##### **创建一个函数对象**

```javascript
var fun = new Function();

console.log(typeof fun);//返回Function;

var fun = new Function("console.log('这是我第一个js函数')");

//调用函数，函数中封装的代码会执行

fun();//这是我第一个js函数

//一般使用函数声明来创建函数

function fun2(){
    console.log("这是我第二个函数");
}

fun2();//这是我第二个函数

//使用函数表达式声明，函数既对象，类似于将函数地址赋值给函数名
//var 函数名 = function([参数1,参数2,...]){
//    
//}


```



##### **函数参数**

```javascript
sum(a,b){
	console.log(a+b);
}

sum(123,456);

//调用函数不会检查实参类型
//需要注意赋值给函数对象的形参的合法性
//多余的实参不会被赋值

//对象作为函数参数
function fun(params){
	console.log(params.name+":"+params.age);    
}

var params = {name:"蒋小凡",age:18};

fun(params);//蒋小凡:18
```

**函数返回值和参数可以是任意值，可以是对象**



##### **立即执行函数**

```javascript
//立即执行函数
(function(){
    alert("我是一个匿名函数");
})();

(function(a,b){
    console.log("a =" + a);
    console.log("b =" + b);
})(123,456);
```



##### 类方法

如果一个函数作为对象属性存储，调用函数即为调用对象的方法

```javascript
var obj = new Objcet();
obj.name = "猪八戒";
obj.sayName = funcction(){
    console.log(obj.name);
}

//console.log(obj.sayName);
obj.sayName();

//console.log();调用的console对象的log方法
```

##### 枚举对象中的属性

```javascript
//使用for ... in 语句
//for(var 变量 in 对象){
//    
//}

//for ... in对象中有几个属性，循环体执行几次
for(var n in obj){
    console.log("属性名：" + n + "属性值："+ obj[n]);
}
```



##### window对象

浏览器提供了window对象,

所有在全局域中的变量都作为window对象存储

创建的函数都作为window对象的方法保存

```javascript
var a = 1;
var b = 2;
console.log(window.a);//1
```



##### 声明提前

```javascript
变量的声明提前
	-使用var关键字声明的变量，会在所有代码执行前声明完
	-如果声明变量不使用var关键字，则不会提前声明

函数的声明提前
	-使用函数声明形式创建的函数function 函数(){}
		它会在所有的代码执行之前就被创建，所以可以在任何位置调用
   	-使用函数表达式var = ...创建的函数不会声明提前
```



##### 隐含参数this

调用函数时浏览器会向函数传递隐含参数this

```javascript
//类似于java类中的this，指向包含该方法的类
function fun(a,b){
	console.log(this);
}
```



##### 使用工厂方法创建对象

```javascript
//通过该方法大批量创建方法
//使用工厂方法创建的对象都是Object
function createPerson(name,age,gender){
    var obj = new Object();
    
    //向对象中添加属性
    obj.name = name;
    obj.age = age;
    obj.gender = gender;
    
    //将新对象返回
    return obj;
}

var obj1 = createPerson("竹巴坚",28,"男");

```



##### 构造函数

```javascript
//构造函数，首字母大小
//构造函数执行流程
//调用构造函数
	-在堆中立刻创建新对象
	-将新对象设置为函数中的this
	-将新对象作为返回值返回
function Person(){
	
}

var per = new Person();
```



##### 原型

**prototype**

**创建的每一个函数，解析器都会给函数自己一个属性prototype**

**该属性对应一个对象，为原型对象**

**当我们以构造函数方式声明对象，都会以一个\_proto\_来指向类中的属性对象**

**一般找类中的属性，如果属性中没有，会去类中的原型找**

```javascript
function MyClass(){
    
}

var mc = new MyClass();
console.log(mc._proto_ == MyClass.prototype);

//向对象的prototype中添加内容，类似于java中的静态变量
MyClass.prototype.a = 123;

console.log(mc.a);

//可以利用hasOwnProperty("");方法查看类中是否有该属性,原型中有某属性，该方法无法判断出来，
mc.hasOwnProperyt("age");//false
```



##### **原型链（只有两层）**

\<class\>._proto\_.\_proto\_\.\_proto\_为null

当我们使用一个对象的属性和方法时，会在自身中寻找

​	自身对象中没有，会去原型中找

​	如果原型中没有，会去原型中的原型中找



##### 数组对象

数组也是对象，但是以索引为属性名

```javascript
//创建数组对象
var arr = new Array();
console.log(typeof arr);//object
arr[0] = 10;

//数组长度,对于连续的数组可以获取长度
//对于非连续数组，会获取最大索引+1;
console,log(arr.length);

//如果修改length的长度，那么多余的元素会被删除

//往数组后面增加值
arr[arr.length] = 20;

//使用字面量创建数组
var arr = [1,2,3,4,5,10];

//创建一个长度为10的数组
var arr = new Array(10);
```

**数组常用方法**

```javascript
//push();
//该方法向数组末尾添加一个或多个元素，并返回新数组的长度

var arr = new Array();

arr.push("唐僧");
arr.push("蜘蛛精","白骨精"):

//pop();
//该方法可以删除数组最后一个元素，返回删除的元素
arr.pop();

//unshift();
//向数组开头添加一个或多个元素，并返回新数组长度
arr.unshift("牛魔王");

//shift();
//删除并返回数组的第一个元素
arr.shift();

//slice();
//从某个已有的数组返回选定的元素
//该方法不会改变原数组
//参数: 1.截取开始的位置索引(包含开始索引) 2,截取结束位置的索引(不包含结束索引)
//第二个参数省略，截取开始到末尾
//参数为负数为倒数
var arr = [1,2,3,4,5];
arr.slice();

//splice();
//可以删除指定元素
//会影响到原数组，并将被删除的元素作为返回值返回
//参数：1。表示开始位置索引	2.表示删除的数量
//第三个及以后的参数，可以传递新的元素，这些元素会自动插入开始位置索引的前面
arr.splice(0,2,100,100);
```

**数组其它方法**

```javascript
//concat();
//连接两个或多个数组并返回新数组
//该方法不会对原数组产生影响

var arr = [1,2,3,4];
var arr2 = [5,6,7,1];
var arr3 = [8,9,0];
arr.concat(arr2,arr3,"牛魔王");

//join()
//该方法可以将数组转换为字符串
//可以指定一个字符串为连接符,如果不指定则默认逗号为连接符
var result = arr.join("-");

console.log(typeof result);//string
console.log(result);//"1-2-3-4";

//reverse();
//该方法用来反转数组
//该方法对原数组有影响

arr.reverse();

//sort()对数组元素进行排序
//sort()会默认按unicode编码进行排序
arr.sort();

//即使使用纯数字数组，使用sort()排序，也会按照unicode编码进行排序
//我们可以在sort中添加回调函数
//它使用那个元素调用不确定，但肯定数组中a一定在b的前面
//浏览器会根据返回值决定元素顺序,如果返回大于0，则元素交换
//返回小于0，元素位置不变
//返回等于0，认为两个元素相等，不交换

arr.sort(function(a,b){
    if(a > b){
        return 1;
    }else if(a < b){
        return -1;
    }else{
        return 0;
    }
    
    //return a - b;
})

```

**数组遍历**

**forEach（）循环ie8以下无法兼容**

```javascript
//for循环

//forEach
var arr = [1,2,3,4,5];
//数组元素以实参的新式传递给回调函数
//浏览器调用foreach传三个参数
//第一个参数：当前正在遍历的元素
//第二个参数：当前正在遍历元素的索引
//第三个参数：第三个参数是正在遍历的数组本身
arr.forEach(function(value,index,obj){
    
});
```



##### 函数的方法

```javascript
//call(),apply();
//都是函数对象的方法，需要函数对象调用
function fun(){
    alert("我是fun函数!");
}

fun.call();//调用函数
fun.apply();//调用函数
fun();//调用函数

//区别
//在调用call()和apply()可以将第一个对象指定为第一个参数
//即此时这个对象将会成为函数执行时的this
//call()方法第一个参数往后跟的是实参
fun.call(obj,1,2);
//appky()方法的实参需要封装到数组里面
fun.apply(obj,[1,2]);
```



##### arguments

调用函数，浏览器每次都会传递两个隐含实参

1.函数上下文对象arguments

2.封装实参的对象 arguments

arguments是一个类数组对象，不是数组，但可以通过索引来获取数据，也可获取长度

即使不定义形参，也能得到传进来的实参

arguments[0]第一个实参

**arguments**中有个属性callee，对应的是当前正在执行的函数对象



##### Date对象

常用方法参考文档

```javascript
//创建一个Dat对象
//如果直接使用构造函数的方式创建对象，则会封装当前代码执行的时间
var d = new Date();

//创建指定时间对象
//通过构造函数构造一个表示时间的字符串为参数
//日期格式 月/日/年 时:分:秒
var d2 = new Date("12/03/2019 11:10:30");

console.log(d);

//d2.getMonth();获取月份
//0-11
//0表示一月

//getTime();
//获取当前对象的时间戳
//计算机底层保存时间都用的时间戳

//直接获取当前时间的时间戳
var time = Date.now();
```



##### Math对象

**Math和其他对象不同，它不是构造函数，是工具类，不用创建对象**

```javascript
//cell();
//对数进行上舍入
//即向上取整，小数位只要有值则向上进一

//floor();对数进行向下取整，舍去小数点

//round():四舍五入取整
console.log(Math.round(1.4));//1

//random(),返回一个0-1之间的随机数
console.log(Math.random());

//生成x-y之间的随机数
Math.round(Math.ranom()*(y-x)+x);

//max,min()获取多个数的最小值

```



##### 包装类

在js中提供了三个包装类，可以将基本数据类型转换为对象

String();

​	将基本数据类型字符串转换为String对象

Number();

Boolean();同上

```javascript
var num = new Number();
console.log(typeof num);//Object

//向num中添加一个属性

num.hello = "abscd";
console.log(num.hello);//abscd
```



##### 字符串相关方法

js创建一个字符串，底层是用字符数组存储

```javascript
//charAt();
//charCodeAt();返回字符编码(Unicode)
//fromCharCode();根据字符编码转换为字符;
//concat()
//indexOf();找字符串中含有指定内容，返回第一次出现的索引，没有则返回-1
//第二个参数可以指定查找位置
//lastIndexOf();从后往前搜索

//slice();和数组相似
//subString();第一个参数是开始位置索引，第二个参数是结束位置索引
//和slice区别:
//subString()该方法不支持第二个参数为负值，不能从后往前
//subString()会自动调整参数位置，如果第二个小于第一个，会自动交换

//split();将一个字符串拆分为一个数组
//和java类似
```



##### 正则表达式

**匹配模式：**

**i	忽略大小写**

**g	全局匹配模式**

```javascript
//创建正则表达式对象
//var 变量 = new RegExp("正则表达式","匹配模式");
//使用typeof代表正则对象，会返回Object
//RegExp("a");检测字符串是否含有a
//严格区分大小写
var reg = new RegExp("a",);

//正则表达式方法：
//test();
//检查一个字符串是否符合正则表达式的规则
//对返回true,否则返回false
```

**正则语法**

```javascript
//正则字面量形式
var reg = /a/i;//a为正则表达式,i为匹配模式，

//检查字符串中有a或者b
// "|"表达或的意思
// [ab] == a|b
var vreg = /a|b/;//a或b

//检查字符串是否有字母
//[a-z]表示任意小写字母
//[A-Z]任意大写字母
//[A-z]表示任意字母
//[0-9]表示任意数字
var reg = /[a-z]/

//检查一个字符串中是否含有abc 或 adc
var reg = /abc|adc|aec/
var reg = /a[bde]c/

//"[^ ]" 取反，除了ab外的东西
var reg = /[^ab]/

//量词
//一个内容出现的次数
// -{n}正好出现n次,只能重复{}前面的字符
var reg = /a{3}/;
reg = /(ab){3}/;

//-(n) 找连续出现的n次
reg = /a(3)/;

//出现1~3次{1,3}  {n,}n次以上
reg = /ab{1,3}c/;

"abbc";//true;

//+ 至少一个
//b+ 至少一个b，相当于b{1,}
reg = /ab+c/;

//* 0个或多个，相当于{0,}

//? 0个或一个，相当于{0,1}

// /^a/ 表示以a开头
// /b$/ 表示以b结尾

//例子：手机号正则
//1.以1开头 2.第二位3-9任意数字 3.三位以后任意数字
var phoneReg = /^1[3-9][0-9]{9}$/;

// 。表示任意字符
//可以转义\. 来表示.
//注意：当使用构造方法创建正则，参数是字符串，需要两个斜杠
reg = new RegExp("\\.");

// \w 任意字母，数字,_ [A_z0-9_]
// \W 除了以上
// \d 任意数字
// \D 除了以上
// \s 空格
// \S 除了空格

// \b 单词边界
// \B 除了单词边界
//测试一个单词有child
reg = /\bchild/;

text = "children"//false

//去除字符串前后空格
var str = "            hello  ";

str = str.replace(/^\s*|\s*$/);

//例子：邮件的正则表达式
//hello@abc.com.cn
// 任意字母数字下划线 . 任意字母数字下划线 @ 任意字母数字 .任意字母[2-5].任意字母[2-5]
//^\w{3,} (\.\w+)* @ [A-z0-9]+ (\.[A-z]{2,5}){1,2}$
emailReg = /^\w{3,}(\.\w+)*@[A-z0-9]+(\.[A-z]{2,5}){1,2}$/
```

**支持正则表达式的String对象方法**

```javascript
//split();拆分字符串
//不指定全局匹配也会拆分
var str = "1a2b3c4d5e";

//根据任意字母拆分字符串
//阔以传递正则表达式作为参数
var result = str.split(/[A-z]/)://1,2,3,4,5

//search()搜索字符串中是否含有指定内容
//和java的indexOf类似
str = "hello abc hello abc";
result = str.search("abc");//6 a的第一次出现的索引

//搜索字符串中是否含有 aec 或者 afc
result = str.search(/a[ef]c/);

//match();可以根据正则表达式将字符串中符合的提取出来
//默认情况下match只会找到第一个符合要求的字符
//可以设置正则表达式为全局表达式g
//match()会将匹配的内容封装到数组中，一个也封装到数组中
result = str.match(/[a-z]/ig);//[abcde]

//replace()将字符串指定内容替换为新的内容
//参数：1.被替换的内容， 2。替换的内容
//默认只会替换一个
result = str.replace("a","@_@");

result = str.replace(/a/ig,"@_@");
```

