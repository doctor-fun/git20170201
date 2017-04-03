#include "func.h"
void handle_request(int fdr)//此函数用到了管道的一端，此端
	//可读可写，子进程暂时只用于从这一端进行读操作读取文件描述符，所以名字变为fdr
{
	int new_fd;
	char *path=(char *)calloc(1,200);
	strcpy(path,".");//路径控制
	fss sym;
	short flag=1;
	while(1)//永久循环
	{
		recv_fd(fdr,&new_fd);//从管道的fdr端读取主进程发过来的accept描述符放到new_fd里
		while (1)
		{
			memset(&sym,0,sizeof(fss));
			printf("new_fd=%d\n",new_fd);
			recv_n(new_fd,(char *)&sym.num,4);//从accept描述中接收4个字节内容，放到sym.num中
			recv_n(new_fd,sym.buf,sizeof(sym.buf));//从accept描述符中接收命令操作对象
			//sym对象赋值完成
			printf("%d->",sym.num);
			printf("%s\n",sym.buf);
			select_func(&sym,new_fd,path);//进行功能操作

		}
		close(new_fd);//子进程关闭accept描述符描述符（这个文件描述符在主进程仍然开着）
		write(fdr,&flag,sizeof(flag));//告诉父进程，活干完了
	}

}
void make_child(pcdata p,int count)
{
	int fds[2];//全双工管道，拥有两端，分别为fds[0],fds[1]
	int i;
	pid_t pid;
	for(i=0;i<count;i++)//产生count个线程
	{	
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//全双工管道初始化
		pid=fork();//得到子线程pid
		if(0==pid)
		{
			close(fds[1]);//关闭管道连接父进程的那一端
			handle_request(fds[0]);//管道的一端传进子进程操作函数，
		}
		p[i].pid=pid;
		p[i].fdw=fds[1];
		p[i].busy=0;
		close(fds[0]);
	}


}
