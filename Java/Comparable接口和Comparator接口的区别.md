# Comparable接口和Comparator接口的区别

### Comparable

源码

```java
package java.lang;
import java.util.*;

package java.lang;
public interface Comparable<T> {
    public int compareTo(T o);
}
```

可见，使用Comparable接口需要实现其接口并覆写其中的compareTo()方法

```
int compareTo(T o)

比较此对象与指定对象的顺序。如果该对象小于、等于或大于指定对象，则分别返回负整数、零或正整数。

参数： o - 要比较的对象。

返回：负整数、零或正整数，根据此对象是小于、等于还是大于指定对象。

抛出：ClassCastException - 如果指定对象的类型不允许它与此对象进行比较
```

### Comparator

源码

```java
package java.util;

import java.io.Serializable;
import java.util.function.Function;
import java.util.function.ToIntFunction;
import java.util.function.ToLongFunction;
import java.util.function.ToDoubleFunction;
import java.util.Comparators;

public interface Comparator<T> {
	int compare(T o1, T o2);
	//还有很多其他方法...
}
```

Comparator可以通过类实现其接口并覆盖compare方法。

**还能通过在类内部将该接口的匿名类对象当作参数传给Collection.sort/Arrays.sort方法**

可不改变代码而实现对类不同方式的排序

**Comparator接口中还有其它方法**

Comparator.reversed()方法，将**排序好**的进行逆序

Comparator.thenComparing(...)，多层排序