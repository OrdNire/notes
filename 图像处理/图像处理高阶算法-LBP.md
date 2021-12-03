## LBP（Local Binary Pattern，局部二值模式）

> 参考博客：https://blog.csdn.net/heli200482128/article/details/79204008
> 					https://blog.csdn.net/chaipp0607/article/details/78161986



**什么是LBP？**

LBP（Local Binary Pattern，局部二值模式）是一种用来描述图像局部纹理特征的算子；它具有旋转不变性和灰度不变性等显著的优点。它是首先由T. Ojala, M.Pietikäinen, 和D. Harwood 在1994年提出，用于纹理特征提取。而且，提取的特征是图像的局部的纹理特征。

**基本LPB算法**

基本LBP算子定义为 $3 * 3$ 的窗口内，以窗口中心像素为阈值，将相邻的8个像素的灰度值与其进行比较，若周围像素值大于中心像素值，则该像素点的位置被标记为1，否则为0。这样，3*3邻域内的8个点经比较可产生8位二进制数（通常转换为十进制数即LBP码，共256种），即得到该窗口中心像素点的LBP值，并用这个值来反映该区域的纹理信息。

![](https://img-blog.csdn.net/20180130113413656?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvaGVsaTIwMDQ4MjEyOA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

简单描述就是说，以中心点为一个阈值，从左上角开始，顺时针计算每一个像素，如果灰度值大于阈值，则为1，否则为0。

然后根据左上角为1，顺时针依次为2，4，8...的权值，计算出每一个二进制值，其转化为十进制的值即为LBP算子计算出在该像素的LBP值。以该值来反映出局部的纹理特征。

**单纯的LBP图像没什么意义，常用LBP直方图来描述一副图像的纹理特征。**

 python 提取基本lbp

```python
import cv2
import numpy as np
import matplotlib.pyplot as plt
import skimage

def set_logical_value(img, x, y, center):
    if(x < 0 or x >= img.shape[0] or y < 0 or y >= img.shape[1]):
        return 0
    else:
        return 1 if img[x, y] > center else 0

def get_basic_lbp(img, x, y):
    binary = []
    center = img[x, y]
    binary.append(set_logical_value(img, x, y - 1, center))
    binary.append(set_logical_value(img, x + 1, y - 1, center))
    binary.append(set_logical_value(img, x + 1, y, center))
    binary.append(set_logical_value(img, x + 1, y + 1, center))
    binary.append(set_logical_value(img, x, y + 1, center))
    binary.append(set_logical_value(img, x - 1, y + 1, center))
    binary.append(set_logical_value(img, x - 1, y, center))
    binary.append(set_logical_value(img, x - 1, y - 1, center))
    return binary

def binary2num(binary):
    binary = binary[::-1]
    bit = 0
    num = 0
    for i in binary:
        num += i << bit
        bit += 1
    return num

def get_basic_lbp_mat(img):
    row = img.shape[0]
    colomn = img.shape[1]
    # img = cv2.copyMakeBorder(img, 1, 1, 1, 1, cv2.BORDER_REPLICATE)
    lbp_mat = np.zeros_like(img)
    for x in range(row):
        for y in range(colomn):
            lbp_mat[x, y] = binary2num(get_basic_lbp(img, x, y))

    return lbp_mat

def get_basic_hist(img):
    hist = cv2.calcHist(img, [0], None, [256], [0, 255])
    hist = cv2.normalize(hist, hist)
    plt.plot(hist)
    plt.savefig("./img85.png")
    plt.show()


img = skimage.data.coffee()


img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
lbp_img = get_basic_lbp_mat(img)
plt.subplot(121)
plt.imshow(img, cmap="gray")
plt.subplot(122)
plt.imshow(lbp_img, cmap="gray")
plt.savefig('./img84.png')
plt.show()
get_basic_hist(lbp_img)
```

![](https://note.youdao.com/yws/api/personal/file/3740CEAC6E9549F18B3E8D7A95AE0E03?method=download&shareKey=af1b4011af6b105c894b53c853ee2aea)

![](https://note.youdao.com/yws/api/personal/file/9F1674681EE2485DB3C370ED02265F7C?method=download&shareKey=d6470f2b8d6824ab8e599e0eddab6932)



### LBP的改进

**LBP圆形算子**

基本的 LBP  算子的最大缺陷在于它只覆盖了一个固定半径范围内的小区域，这显然不能满足不同尺寸和频率纹理的需要。为了适应不同尺度的纹理特征，并达到灰度和旋转不变性的要求，Ojala 等对 LBP 算子进行了改进，将 3×3 邻域扩展到任意邻域，并用圆形邻域代替了正方形邻域，改进后的 LBP 算子允许在半径为 R  的圆形邻域内有任意多个像素点。从而得到了诸如半径为R的圆形区域内含有P个采样点的LBP算子。

![](https://img-blog.csdn.net/20180130113742101?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvaGVsaTIwMDQ4MjEyOA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)



**LBP旋转不变模式**

​		从 LBP 的定义可以看出，LBP 算子是灰度不变的，但却不是旋转不变的。图像的旋转就会得到不同的 LBP值。 
 　　Maenpaa等人又将 LBP 算子进行了扩展，提出了具有旋转不变性的 LBP 算子，即不断旋转圆形邻域得到一系列初始定义的 LBP 值，取其最小值作为该邻域的 LBP 值。 
 　　图 2.5 给出了求取旋转不变的 LBP 的过程示意图，图中算子下方的数字表示该算子对应的 LBP 值，图中所示的 8 种  LBP模式，经过旋转不变的处理，最终得到的具有旋转不变性的 LBP 值为 15。也就是说，图中的 8 种 LBP 模式对应的旋转不变的 LBP  模式都是00001111。 
​		 简单来说就是对圆形LBP算子旋转，因为每一个像素点的权值不一样，所以的出来的LBP在中心点的像素值也不同，从而会导致结果也不一样，所以旋转不变性选取LBP算子旋转后所有情况的最小值，这样可以达到旋转不变性，因为最小值不变。

![](https://img-blog.csdn.net/20180130113806268?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvaGVsaTIwMDQ4MjEyOA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

在上面的图中说明的是，图中的这8种模式，都有相同的旋转不变模式，就是十进制为15的那个值，即00001111。那么对256种模式都做这种旋转，得到最小的数作为这种模式的旋转不变模式，旋转不变模式一共有36种，可以写一个验证，用哈希表统计即可。

利用上述方法来达到旋转不变性

```python
# 计算旋转不变性
def get_rotate_lbp(img, x, y):
    binary = get_basic_lbp(img, x, y)
    res = 1000
    for i in range(8):
        binary.append(binary[0])
        del binary[0]
        res = min(res, binary2num(binary))
    return res

def get_rotate_lbp_mat(img):
    row = img.shape[0]
    colomn = img.shape[1]
    # img = cv2.copyMakeBorder(img, 1, 1, 1, 1, cv2.BORDER_REPLICATE)
    lbp_mat = np.zeros_like(img)
    max_num = 0
    for x in range(row):
        for y in range(colomn):
            num = get_rotate_lbp(img, x, y)
            lbp_mat[x, y] = num
            max_num = max(max_num, num)

    return lbp_mat, max_num

def get_rotate_hist(img, max_num):
    hist = cv2.calcHist(img, [0], None, [max_num], [0, max_num])
    print(max_num)
    hist = cv2.normalize(hist, hist)
    plt.plot(hist)
    plt.savefig("./img86.png")
    plt.show()

    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
lbp_img, max_num = get_rotate_lbp_mat(img)
get_rotate_hist(lbp_img, max_num)
plt.subplot(121)
plt.imshow(img, cmap="gray")
plt.subplot(122)
plt.imshow(lbp_img, cmap="gray")
plt.savefig('./img87.png')
plt.show()
```



**等价LBP**

上面处理的都是只会产生八个 bit 的lbp算子，但当lbp算子越大时，产生的位数也越多，那么会导致很大的二进制模式，随之会引起计算效率低等不良因素。同时，过多的模式种类对于纹理的表达是不利的。例如，将LBP算子用于纹理分类或人脸识别时，常采用LBP模式的统计直方图来表达图像的信息，而较多的模式种类将使得数据量过大，且直方图过于稀疏。

为了解决二进制模式过多的问题，提高统计性，Ojala提出了采用一种“等价模式”（Uniform Pattern）来对LBP算子的模式种类进行降维。Ojala等认为，在实际图像中，绝大多数LBP模式最多只包含两次从1到0或从0到1的跳变。因此，Ojala将“等价模式”定义为：当某个LBP所对应的循环二进制数从0到1或从1到0最多有两次跳变时，该LBP所对应的二进制就称为一个等价模式类。如00000000（0次跳变），00000111（只含一次从0到1的跳变），10001111（先由1跳到0，再由0跳到1，共两次跳变）都是等价模式类。除等价模式类以外的模式都归为另一类，称为混合模式类，例如10010111（共四次跳变）

这里所谓的“跳变”，可以利用两位两位的比较，如果该两位不同则包含一次跳变。

经过这样的分类后，二进制模式会急剧减少。



### 对LBP特征向量进行提取的步骤

1. 首先将检测窗口划分为16×16的小区域（cell）。 

2. 对于每个cell中的一个像素，将相邻的8个像素的灰度值与其进行比较，若周围像素值大于中心像素值，则该像素点的位置被标记为1，否则为0。这样，3*3邻域内的8个点经比较可产生8位二进制数，即得到该窗口中心像素点的LBP值

3. 然后计算每个cell的直方图，即每个数字（假定是十进制数LBP值）出现的频率；然后对该直方图进行归一化处理。 

4. 最后将得到的每个cell的统计直方图进行连接成为一个特征向量，也就是整幅图的LBP纹理特征向量； 

   然后便可利用SVM或者其他机器学习算法进行分类了。 



