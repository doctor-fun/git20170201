#include "head.h"
void send_n(int fd,char * buf,int len)
{
	int total=0;
	int pos;
	while (total<len)
	{
		pos=send(fd,buf+total,len-total,0);
		total=total+pos;
	}
}
void recv_n(int fd,char *buf,int len)
{
	int total=0;
	int pos;
	while (total<len)
		{
			pos=recv(fd,buf+total,len-total,0);
			total=total+pos;	
		}
}
void send_file(char *p,int new_sfd)
{
	td t;
	memset(&t,0,sizeof(t));
	t.len=strlen(p);//指令放在火车二，指令长度放在火车1的计数中，
	strncpy(t.buf,p,t.len);//将火车二buf中指令内容放到火车一中，
	send_n(new_sfd,(char *)&t,4+t.len);//火车一对象的Int（字节）和火车二存放在火车一Buf中的内容传给sfd
	int fd;

	printf("the file is:%s\n",t.buf);

	fd=open(t.buf,O_RDONLY);//从这一语句中可以看出指令为文件名（相对路径）或者绝对路径

	if(fd==-1)
	{
		perror("open");
		return;
	}
	while(memset(&t,0,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0)
	send_n(new_sfd,(char* )&t,t.len+4);
	t.len=0;
	send_n(new_sfd,(char *)&t.len,4);

}
void recv_file (int new_sfd)
{
	char buf[1000];
	int fd;
	int len;
	memset(&buf,0,sizeof(buf));
	recv_n(new_sfd,(char *)&len,4);//先接收4个字节，将4个字节的内容附给len,
	//从len的内容可以看出来继续从sfd中接收多少字节到Buf当中；
	recv_n(new_sfd,buf,len);//再接收len个字节放到buf当中;
	
	fd=open(buf,O_WRONLY|O_CREAT);

	while(1)
	{
		memset(&buf,0,sizeof(buf));
		recv_n(new_sfd,(char*)&len,4);
		if(len>0)
		{
			recv_n(new_sfd,buf,len);
			write(fd,buf,len);

		}
			else 
				break;
	}
	printf("I have the file\n");
	close(fd);
}

