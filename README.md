# ICP-demo

环境搭建：visual studio 2017 + PCL 1.9.1

配置环境参考：https://blog.csdn.net/STV1536797462/article/details/93981308

算法思想：迭代最近点算法，将两张点云图融合为一张点云图。

控制台输出为：旋转矩阵 R 和 偏移矩阵 t。

点云图可以在meshlab中查看，输入的点云图originalM.xyz 和 originalT.xyz，将两幅图合成一张点云图rotatedT.xyz.