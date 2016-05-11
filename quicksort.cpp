#include <iostream>
using namespace std;

void quicksort(int* s,int start,int end){
	if(start>=end)
		return;
	int mark=s[start];
	int i=start;
	int j=end;
	while(i<j){	//填坑。。。。
		while(i<j&&s[j]>=mark)
			--j;
		if(i<j)
			s[i]=s[j];
		while(i<j&&s[i]<mark)
			++i;
		if(i<j)
			s[j]=s[i];
	}
	s[i]=mark;
	quicksort(s,start,i-1);
	quicksort(s,i+1,end);
}
int main(){
	int s[]={5,3,9,12,4,7,22,0,11,6};
	int length=sizeof(s)/sizeof(int);
	quicksort(s,0,length-1);
	for(int i=0;i<length;++i)
		cout<<s[i]<<",";
	cout<<endl;
}
