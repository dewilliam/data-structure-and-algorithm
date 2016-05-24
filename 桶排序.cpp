//实现了最简单的桶排序算法
//author:william xie
//time:16年5月12
#include <iostream>
using namespace std;

void bucketsort(int* s,int length){
	int max=s[0];
	//find the maxmum value.....
	for(int i=0;i<length;++i)
		if(s[i]>max)
			max=s[i];
	//sort.....
	int* buckets=new int[max+1];
	for(int i=0;i<length;++i)
		buckets[s[i]]++;
	int j=0;
	//copy back....
	for(int i=0;i<max+1;++i)
		if(buckets[i]>0)
			for(int z=0;z<buckets[i];++z)
				s[j++]=i;
}
int main(){
	int s[]={5,3,9,12,4,7,22,0,11,6};
	int length=sizeof(s)/sizeof(int);
	bucketsort(s,length);
	for(int i=0;i<length;++i)
		cout<<s[i]<<",";
	cout<<endl;
}
