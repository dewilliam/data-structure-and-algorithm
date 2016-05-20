#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
class Node{
public:
	int serial_num;//顶点编号
	string name;//顶点名称
	vector<pair<int,int> >* list;//保存邻接顶 点信息的列表指针
	unsigned int distence;//距离初始顶点的距离
	Node* parent;//在最短路径中的父节点
	bool marked;//是否已经做过最短路径节点（是否已经在S集合中）
	Node(int s,string n,vector<pair<int,int> >*l):serial_num(s),name(n),list(l),distence(0xFFFFFFFF),parent(NULL),marked(false){}
};
void dijkstra(vector<Node*>&node_lists,int start){
	cout<<"dijkstra..."<<endl;
	Node* source=node_lists[start-1];
	source->distence=0;//初始顶点的初始化
	source->parent=source;//初始顶点的初始化
	vector<Node*>S;//保存处理过的顶点的集合
	S.push_back(source);
	// node_lists[start-1]=NULL;
	int nums=node_lists.size()-1;
	while(nums){
		int s_size=S.size();
		Node* now=S[s_size-1];//去最新的一个顶点进行处理
		unsigned int mindis=0xFFFFFFFF;
		int min_one=0;
		for(int i=0;i<now->list->size();++i){//
			vector<pair<int,int> >this_list=*(now->list);
			int other_node_num=this_list[i].first;
			Node* other_node=node_lists[other_node_num-1];
			if(other_node_num==start||other_node->marked)//不处理初始顶点和已经标记过得顶点
				continue;
			if((now->distence+this_list[i].second)<other_node->distence){//“松弛”过程
				other_node->distence=now->distence+this_list[i].second;
				other_node->parent=now;
			}
			if(other_node->distence<=mindis){//找到最小距离点，即为下一个处理的点
				mindis=other_node->distence;
				min_one=other_node_num;
			}
		}
		if(min_one==0)//说明邻接表中全是初始顶点和已经 处理过的顶点，所以不需要在继续
			break;
		Node* min=node_lists[min_one-1];
		min->marked=true;
		S.push_back(min);//把最小距离节点加到S集合的末尾，下一循环就处理它，并标记为已处理
		--nums;//为处理节点书减一，当减到0时DIJKSTRA就over
	}
}
void find(vector<Node*>&node_lists,int end){
	cout<<"find..."<<endl;
	Node* now=node_lists[end-1];
	int dis=now->distence;//路径终端的节点保存的distance值 就是到初始顶点的值
	while(now->parent!=now){//循环找父节点
		cout<<now->serial_num<<",";
		now=now->parent;
	}
	cout<<now->serial_num<<endl;
	cout<<"distence:"<<dis<<endl;
}
int main(){
	int start=clock();
	//从文件中按格式读取数据
	vector<Node*>node_lists;
	string file="data/map_data";
	fstream out(file.c_str(),ios::in);
	string each_line;
	getline(out,each_line);
	while(!out.eof()){
		stringstream ss(each_line);
		int serial_num;
		string name;
		int num;
		ss>>serial_num>>name>>num;
		vector<pair<int,int> >* new_list=new vector<pair<int,int> >(num);
		for(int i=0;i<num;++i){
			int v;
			int distence;
			ss>>v>>distence;
			pair<int,int> new_pair=make_pair(v,distence);
			(*new_list)[i]=new_pair;
		}
		Node* no=new Node(serial_num,name,new_list);
		node_lists.push_back(no);
		getline(out,each_line);
	}
	dijkstra(node_lists,5);
	printf("time: %.6lf\n",double(clock()-start)/CLOCKS_PER_SEC);
	while(true){
		int end;
		cin>>end;
		find(node_lists,end);
	}
	// cout<<node_lists.size()<<endl;
	// cout<<node_lists[0]->serial_num<<","<<node_lists[0]->name<<endl;
	// vector<pair<int,int> >test=*(node_lists[0]->list);
	// cout<<test[0].first<<","<<test[0].second<<endl;
	// cout<<test.size()<<endl;
	// node_lists[0]=NULL;
	// test=*(node_lists[1]->list);
	// cout<<node_lists[1]->serial_num<<","<<node_lists[1]->name<<endl;
	// cout<<test[0].first<<","<<test[0].second<<endl;
	// cout<<test.size()<<endl;
}
