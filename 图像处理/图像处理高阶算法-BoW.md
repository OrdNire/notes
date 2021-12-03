## BoW(Bag of words) 词袋算法

> 参考博客 https://blog.csdn.net/tiandijun/article/details/51143765
> 				https://www.jianshu.com/p/7aceda6a0487



**什么是BoW？**

最初的Bag of words，也叫做“词袋”，在信息检索中，Bag of words model假定对于一个文本，忽略其词序和语法，句法，将其仅仅看做是一个词集合，或者说是词的一个组合，文本中每个词的出现都是独立的，不依赖于其他词 是否出现，或者说当这篇文章的作者在任意一个位置选择一个词汇都不受前面句子的影响而独立选择的。

最后将 BoW 扩展到图像上，就是提取图像的特征点，并进行分类形成一个 codebook ，利用这个 codebook 去做图像的分类。

**Bow的步骤总结：**

- 提取图像库中所有图像的局部特征，例如sift，得到特征集合*F*
- 对特征集合*F*进行聚类，得到*k*个聚类中心$\{C_i|i = 1,..,k\}$，每一个聚类中心$C_i$代表着一个视觉词汇。聚类中心的集合就是视觉词典
  $vocabulary = \{C_i|i = 1,..,k\}$
- 一幅图像的BoW表示
  - 提取图像的局部特征，得到特征集合 $f = \{f_i|i = 1,..,k\}$
  - 计算特征$f_i$属于哪个词汇$C_i$（到该中心的距离最近）
  - 统计每个词汇$C_i$在图像中出现的频率，得到一个一维向量，该向量就是图像的BoW表示



![](https://images2018.cnblogs.com/blog/439761/201808/439761-20180807095403053-295725057.jpg)



详细使用的方法参考博客 https://blog.csdn.net/tiandijun/article/details/51143765

其中分类时用到了 k-means 聚类算法，[K-means（非常详细）](https://zhuanlan.zhihu.com/p/78798251)

示例：

利用 [GitHub - lucifer726/bag-of-words-: 基于opencv-python的sift、kmeans、bow图像检索](https://github.com/lucifer726/bag-of-words-) 测试图像检索

代码进行了一些改进，但效果好像不怎么样

![](https://note.youdao.com/yws/api/personal/file/4F2FA1D8D7C444ACA49141026D508F57?method=download&shareKey=536cfaf762b6b5ecfd57897eb8333b23)



