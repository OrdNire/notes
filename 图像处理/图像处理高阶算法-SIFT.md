## SIFT算法

> 参考 [SIFT算法详解](https://blog.csdn.net/zddblog/article/details/7521424)

尺度不变特征转换(Scale-invariant feature transform或SIFT)是一种电脑视觉的算法用来侦测与描述影像中的局部性特征，它在空间尺度中寻找极值点，并提取出其位置、尺度、旋转不变量，此算法由 David Lowe在1999年所发表，2004年完善总结。

#### SIFT算法的特点有：

1. SIFT特征是图像的局部特征，其对旋转、尺度缩放、亮度变化保持不变性，对视角变化、仿射变换、噪声也保持一定程度的稳定性；
2. 独特性（Distinctiveness）好，信息量丰富，适用于在海量特征数据库中进行快速、准确的匹配；
3. 多量性，即使少数的几个物体也可以产生大量的SIFT特征向量；
4. 高速性，经优化的SIFT匹配算法甚至可以达到实时的要求；
5. 可扩展性，可以很方便的与其他形式的特征向量进行联合。

#### SIFT算法可以解决的问题：

目标的自身状态、场景所处的环境和成像器材的成像特性等因素影响图像配准/目标识别跟踪的性能。而SIFT算法在一定程度上可解决：

1. 目标的旋转、缩放、平移（RST）

2. 图像仿射/投影变换（视点viewpoint）

3. 光照影响（illumination）

4. 目标遮挡（occlusion）

5. 杂物场景（clutter）

6. 噪声

SIFT算法的实质是在不同的尺度空间上查找关键点(特征点)，并计算出关键点的方向。SIFT所查找到的关键点是一些十分突出，不会因光照，仿射变换和噪音等因素而变化的点，如角点、边缘点、暗区的亮点及亮区的暗点等。

#### Lowe将SIFT算法分解为如下四步：

1. 尺度空间极值检测：搜索所有尺度上的图像位置。通过高斯微分函数来识别潜在的对于尺度和旋转不变的兴趣点。

2. 关键点定位：在每个候选的位置上，通过一个拟合精细的模型来确定位置和尺度。关键点的选择依据于它们的稳定程度。

3. 方向确定：基于图像局部的梯度方向，分配给每个关键点位置一个或多个方向。所有后面的对图像数据的操作都相对于关键点的方向、尺度和位置进行变换，从而提供对于这些变换的不变性。

4. 关键点描述：在每个关键点周围的邻域内，在选定的尺度上测量图像局部的梯度。这些梯度被变换成一种表示，这种表示允许比较大的局部形状的变形和光照变化。

#### SIFT的缺点：

SIFT在图像的不变特征提取方面拥有无与伦比的优势，但并不完美，仍然存在：

1. 实时性不高。
2. 有时特征点较少。
3. 对边缘光滑的目标无法准确提取特征点。
4. 对模糊的图像和边缘平滑的图像，检测出的特征点过少，对圆更是无能为力。



简单示例：

原图

![](https://note.youdao.com/yws/api/personal/file/47B0286E43A74E17AFEE09F0458F890D?method=download&shareKey=767db0db0333c7f8e960e5a6adce5cca)

![](https://note.youdao.com/yws/api/personal/file/10E3DC6EBB784748BD233569CE5B0BE6?method=download&shareKey=4339e768d6fc5c1160f217292aa4f62d)



匹配特征点

> 代码参考 https://blog.csdn.net/qq_44019424/article/details/106010362

```python
import cv2
import matplotlib.pyplot as plt
import numpy as np

img01 = cv2.imread('img01.jpg', -1)
img02 = cv2.imread('tom.jpg', -1)

# 检测关键点
def detect(img):
    # 转为灰度图
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # 创建 descriptor 对象
    descriptor = cv2.SIFT_create()
    kps, features = descriptor.detectAndCompute(img, None)
    return (kps, features)

# 查看特征点
def show_points(img):
    kps, features = detect(img)
    print("特征点数量:{}".format(len(kps)))
    img_points = cv2.drawKeypoints(img, kps, img)
    cv2.imshow('key_points_image',img_points)
    cv2.waitKey()

# 匹配特征点
def match_key_points(kps_left, kps_right, features_left, features_right, ratio, threshold):
    """
    :param kps_left:
    :param kps_right:
    :param features_left:
    :param features_right:
    以上为两张图片的特征点和特征向量
    :param ratio:
    :param threshold: 阈值
    """

    # 建立暴力匹配器
    matcher = cv2.DescriptorMatcher_create("BruteForce")
    # 使用knn检测
    raw_matches = matcher.knnMatch(features_left, features_right, 2)
    print(len(raw_matches))
    matches = []  # 存坐标，为了后面
    good = []  # 存对象，为了后面的演示

    for m in raw_matches:
        # 筛选条件
        if len(m) == 2 and m[0].distance < m[1].distance * ratio:
            good.append([m[0]])
            matches.append((m[0].queryIdx, m[0].trainIdx))
            """
            queryIdx：测试图像的特征点描述符的下标==>img_left
            trainIdx：样本图像的特征点描述符下标==>img_right
            distance：代表这一处匹配的特征点描述符的欧式距离，数值越小也就说明俩个特征点越相近。
            """

    kps_left = np.float32([kp.pt for kp in kps_left])
    kps_right = np.float32([kp.pt for kp in kps_right])
    print(len(matches))
    if len(matches) > 4:
        # 获取匹配点坐标
        pts_left = np.float32([kps_left[i] for (i,_) in matches])
        pts_right = np.float32([kps_right[i] for (_,i) in matches])
        # 计算变换矩阵(采用ransac算法从pts中选择一部分点)
        H,status = cv2.findHomography(pts_right, pts_left, cv2.RANSAC, threshold)
        return (matches, H, good)
    return None

kps_src, features_src = detect(img01)
kps_dest, features_dest = detect(img02)
matches, H, good = match_key_points(kps_src, kps_dest, features_src, features_dest, 0.5, 0.99)
res_image = cv2.drawMatchesKnn(img01, kps_src, img02, kps_dest, good[:len(good) - 1],None,flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
cv2.imshow('res',res_image)
cv2.waitKey()
```



提取出的特征点：

![](https://note.youdao.com/yws/api/personal/file/294F40830B6A4545B931881B03DF4CD2?method=download&shareKey=280e2fc92f04dc62d276c970df24e677)

![](https://note.youdao.com/yws/api/personal/file/DC850241F10D4BF8BAAB6E9D9A006383?method=download&shareKey=7e79caacac3b52157b207be2fc3d7036)



匹配结果：

![](https://note.youdao.com/yws/api/personal/file/8DDB6E05B77D4D2BB64B8DC904BBACD5?method=download&shareKey=145c9a007eed4646018d0c4906286286)



**SIFT理论原理**

> 参考https://blog.csdn.net/zddblog/article/details/7521424



**SIFT算法原理及其实现**

> [SIFT/sift.py at master · paulaner/SIFT · GitHub](https://github.com/paulaner/SIFT/blob/master/sift.py)
>
> https://thutmose.blog.csdn.net/article/details/84999282

