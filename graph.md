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
