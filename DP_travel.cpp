//author:谢添
//location:北京交通大学 下一代互联网与互联工程国家工程实验室
//email:mftianxie@gmail.com
//程序的具体思路和解释看《算法-日记.md》旅游花费部分问题。。。
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;
class node{
public:
	int serial_num;
	string name;
	int parent;
	double path;
	double fee;
	bool marked;
	vector<pair<int,double> >neighbors;
	node(int s,string n,vector<pair<int,double> >nb):serial_num(s),name(n),parent(-1),path(0xFFFFFFFF),fee(0xFFFFFFFF),marked(false),neighbors(nb){}
};
vector<node> graph;
vector<double> fees_list;
void travel(int source,double total_cash){
	cout<<"getting path..."<<endl;
	graph[source].marked=true;
	graph[source].fee=fees_list[source];
	graph[source].path=0;
	queue<int> Q;
	Q.push(source);
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		int size=graph[u].neighbors.size();
		double min_dist=0xFFFFFFFF;
		int min_one=0;
		for(int i=0;i<size;++i){
			int each_neighbor=(graph[u].neighbors)[i].first;
			double each_dist=(graph[u].neighbors)[i].second;
			if((total_cash-fees_list[each_neighbor])<0)
				continue;
			if((graph[u].path+each_dist)<=graph[each_neighbor].path){
				graph[each_neighbor].path=graph[u].path+each_dist;
				if((graph[u].fee+fees_list[each_neighbor])<graph[each_neighbor].fee)
					graph[each_neighbor].fee=graph[u].fee+fees_list[each_neighbor];
				graph[each_neighbor].parent=u;
			}
			if(graph[each_neighbor].path<=min_dist&&graph[each_neighbor].marked==false){
				min_dist=graph[each_neighbor].path;
				min_one=each_neighbor;
			}
		}
		if(min_one!=0){//min_one==0说明已经没有要处理的顶点了
			graph[min_one].marked=true;
			Q.push(min_one);
		}
	}
	cout<<"over..."<<endl;
}
int main(){
	string file="data/travel_data";
	fstream out(file.c_str(),ios::in);
	double total_cash;
	int node_num;
	string title;
	getline(out,title);
	stringstream ss(title);
	ss>>total_cash>>node_num;
	for(int i=0;i<node_num;++i){
		int serial_num;
		string node_name;
		double fee;
		int neighbor_num;
		string data;
		getline(out,data);
		stringstream each(data);
		each>>serial_num>>node_name>>fee>>neighbor_num;
		vector<pair<int,double> >neighbors_list(neighbor_num);
		for(int j=0;j<neighbor_num;++j){
			int nerbor_serial;
			double path;
			each>>nerbor_serial>>path;
			pair<int,double> new_nerbor=make_pair(nerbor_serial,path);
			neighbors_list.push_back(new_nerbor);
		}
		node new_node(serial_num,node_name,neighbors_list);
		graph.push_back(new_node);
		fees_list.push_back(fee);
	}
	int source=0;
	travel(source,total_cash);
	while(true){
		int destination;
		cin>>destination;
		cout<<"total fee:"<<graph[destination].fee<<",	cash after travel:"<<total_cash-graph[destination].fee<<endl;
		while(true){
			cout<<graph[destination].serial_num<<",";
			if(destination==graph[destination].parent)
				break;
			destination=graph[destination].parent;
			if(destination==-1)
				break;
		}
		cout<<endl;
	}
}
