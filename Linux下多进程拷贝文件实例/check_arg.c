#include"pcpy.h"
int check_arg(const char* SFile,const int arg_num,int pronum)
{
	//产源文件是否存在?*/
	if((access(SFile,F_OK))!=0){
		perror( "check Arg Error");
		exit(-1);
	}
	/*参数数量足否满*/
	if(arg_num< 3){
		printf( "Check Arg Error ;参数数量异常!");exit(-1);
	}
	/*进程数量足否溢出?*/
	if(pronum<0||pronum >=100){
		printf ("Check Arg Error :进程数量要大于0,小于100.\n");
		exit(-1);
	}
	return 0;
	}

