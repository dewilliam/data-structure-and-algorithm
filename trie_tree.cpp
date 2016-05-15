#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class TrieNode{
public:
	char nodechar;
	int freq;
	bool is_word;//从根节点到该节点是否是一个完整的已存在的单词
	TrieNode* childnodes[26];
	TrieNode():nodechar(),freq(0),is_word(false){
		for(int i=0;i<26;++i)
			childnodes[i]=NULL;
	}
};
void generate_data(){
	string file="english_data";
	string result_file="english_data_result";
	string data;
	fstream out(file.c_str(),ios::in);
	fstream in(result_file.c_str(),ios::app|ios::out);
	out>>data;
	while(!out.eof()){
		in<<data<<endl;
		out>>data;
	}
}
void build(TrieNode* root){
	string result_file="english_data_result";
	fstream out(result_file.c_str(),ios::in);
	string data;
	out>>data;
	while(!out.eof()){
		string::iterator ite=data.begin();
		TrieNode* parent_node=root;
		while(ite!=data.end()){
			*ite=tolower(*ite);
			int pos=*ite-'a';
			int h=ite-data.begin();//节点的深度
			if(parent_node->childnodes[pos]==NULL){
				TrieNode* this_node=new TrieNode;
				this_node->nodechar=*ite;
				this_node->freq=1;
				parent_node->childnodes[pos]=this_node;
				parent_node=this_node;
			}else{
				TrieNode* this_node=parent_node->childnodes[pos];
				this_node->freq++;
				parent_node=this_node;
			}
			ite++;
			if(ite==data.end())
				break;
		}
		parent_node->is_word=true;
		out>>data;
	}
}
int find(TrieNode& root,string check){
	string::iterator ite=check.begin();
	TrieNode parent_node=root;
	while(ite!=check.end()){
		*ite=tolower(*ite);
		int pos=(*ite-'a');
		if(parent_node.childnodes[pos]==NULL){
			cout<<"middle"<<endl;
			return 0;
		}
		else
			parent_node=*(parent_node.childnodes[pos]);
		++ite;
	}
	if(parent_node.is_word==false){
		cout<<"last"<<endl;
		return 0;
	}
	else
		return parent_node.freq;
}
int main(){
	generate_data();
	TrieNode root;
	build(&root);
	while(true){
		string check;
		cin>>check;
		int times=find(root,check);
		cout<<"times:"<<times<<endl;
	}
}
