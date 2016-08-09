# 1075 Thread in a space
我们知道在三维空间中 三个不共线的点 可以确定一个平面, 平面CAB 可将球切成如图的一个圆.其中CE, BD 为切线

![图1](https://github.com/liudyboy/Image/raw/ACM/Thread_in_a_Space.jpg)

由图可知所需求的长度为 CE + 弧ED + DB 的长度</br>
我们知 三角形 ADB, ACE 都为直角三角形,并且 由两点的距离公式可知道 AC, AB 长度, 所以由勾股定理可求得CE, DB;</br>
并且 由 cos<CAE = AE / AC , 可求得 <CAE, <BAD  的大小</br>
由向量AB 和 向量AC 可求得 <BAC 的大小</br>
所以 <DAE = <BAC - <BAD - <EAC ; 知道<DAE 便可求出弧长ED;</br>
