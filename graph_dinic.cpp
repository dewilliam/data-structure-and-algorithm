//用邻接矩阵，层次数组实现了一个基本的dinic算法
//详细解释和写算法的过程见《图-日志.md》
//author:谢添
//location:北京交通大学 下一代互联网与互联工程国家工程实验室
//email:mftianxie@gmail.com
//time:16年5月22
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;
bool BFS(double** table,int* dist,int source,int num){
	for(int i=0;i<num;++i)//每次BFS都初始化距离
		dist[i]=-1;
	dist[source]=0;//源顶点距离置0
	queue<int> list;
	list.push(source);
	while(!list.empty()){
		int this_node=list.front();
		list.pop();
		for(int i=1;i<num;++i)
			if(dist[i]<0&&table[this_node][i]>0){
				dist[i]=dist[this_node]+1;
				list.push(i);//每个下一层的新顶点都加入到队列
			}
	}
	if(dist[num-1]<0)
		return false;
	return true;
}
double dinic(double** table,int* dist,int this_node,int num,double flow){
	if(this_node==num-1)//汇节点时，直接返回flow值
		return flow;
	double down_min;
	for(int i=1;i<num;++i){
		double min=(flow<table[this_node][i])?flow:table[this_node][i];//找到最小值，比较下层最小和当前边谁比较小。
		if(table[this_node][i]>0&&dist[i]==(dist[this_node]+1)){
			down_min=dinic(table,dist,i,num,min);//返回下面节点中的最小值。
			if(down_min){
				table[this_node][i]-=down_min;
				table[i][this_node]+=down_min;//反向弧增加相应的流量
				return down_min;
			}
		}
	}
	return 0;
}
int main(){
	int start=clock();
	int n,m;
	string file="data/dinic_data";
	fstream out(file.c_str(),ios::in);
	string init;
	getline(out,init);
	stringstream ss_init(init);
	ss_init>>n>>m;
	n++;
	double** table=new double* [n];//邻接矩阵的初始化和读取文件赋值
	for(int i=0;i<n;++i)
		table[i]=new double [n];
	for(int i=0;i<m;++i){
		string data;
		getline(out,data);
		stringstream ss(data);
		int x,y;
		double w;
		ss>>x>>y>>w;
		table[x][y]=w;//点x和点y连边的权值（流量）为w
	}
	int* dist=new int[n];
	int source=1;
	double total_min=0;
	double max=0xFFFFFFFF;
	while(BFS(table,dist,source,n)){
		double this_flow;
		while(this_flow=dinic(table,dist,source,n,max))
			total_min+=this_flow;
	}
	cout<<"total_min:"<<total_min<<endl;
	printf("time: %.6lf\n",double(clock()-start)/CLOCKS_PER_SEC);
}
