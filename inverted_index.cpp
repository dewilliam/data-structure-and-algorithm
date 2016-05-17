/*
//倒排索引。
// 构建了meta类型，保存每一个单词的倒排索引信息。
// vector存储所有的倒排索引。
// 又构建了字典树（trie tree） ，用来判定是否存在某单词的索引，
// 每一个TrieNode的单词终节点上存储着该单词在vector中的存储位置，这样可以直接定位到该位置操作。
// 流程：先对源文档进行处理，去掉不该有的字符。
// 然后对文档中每一个单词创建索引。
// 之后对vector进行排序。
// 最后把所有的索引输出到文件中。
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
class meta{
public:
	string word;
	int freq;
	vector<int> pos;//存储在文档中该单词的位置
	meta(string w):word(w),freq(1){}
};
class TrieNode{
public:
	char nodechar;
	int pos;//存储在lists中的位置
	bool is_word;//从根节点到该节点是否是一个完整的已存在的单词
	TrieNode* childnodes[26];
	TrieNode():nodechar(),pos(),is_word(false){
		for(int i=0;i<26;++i)
			childnodes[i]=NULL;
	}
};
void process_data(){
	cout<<"process_data"<<endl;
	string file="data/data2";
	fstream fs(file.c_str(),ios::in|ios::out);
	stringstream buffer;
	buffer<<fs.rdbuf();
	string data(buffer.str());
	for(int i=0;i<data.size();++i)
		if(data[i]=='\''&&data[i+1]=='s'){
			data[i]=' ';
			data[i+1]=' ';
		}else if(data[i]=='\''&&data[i+1]=='t'){
			data[i]=data[i+1];
			data[i+1]=' ';
		}else if(data[i]=='\''&&data[i+1]=='r'&&data[i+2]=='e'){
			data[i]=data[i+1];
			data[i+1]=data[i+2];
			data[i+2]=' ';
		}else if(data[i]<'A'||(data[i]>'Z'&&data[i]<'a')||data[i]>'z'){
			data[i]=' ';
		}
	fs.seekp(0,ios::beg);
	fs<<data;
}
void str_lower(string& data){
	for(int i=0;i<data.size();++i)
		data[i]=tolower(data[i]);
}
bool trie_find(TrieNode& root,string& check,int& vector_pos){
	string::iterator ite=check.begin();
	TrieNode parent_node=root;
	while(ite!=check.end()){
		*ite=tolower(*ite);
		int pos=(*ite-'a');
		if(parent_node.childnodes[pos]==NULL)
			return false;
		else
			parent_node=*(parent_node.childnodes[pos]);
		++ite;
	}
	if(parent_node.is_word==false)
		return false;
	else{
		vector_pos=parent_node.pos;
		return true;
	}
}
void trie_insert(TrieNode* root,string& data,int vector_pos){
	TrieNode* parent_node=root;
	string::iterator ite=data.begin();
	while(ite!=data.end()){
		*ite=tolower(*ite);
		int pos=*ite-'a';
		int h=ite-data.begin();//节点的深度
		if(parent_node->childnodes[pos]==NULL){
			TrieNode* this_node=new TrieNode;
			this_node->nodechar=*ite;
			// this_node->freq=1;
			parent_node->childnodes[pos]=this_node;
			parent_node=this_node;
		}else{
			TrieNode* this_node=parent_node->childnodes[pos];
			// this_node->freq++;
			parent_node=this_node;
		}
		ite++;
	}
	parent_node->is_word=true;
	parent_node->pos=vector_pos;
}
void build(vector<meta>& lists){
	cout<<"build"<<endl;
	string file="data/data2";
	TrieNode root;
	fstream out(file.c_str(),ios::in);
	string data;
	out>>data;
	int lines=1;
	while(!out.eof()){
		str_lower(data);//统一小写字母
		if(data=="the"||data=="then"){
			out>>data;
			++lines;
			continue;
		}
		int vector_pos;
		if(!trie_find(root,data,vector_pos)){
			meta new_meta(data);
			new_meta.pos.push_back(lines);
			lists.push_back(new_meta);
			int new_pos=lists.size()-1;
			//insert into trie tree...
			trie_insert(&root,data,new_pos);
		}else{
			lists[vector_pos].freq++;
			lists[vector_pos].pos.push_back(lines);//已经存在的word就在lists中追加位置
		}
		out>>data;
		++lines;
	}
}
void sort_list(vector<meta>&lists,int start,int end){
	if(start>=end)
		return;
	meta mark=lists[start];
	int i=start;
	int j=end;
	while(i<j){	//填坑。。。。
		while(i<j&&lists[j].word>=mark.word)
			--j;
		if(i<j)
			lists[i]=lists[j];
		while(i<j&&lists[i].word<mark.word)
			++i;
		if(i<j)
			lists[j]=lists[i];
	}
	lists[i]=mark;
	sort_list(lists,start,i-1);
	sort_list(lists,i+1,end);
}
void write_file(vector<meta>& lists){
	cout<<"write_file..."<<endl;
	vector<meta>::iterator ite=lists.begin();
	string file="data/inverted_index_result";
	fstream in(file.c_str(),ios::out|ios::app);
	while(ite!=lists.end()){
		stringstream ss;
		for(int i=0;i<(*ite).pos.size();++i){
			ss<<(*ite).pos[i];
			if(i!=(*ite).pos.size()-1)
				ss<<",";
		}
		string poses;
		ss>>poses;
		in<<(*ite).word<<" <"<<(*ite).freq<<":"<<poses<<">"<<"\n";
		++ite;
	}
}
int main(){
	int start=clock();
	process_data();
	vector<meta>lists;
	build(lists);
	int end=lists.size()-1;
	cout<<"sort..."<<endl;
	sort_list(lists,0,end);
	write_file(lists);
	printf("time: %.6lf\n",double(clock()-start)/CLOCKS_PER_SEC);
}
