#include "head.h"
int main(int argc,char *argv[])
	{
		if(3!=argc)
		{
			printf("error input\n");
			return -1;
		}

		int ret;
		int sfd;
		set_init_client(&sfd,argv[1],argv[2]);//将服务器的Ip和端口绑定到sfd
		fss sym;
		fd_set fd;//定义一个描述符集合,用于select轮询
		while(1)
		{	

			FD_ZERO(&fd);//清空描述符集合的数据
			FD_SET(STDIN_FILENO,&fd);//将客户端进程的标准输入描述符放进fd
			FD_SET(sfd,&fd);//将sfd描述符放进fd里面
			ret=select(13,&fd,NULL,NULL,NULL);//13为随便给一个最大下标，表示监听0到13范围内所有描述符，以实际为准
			//成功返回监听描述符的下标，超时返回0，出错返回-1;
			char buf[700]={0};
			memset(&sym,0,sizeof(sym));//对sym->num（键值）和sym->buf（操作对象）进行赋值；
			if(ret>0)
			{
				if(FD_ISSET(STDIN_FILENO,&fd))//假如&fd集合中的STDIN_FILENO,可读
				{
					str_to_new(&sym);//从用户标准输入中获得命令流，然后对sym->num（键值）和sym->buf（操作对象）进行赋值；
					send_n(sfd,(char *)&sym,sizeof(sym));//将键值和操作对象(不包括cd类指令)发给对端；
					if(sym.num==3)
					{
						send_file(sym.buf,sfd);//当sym->num为3时，表明需要将相应文件发给服务器；
						printf("I send the file\n");
					}
					if(sym.num==4)//当Num为4时，此时服务器会完成收指令，识别指令，并往sfd客户端里方向传送相应文件的操作
					{
						//此时sfd管道可读，进行文件收入
						recv_file(sfd);
						printf("I get the file\n");
					}
					printf("send successfull\n");
					system("clear");
				}
				if(FD_ISSET(sfd,&fd))
				{
					memset(buf,0,sizeof(buf));
					ret=recv(sfd,buf,sizeof(buf),0);
					if(ret==0)
					{
						printf("This is end\n");break;
					}
					printf("%s",buf);

				}
				

			}


		}
}
