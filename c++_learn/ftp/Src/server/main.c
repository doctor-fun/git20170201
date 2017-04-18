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

	int lisent_fd;
	lisent_fd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==lisent_fd)
	{	
		perror("socket");
		return -1;
	}
	set_init(lisent_fd,argv[1],argv[2]);
	listen(lisent_fd,count);//原接口listen自带服务器现可连接数管理

	fd_set fd_team;
	FD_ZERO(&fd_team);
	FD_SET(lisent_fd,&fd_team);

	int i;
	for(i=0;i<count;i++)
		FD_SET(p[i].fdw,&fd_team);//将每个进程的管道端监控起来

	int j,ret1,accept_fd;
	short flag;
	while(1)
	{
		ret1=select(13,&fd_team,NULL,NULL,NULL);//从13可见，建立的子进程数目不能太多

		if(ret1>0)
		{
				if(FD_ISSET(lisent_fd,&fd_team))
				{
					accept_fd=accept(lisent_fd,NULL,NULL);
					for(j=0;j<count;j++)
					{
						if(p[j].busy==0)
						{
							send_fd(p[j].fdw,accept_fd);
							p[j].busy=1;
							break;
						}
					}
				}
				for(j=0;j<count;j++)//轮询与子进程的全双工管道，
				{
					if(FD_ISSET(p[j].fdw,&fd_team))
					{
						read(p[j].fdw,&flag,sizeof(flag));
						p[j].busy=0;
						printf("run ok\n");
					}
				}
			}
	
		}
}
