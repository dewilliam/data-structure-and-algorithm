//author:谢添
//location:北京交通大学 下一代互联网与互联设备国家工程实验室
//email:mftianxie@gmail.com
#include <iostream>
using namespace std;
int main(){
	int coins[7]={1,2,5,10,20,50,100};
	int min[101];
	for(int i=0;i<=100;++i)
		min[i]=0xFFFF;//全部初始化为很大的值，这样才能处理min[last]+1<min[i]
	min[0]=0;
	for(int i=0;i<=100;++i)
		for(int j=0;j<7;++j){
			int last=i-coins[j];
			//这句是关键，很多状态转移的精华浓缩在这一句话
			//用以前的状态加一个硬币构成了当前状态。
			//然后逐渐向后走，直到找到最小的解。
			if(coins[j]<=i&&min[last]+1<min[i])
				min[i]=min[last]+1;
		}
	while(true){
		int value;
		cin>>value;
		cout<<"coins num:"<<min[value]<<endl;
	}
}
