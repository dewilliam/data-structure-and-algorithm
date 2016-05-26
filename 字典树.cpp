//author:谢添
//location:北京交通大学 下一代互联网与互联设备国家工程实验室
//email:mftianxie@gmail.com
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
	vector<int> word_pos;
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
	int lines=1;
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
		parent_node->word_pos.push_back(lines);
		out>>data;
		lines++;
	}
}
void find(TrieNode& root,string check){
	string::iterator ite=check.begin();
	TrieNode parent_node=root;
	while(ite!=check.end()){
		*ite=tolower(*ite);
		int pos=(*ite-'a');
		if(parent_node.childnodes[pos]==NULL){
			cout<<"times:0"<<endl;
			return;
		}
		else
			parent_node=*(parent_node.childnodes[pos]);
		++ite;
	}
	if(parent_node.is_word==false){
		cout<<"times:0"<<endl;
		return;
	}
	else{
		cout<<"times:"<<parent_node.freq<<endl;
		vector<int>::iterator lines=parent_node.word_pos.begin();
		cout<<"pos(line):";
		while(lines!=parent_node.word_pos.end()){
			cout<<*lines<<",";
			++lines;
		}
		cout<<endl;
	}
}
int main(){
	int start=clock();
	cout<<"generate_data"<<endl;
	generate_data();
	printf("time: %.6lf\n",double(clock()-start)/CLOCKS_PER_SEC);
	TrieNode root;
	start=clock();
	cout<<"build"<<endl;
	build(&root);
	printf("time: %.6lf\n",double(clock()-start)/CLOCKS_PER_SEC);//1200万个单词，大概3.5秒左右
	while(true){
		string check;
		cin>>check;
		find(root,check);
	}
}
