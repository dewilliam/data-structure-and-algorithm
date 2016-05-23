#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
using namespace std;
void preflow(double** table,int* level,double* R,int source,int terminal,int n){
	queue<int> Q;
	Q.push(source);
	double max_flow=0;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		for(int i=1;i<n;++i){
			if(u==source||level[u]==level[i]+1){
				double min=(R[u]<table[u][i])?R[u]:table[u][i];
				cout<<"u:"<<u<<"i:"<<i<<"min:"<<min<<endl;
				//push flow...
				R[u]-=min;
				R[i]+=min;
				table[u][i]-=min;
				table[i][u]+=min;
				if(i==terminal)
					max_flow+=min;
				//end push
				if(i!=source&&i!=terminal)
					Q.push(i);
			}
		}
		if(u!=source&&u!=terminal&&R[u]>0){
			level[u]+=1;
			Q.push(u);
		}
	}
	cout<<"max_flow:"<<max_flow<<endl;
}
int main(){
  //指针初始化只能在主函数进行，在其他函数中初始化后不能用。。。
	double** table;
	int* level;
	double* R;
	int source=1;
	int terminal=5;
	int n,m;
	string file="data/dinic_data";
	fstream out(file.c_str(),ios::in);
	string init;
	getline(out,init);
	stringstream ss_init(init);
	ss_init>>n>>m;
	n++;
	table=new double* [n];//邻接矩阵的初始化和读取文件赋值
	for(int i=0;i<n;++i)
		table[i]=new double [n];
	for(int i=0;i<m;++i){
		string data;
		getline(out,data);
		stringstream ss(data);
		int x,y;
		double w;
		ss>>x>>y>>w;
		table[x][y]=w;
	}
	level=new int[n];
	R=new double[n];
	for(int i=0;i<n;++i){
		level[i]=0;
		R[i]=0;
	}
	level[source]=n;
	R[source]=0xffff;
	R[terminal]=-1000;
	preflow(table,level,R,source,terminal,n);
}
