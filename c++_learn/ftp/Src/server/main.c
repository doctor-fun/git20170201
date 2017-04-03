#include "func.h"
int main(int argc,char * argv[])
	//Ip,port，线程数
{
	if (argc!=4)
	{
		printf("error args\n");
		return -1;
	}
	int count =atoi(argv[3]);
	pcdata p=(pcdata)calloc(count,sizeof(cdata));
	//为子进程空间申请结构体；
	make_child(p,count);
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{	
		perror("socket");
		return -1;
	}
	set_init(sfd,argv[1],argv[2]);
	listen(sfd,count);//原接口listen自带服务器现可连接数管理

	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(sfd,&fd);

	int i;
	for(i=0;i<count;i++)
		FD_SET(p[i].fdw,&fd);//将每个线程的管道

	int j,ret1,new_fd;
	short flag;
	while(1)
	{
		ret1=select(13,&fd,NULL,NULL,NULL);
		if(ret1>0)
		{
				if(FD_ISSET(sfd,&fd))
				{
					new_fd=accept(sfd,NULL,NULL);
					for(j=0;j<count;j++)
					{
						if(p[j].busy==0)
						{
							send_fd(p[j].fdw,new_fd);
							p[j].busy=1;
							break;
						}
					}
				}
				for(j=0;j<count;j++)
				{
					if(FD_ISSET(p[j].fdw,&fd))
					{
						read(p[j].fdw,&flag,sizeof(flag));
						p[j].busy=0;
						printf("run ok\n");
					}
				}
			}
	
		}
}
