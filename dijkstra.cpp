#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
class Node{
public:
	int serial_num;
	string name;
	vector<pair<int,int> >* list;
	unsigned int distence;
	Node* parent;
	bool marked;
	Node(int s,string n,vector<pair<int,int> >*l):serial_num(s),name(n),list(l),distence(0xFFFFFFFF),parent(NULL),marked(false){}
};
void dijkstra(vector<Node*>&node_lists,int start){
	cout<<"dijkstra..."<<endl;
	Node* source=node_lists[start-1];
	source->distence=0;
	source->parent=source;
	vector<Node*>S;
	S.push_back(source);
	// node_lists[start-1]=NULL;
	int nums=node_lists.size()-1;
	while(nums){
		int s_size=S.size();
		Node* now=S[s_size-1];
		unsigned int mindis=0xFFFFFFFF;
		int min_one=0;
		for(int i=0;i<now->list->size();++i){//
			vector<pair<int,int> >this_list=*(now->list);
			int other_node_num=this_list[i].first;
			Node* other_node=node_lists[other_node_num-1];
			if(other_node_num==start||other_node->marked)
				continue;
			if((now->distence+this_list[i].second)<other_node->distence){
				other_node->distence=now->distence+this_list[i].second;
				other_node->parent=now;
			}
			if(other_node->distence<=mindis){
				mindis=other_node->distence;
				min_one=other_node_num;
			}
		}
		if(min_one==0)
			break;
		Node* min=node_lists[min_one-1];
		min->marked=true;
		S.push_back(min);
		--nums;
	}
}
void find(vector<Node*>&node_lists,int end){
	cout<<"find..."<<endl;
	Node* now=node_lists[end-1];
	int dis=now->distence;
	while(now->parent!=now){
		cout<<now->serial_num<<",";
		now=now->parent;
	}
	cout<<now->serial_num<<endl;
	cout<<"distence:"<<dis<<endl;
}
int main(){
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
	dijkstra(node_lists,1);
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
