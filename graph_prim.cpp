//用最小堆实现图的最小生成树的prim算法
//author:william xie
//time:16年5月23
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
class node{
public:
	int serial_num;
	bool is_used;//是否已经被加入到最小生成树中
	vector<int> childs;//生成树中的子节点
	node(int s):serial_num(s),is_used(false){}
	node& operator=(node no){
		serial_num=no.serial_num;
		is_used=no.is_used;
		childs=no.childs;
	}
};
class edge{
public:
	double weight;
	int tail;//边的尾节点在node_list中的下标
	int head;//边的头节点在node_list中的下标
	edge():weight(0),tail(0),head(0){}
	edge(double w,int t,int h):weight(w),tail(t),head(h){}
	edge& operator=(edge e){
		weight=e.weight;
		tail=e.tail;
		head=e.head;
	}
	bool operator>(edge e){
		return (weight>e.weight);
	}
};
int root;
vector<node> node_list;//存放所有的节点
vector<edge> edges;//存放边，用此数组进行最小堆操作

void percolate_down(int i,int current_size){//递归下滤操作
	int left=i<<1;
	if(left>current_size)
		return;
	int right=i<<1+1;
	int min_one;
	if(right<=current_size)
		min_one=(edges[left].weight<edges[right].weight)?left:right;
	else
		min_one=left;
	if(edges[i].weight>edges[min_one].weight){
		edge temp=edges[i];
		edges[i]=edges[min_one];
		edges[min_one]=temp;
		percolate_down(min_one,current_size);
	}
}
void adjust(int current_size){//调整最小堆
	for(int i=current_size>>1;i>=1;--i)
		percolate_down(i,current_size);//所有有子节点的节点进行下滤操作。
}
void heap(){
}
void prim(int& n,int& m){
	cout<<"prim..."<<endl;
	int nodes_num=n;
	int current_size=m;
	adjust(current_size);
	edge top=edges[1];//首先对最小边操作，因为它和以后的判断逻辑不一样
	node_list[top.tail].is_used=true;//把首尾节点都加到树中。
	node_list[top.head].is_used=true;
	node_list[top.tail].childs.push_back(top.head);//把头节点加入到尾节点的孩子数组中，构成树结构
	root=top.tail;//把树根存储起来
	nodes_num--;
	edges[1]=edges[current_size];
	edges.erase(edges.begin()+current_size);
	current_size--;
	percolate_down(1,current_size);
	while(nodes_num>1){//nodes_num不需要到0，到1时所有节点已经都加到树里面了。
		top=edges[1];
		//如果top满足条件，就像对第一条边那样处理。但要把不在树中的节点加到树中节点的孩子中。（注意顺序）
		//如果top不能满足条件，就调整最小堆。
		//具体解释见<a href="https://github.com/dewilliam/data-structure-and-algorithm/blob/master/%E5%9B%BE-%E6%97%A5%E8%AE%B0.md">图-日记.md中</a>
		while(current_size){
			if(node_list[top.tail].is_used!=node_list[top.head].is_used){
				if(node_list[top.tail].is_used)
					node_list[top.tail].childs.push_back(top.head);
				else
					node_list[top.head].childs.push_back(top.tail);
				node_list[top.tail].is_used=true;
				node_list[top.head].is_used=true;
				nodes_num--;
				edges[1]=edges[current_size];
				edges.erase(edges.begin()+current_size);
				current_size--;
				break;
			}else{
				edge temp=edges[1];
				edges[1]=edges[current_size];
				edges[current_size--]=edges[1];
				percolate_down(1,current_size);
				top=edges[1];
			}
		}
		if(!current_size){
			current_size=edges.size();
			adjust(current_size);
		}
	}
}
void tree_out(int r,int h){//递归遍历整棵树。。。
	for(int i=0;i<h;++i)
		cout<<"     ";
	cout<<node_list[r].serial_num<<endl;
	int nh=h+1;
	for(int i=0;i<node_list[r].childs.size();++i){
		int num=(node_list[r].childs)[i];
		tree_out(node_list[num].serial_num,nh);
	}
}
int main(){
	//读取文件数据
	int n,m;
	string file="data/dinic_data";
	fstream out(file.c_str(),ios::in);
	string init;
	getline(out,init);
	stringstream ss_init(init);
	ss_init>>n>>m;
	edge ed;
	edges.push_back(ed);
	//生成边集合
	for(int i=1;i<=m;++i){
		string data;
		getline(out,data);
		stringstream ss(data);
		int x,y;
		double w;
		ss>>x>>y>>w;
		edge ee(w,x,y);
		edges.push_back(ee);
	}
	//生成顶点集合。。
	node title(0);
	node_list.push_back(title);
	for(int i=1;i<=n;++i){
		node no(i);
		node_list.push_back(no);
	}
	prim(n,m);
	tree_out(root,0);
}
