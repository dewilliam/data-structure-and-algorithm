//author:谢添
//location:北京交通大学 下一代互联网与互联设备国家工程实验室
//email:mftianxie@gmail.com
#include <iostream>
#include <stdlib.h>
#define N 10
#define M 50
using namespace std;
int main(){
	int apples[N][M];
	int max[N][M]={0};
	for(int i=0;i<N;++i){
		for(int j=0;j<M;++j){
			int apple=rand()%10;
			apples[i][j]=apple;
			cout<<apple<<",";
		}
		cout<<endl;
	}
	for(int i=0;i<N;++i){
		for(int j=0;j<M;++j){//主要是边界的特殊处理，也很简单。。。
			int A=apples[i][j];
			if(!(i|j))
				max[i][j]=A;
			else if(i==0)
				max[i][j]=max[i][j-1]+A;
			else if(j==0)
				max[i][j]=max[i-1][j]+A;
			else
				max[i][j]=A+((max[i-1][j]>max[i][j-1])?max[i-1][j]:max[i][j-1]);
		}
	}
	while(true){
		int i,j;
		cin>>i>>j;
		cout<<"max:"<<max[i][j]<<endl;
	}
}
