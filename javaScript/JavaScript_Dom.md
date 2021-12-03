# DOM

## 简介

Document Object Model文档对象模型

通过js操作html中的标签

![image-20200827092822665](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200827092822665.png)

**节点**

文档节点：整个HTML文档

元素节点：HTML文档中的HTML标签

属性节点：元素的属性

文本节点：HTML标签中的文本内容

## 事件

我们可以在事件对应的属性中设置一些js代码，事件触发js执行

结构和行为耦合，不推荐



可以为一个元素绑定一个函数(推荐使用)

```javascript
<button id="btn">我是一个按钮</button>

<script>
    var btn = document.getElementById("btn");
    console.log(btn);;

    btn.onclick = function(){
        alert("你点我了");
    }
</script>
```



**onload事件**

onload事件会在页面加载完毕后会触发(其中写js)

```javascript
//会在整个页面加载完成后执行
window.onload = function(){
    alert("hello");
}
```



**getElementsByTagName方法**

通过标签名返回一组元素的对象

```javascript
//返回一组数据，数组
var lis = documents.getElementsByTagName("li");

//遍历
for(let i = 0;i < lis.length; i ++){
    console.log(lis[i].innerHTML);
}
```



**getElementsByName方法**

通过name返回一组数据

```javascript
var inputs = documents.getElementsByName("gender");

//对于radio的type 
//innerHTML元素内部的HTML标签
//对于自结束标签无意义
for(let i = 0;i < lis.length; i ++){
    alert(lis[i].value);//直接读属性名
    alert(lis[i].className);
}
//class是无法用"."来读取，只能以className读取
```

