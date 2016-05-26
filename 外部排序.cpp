//实现了大数据的外部排序
//用到了归并排序，最小堆，选择置换方式
//选择置换：生成临时排序文件
//最小堆：用来把临时文件归并成一个整体排序文件
//注意磁盘io的效率，这是该算法的主要时间消耗
//空间消耗很少
//author:谢添
//location:北京交通大学 下一代互联网与互联工程国家工程实验室
//email:mftianxie@gmail.com
//time:16年5 月13
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#define TOTAL_SIZE 100000000
#define STACK_SIZE 1000000
#define M_FILE "data"
using namespace std;
fstream read_stream(M_FILE);
//用栈来做缓冲区
template <class type>
class stack{
private:
	int size;
	int top;//栈顶位置，初始化应为0
	type* container;
	bool is_empty(){
		return (top==0);
	}
	bool is_full(){
		return (top==size);
	}
public:
	stack(int n):size(n),top(0){
		container=new type[n];
	}
	void intsert(type data){
		if(is_full())
			return;
		container[top++]=data;
	}
	bool pop(type& data){
		if(is_empty())
			return false;
		data=container[--top];
		return true;
	}
};
stack<int> read_stack(STACK_SIZE);

class item{
public:
	int key;
	int value;
	item& operator=(item& it){
		key=it.key;
		value=it.value;
	}
};
void generate_data(){
	int a;
	// string file="data";
	fstream fs(M_FILE,ios::app|ios::out);
	//产生一亿条随机数据。。。
	for(int i=0;i<100;++i){
		stringstream ss;
		for(int j=0;j<STACK_SIZE;++j){
			a=rand();
			ss<<a<<"\n";
		}
		fs<<ss.str()<<endl;
	}
}
//读取数据，利用缓冲区
//缓冲区的内存占用：Int型4个Bytes，一百万个数据缓冲，则共用4M内存
int read_data(){
	int data;
	if(read_stack.pop(data)){
		return data;
	}else{
		int new_data;
		//方式有待改进，感觉和每次磁盘IO一个数据效果一样..........
		for(int i=0;i<STACK_SIZE;++i){
			read_stream>>new_data;
			read_stack.intsert(new_data);
		}
		read_stack.pop(data);
		return data;
	}
}
void percolete_down(int* s,int i,int size){
	if(size==1)
		return;
	int mark=s[i];
	int left=i<<1;
	int right=left+1;
	int min;
	if (left<size&&right<size){
		/* code */
		//比较大小
		min=(s[left]<s[right])?left:right;
		if(s[min]<mark){
			s[i]=s[min];
			s[min]=mark;
			percolete_down(s,min,size);
		}
	}else if(left<size&&right>=size){
		min=left;
		if(s[min]<mark){
			s[i]=s[min];
			s[min]=mark;
			// percolete_down(s,min,size);
		}
	}else{
		return;
	}
}
void pdown_item(vector<item>&s,int i,int size){
	if(size==1)
		return;
	item mark=s[i];
	int left=i<<1;
	int right=left+1;
	int min;
	if(left<size&&right<size){
		min=(s[left].value<s[right].value)?left:right;
		if(s[min].value<mark.value){
			s[i]=s[min];
			s[min]=mark;
			pdown_item(s,min,size);
		}
	}else if(left<size&&right>=size){
		min=left;
		if(s[min].value<mark.value){
			s[i]=s[min];
			s[min]=mark;
		}
	}else{
		return;
	}
}
void percolete_up(int* s,int i){
	if((i>>1)<1)
		return;
	int mark=s[i];
	int parent=i>>1;
	if(s[parent]<=s[i])
		return;
	else{
		s[i]=s[parent];
		s[parent]=mark;
		percolete_up(s,parent);
	}
}
void pup_item(vector<item>&s,int i){
	if((i>>1)<1)
		return;
	item mark=s[i];
	int parent=i>>1;
	if(s[parent].value<=s[i].value)
		return;
	else{
		s[i]=s[parent];
		s[parent]=mark;
		pup_item(s,parent);
	}
}
int slice_data(){
	//用选择置换的方法生成若干个小的临时排序文件
	/*
	//也可以用快速排序来处理，
	//方式不一样，快速排序为一 次读取N个数据，排序之后输出到一个临时文件，
	//这样快排方式，临时文件的个数是确定的 。
	//而选择置换的方式中，临时文件个数不确定
	*/
	//维护一个小顶堆
	//小顶堆也是用掉4M内存
	//也就是说，在slice_data阶段，内存共占用8M
	//time: 62.077秒................................
	//读取磁盘数据时维护一个缓存区
	int size=STACK_SIZE;
	int current_size=size-1;
	int* heap=new int[size];
	for(int i=1;i<size;++i)
		heap[i]=read_data();
	//下滤方法构造小顶堆
	for(int i=current_size>>1;i>0;--i){
		percolete_down(heap,i,current_size);
	}
	int file_num=0;//生成的临时文件的序号
	stringstream cache;
	for(int i=0;i<TOTAL_SIZE;++i){
		//提取出最小的元素（栈顶元素）
		//向磁盘输出数据时也可以加入缓冲，减少IO次数
		// new_file<<heap[1]<<endl;
		cache<<heap[1]<<"\n";
		heap[1]=heap[current_size];
		// current_size--;//堆大小先减一
		percolete_down(heap,1,current_size-1);//最后一个元素空缺了。。。
		//.....
		// int new_data;
		// read_stream>>new_data;
		//....
		int new_data=read_data();
		//如果新数据比堆顶数据还小，就先存到数组最后，它与堆中的数据不存在一个临时文件中(比较重要，大小关系不能搞错)
		if(new_data<heap[1]){
			heap[current_size--]=new_data;
		}
		else{
			heap[current_size]=new_data;
			percolete_up(heap,current_size);
		}
		//堆空间用完后，重新生成堆
		if(current_size==0){
			//临时文件名
			string file_name;
			stringstream ss;
			ss<<"file_"<<file_num;
			ss>>file_name;
			fstream new_file(file_name.c_str(),ios::app|ios::out);
			new_file<<cache.str();
			cache.str("");//清空stringstream
			file_num++;
			current_size=size-1;
			for(int i=current_size>>1;i>0;--i)
				percolete_down(heap,i,current_size);
		}
	}
	delete heap;
	return file_num;
}
void mergesort(int num){
	//把slice_data阶段生成的若干临时排序文件归并排序， 输出到一个文件中
	/*
	//用胜者树或者小顶堆，各有利弊。
	//胜者树的空间要比小 顶堆的空间大一倍，但是元素比较次数要少
	//胜者树只跟胜者比较，小顶堆要把儿子节点元素都要比较
	*/
	//heap...
	//time: 44.969 s
	vector<ifstream*> fps;//保存每个临时文件的指针
	for(int i=0;i<num;++i){
		string file_name;
		stringstream ss;
		ss<<"file_"<<i;
		ss>>file_name;
		ifstream* fs=new ifstream(file_name.c_str());
		fps.push_back(fs);
	}
	// int* external=new int[num+1];//保存真实数据
	vector<item> external;
	item it;
	external.push_back(it);
	for(int i=1;i<num+1;++i){
		item it;
		*fps[i-1]>>it.value;
		it.key=i;
		external.push_back(it);
	}
	for(int i=num>>1;i>0;--i)
		pdown_item(external,i,num);
	string output="output_data";
	fstream opf(output.c_str(),ios::app|ios::out);//输出的文件（汇总以后的）
	int size_of_file=num;
	while(size_of_file){
		//归并的重点
		opf<<external[1].value<<"\n";
		int change=external[1].key;
		external[1]=external[num];
		pdown_item(external,1,num-1);
		int new_data;//预读取
		*fps[change-1]>>new_data;
		//判断某一文件读取完毕，并处理这一情况
		if(fps[change-1]->eof()){//此时new_data中没有读到文件
			--num;
			--size_of_file;
		}else{
			external[num].value=new_data;
			external[num].key=change;
			pup_item(external,num);
		}
	}
}
int main(){
	//共用时间：time: 109.303秒
	cout<<"start..."<<endl;
	int start=clock();
	int num=slice_data();
	cout<<"mergesort...."<<endl;
	mergesort(num);
	//删除临时文件
	for(int i=0;i<num;++i){
		string file_name;
		stringstream ss;
		ss<<"file_"<<i;
		ss>>file_name;
		remove(file_name.c_str());
	}
	cout<<"end..."<<endl;
	printf("time: %.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
}
