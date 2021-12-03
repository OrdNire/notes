# Object的equals方法和hashCode方法覆写

equals方法覆写，可用来判断两个对象是否相等

### 标准:

```java
@Override
public boolean equals(Object obj){
    if(obj == null)
        return false;
    if(getClass() != obj.getClass())
        return false;
    T other = (T) obj;
    if(.....)
        return false;
    return true;
}
```

以Student类为例

```java
@Override
public boolean equals(Object obj){
    if(obj == null)
        return false;
    if(getClass() != obj.getClass())
        return false;
    Student other = (Student) obj;
    if(!sno.equals(other.sno))
        return false;
    return true;
}
```

### hashCode方法

**map中put方法，map中同时有hashTable存储hash值对应的对象，如果put一个对象，根据hash值找，如果不存在则存入，否则调用equals方法，如果相同则不存，不同则更换散列地址存储**

**必须同时覆写equals和hashCode方法**

如果未覆写hashCode方法，例如学生类，id相同为同一个学生，如果hashCode未覆写，则创建两个id相同的学生，得到的hashCode是不同的值，在使用map等集合的时，认为时两个不同的元素

**同样，hashCode方法编写需要用类中不易变更的属性作为计算元素。**