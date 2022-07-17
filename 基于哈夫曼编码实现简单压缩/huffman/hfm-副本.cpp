#include<iostream>
#include<fstream>
#include<fstream>
#include <queue>
#include <sys/types.h>

#include <unistd.h>

#define ll long long
#define N  10000001
		

using namespace std;
int cnt;
struct node{
	int l,
	r,
	val;
	char ch;
}hfm[N];

char a[128],b[128],str[N];
int tohfm[512];
int len;//文件字节数
int root;
int cdl[512];
int code[1024];
bool apr[1024];

struct cmp{
	bool operator()(int a,int b){
		return hfm[a].val>hfm[b].val;
		}
	};

priority_queue<int,vector<int>,cmp> q;

void dfs(int x,int dep,int cd){
	if(!x)return;
	if(hfm[x].ch){
		int ascii=hfm[x].ch;
		cdl[ascii]=dep;
		code[ascii]=cd;
		return;
	}
	dfs(hfm[x].l,dep+1,cd<<1);
	dfs(hfm[x].r,dep+1,cd<<1|1);
}

void huffman(){
	for(int i=1;i<=cnt;i++)q.push(i);
	while(q.size()>=2){
		int a,b,c;
		a=q.top();
		q.pop();
		b=q.top();
		q.pop();
		c=++cnt;
		hfm[c].l=a;
		hfm[c].r=b;
		hfm[c].val=hfm[a].val+hfm[b].val;
		q.push(c);
	}
	if(cnt==1){
		code[(unsigned)hfm[1].ch]=2;
		cdl[(unsigned)hfm[1].ch]=1;
	}
	else dfs((root=cnt),0,1);
}

int get(int a,int b){
	return (a&(1<<(8-b)))>>(8-b);
	}
#define code(a,b) get(code[a],b)
#define Out(x,y) output.write((char*)&x,y)
int main(){
	scanf("%s%s",a,b);
	ofstream output(b,ios::out|ios::binary);
	FILE* file = fopen(a, "rb");
	fseek(file,0,SEEK_END);//将文件pos偏移到文件尾
	len=ftell(file);//求出文件首位置到尾位置的字节数
	fclose(file);//关闭文件
	ifstream input(a,ios::in|ios::binary);
	input.read((char*)&str,len);
	for(int i=0;i<len;i++){
		if(!apr[(int)str[i]])
			tohfm[(int)str[i]]=++cnt;// int tohfm
			apr[(int)str[i]]=true;//bool
			hfm[cnt].ch=str[i];
		hfm[tohfm[(int)str[i]]].val++;
	}
	//#define code(a,b) get(code[a],b)
//#define Out(x,y) output.write((char*)&x,y)
	int Len=len;
	input.close();
	int cnt1=cnt;
	huffman();
	output.write((char*)&cnt1,4);
	output.write((char*)&Len,4);
	printf("%d %d\n",cnt1,Len);
	//将编码表存到压缩文件中
	for(int i=1;i<=cnt1;i++){
		int ascii=(int)hfm[i].ch;
		output.write((char*)&hfm[i].ch,1);
		printf("%c %d ",ascii,cdl[ascii]);
		int ans=code[ascii];
		output.write((char*)&ans,1);
		for(int j=1;j<=8;j++)printf("%d",code(ascii,j));
		puts("");
	}
	int tail=0,ans=0;
	for(int i=0;i<Len;i++){
		int ascii=(int)str[i];
		//printf("%d  ",code[ascii]);
		for(int j=8-cdl[ascii]+1;j<=8;j++){
			tail++;
			ans=ans<<1|code(ascii,j);
			if(tail==8){
				for(int j=1;j<=8;j++)printf("%d",get(ans,j));
				//printf("%d  ",ans); 
				output.write((char*)&ans,1);
				tail=0,ans=0;
			}
		}
	}
	puts("");
	if(tail){
		ans<<=(8-tail);
		output.write((char*)&ans,1);
	}
	output.close();
	return 0;
}
/*
 1.txt
 2.txt
*/
