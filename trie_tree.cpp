#include <iostream>
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
int main(){
	// generate_data();
	TrieNode root;
	// build(root);
	string result_file="english_data_result";
	fstream out(result_file.c_str(),ios::in);
	string data;
	out>>data;
	while(!out.eof()){
		cout<<data<<endl;
		string::iterator ite=data.begin();
		while(ite!=data.end()){
			TrieNode parent_node=root;
			int pos=*ite-'a';
			int h=ite-data.begin();//节点的深度
			if(parent_node.childnodes[pos]==NULL){
				TrieNode* this_node=new TrieNode;
				this_node->nodechar=*ite;
				this_node->freq=1;
				parent_node.childnodes[pos]=this_node;
				parent_node=*this_node;
			}else{
				TrieNode this_node=*(parent_node.childnodes[pos]);
				this_node.freq++;
				parent_node=this_node;
			}
			parent_node.is_word=true;
			++ite;
		}
		out>>data;
	}
}
