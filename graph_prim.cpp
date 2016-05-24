#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
class node{
public:
	int serial_num;
	bool is_used;
	vector<int> childs;
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
	int tail;
	int head;
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
vector<node> node_list;
// vector<node> used_list;
vector<edge> edges;

void percolate_down(int i,int current_size){
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
void adjust(int current_size){
	for(int i=current_size>>1;i>=1;--i)
		percolate_down(i,current_size);
}
void heap(){
}
void prim(int& n,int& m){
	cout<<"prim..."<<endl;
	int nodes_num=n;
	int current_size=m;
	adjust(current_size);
	edge top=edges[1];
	node_list[top.tail].is_used=true;
	node_list[top.head].is_used=true;
	node_list[top.tail].childs.push_back(top.head);//
	root=top.tail;
	nodes_num--;
	edges[1]=edges[current_size];
	edges.erase(edges.begin()+current_size);
	current_size--;
	percolate_down(1,current_size);
	while(nodes_num>1){
		top=edges[1];
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
				cout<<"cu:"<<current_size<<endl;
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
void tree_out(int r,int h){
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
	int n,m;
	string file="data/dinic_data";
	fstream out(file.c_str(),ios::in);
	string init;
	getline(out,init);
	stringstream ss_init(init);
	ss_init>>n>>m;
	edge ed;
	edges.push_back(ed);
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
	node title(0);
	node_list.push_back(title);
	for(int i=1;i<=n;++i){
		node no(i);
		node_list.push_back(no);
	}
	prim(n,m);
	tree_out(root,0);
}
