#include<bits/stdc++.h>
#include<fstream>
#define ll long long
#define N 10000001
#define In(x,y) input.read((char*)&x,y)
#define Out(x,y) output.write((char*)&x,y)
using namespace std;
char a[128],b[128],hfm[(1<<16)-1];
int n,len;
int get(int a,int b){return (a&(1<<(8-b)))>>(8-b);}
int main(){
	scanf("%s%s",a,b);
	ifstream input(a,ios::in|ios::binary);
	ofstream output(b,ios::out|ios::binary);
	In(n,4),In(len,4);
	printf("N=%d Len=%d\n",n,len);
	for(int i=1;i<=n;i++){
		char ch;
		int code=0;
		In(ch,1),In(code,1);
		printf("%c : %d\n",ch,(int)code);
		hfm[(int)code]=ch;
	}
	int byte;
	int val=1;
	while(len){
		byte=0;
		In(byte,1);
		for(int i=1;i<=8;i++){
			val=val<<1|get(byte,i);
			printf("val=%d",val);
			if(hfm[val]){
				len--;
				Out(hfm[val],1);
				printf("%c",hfm[val]);
				val=1;
			}
			if(!len)break;
		}
	}
	return 0;
}
