<h2>16年5月19，周四</h2>
用邻接表保存图信息。<br>
在磁盘中用一下形式保存：<br>
1 beijing 3 2 30 3 60 5 100<br>
2 tianjin 2 1 30 4 200<br>
3 tangshan 1 1 60<br>
4 nanjing 1 2 200<br>
5 jinan 1 1 100<br>
每列开头为顶点编号，顶点名称。<br>
之后:第一个为与该顶点相邻的顶点个数，后面是每个相邻顶点的编号，和边的权值。<br>
<br>
在内存中保存形式为：<br>
用pair<int,int>保存相邻的顶点和权值。<br>
每一个顶点的所有pair都放在一个vector里面。<br>
定义一个Node类，保存顶点信息（顶点编号，顶点名称，指向对应vector的指针）。<br>
Node --> vector(pair(int,int),pair(int,int),...)。<br>
<br>
dijkstra算法时，从源顶点开始，遍历它的邻接表中的顶点，更新每个顶点的distance值，找到最小的那个，重复执行<br>
每执行一次上述逻辑，list_num计数器减一，直到list_num==0为止<br>
<br>
不知道对不对，，，晚上试一下<br>

<h3>22:52</h3>
上述方法可以实现，但要在每个节点上在加一个属性marked，某个节点做过最小距离的节点后，marked置为true，以后就不再处理该节点<br>
源代码放在dijkstra.cpp中<br>
