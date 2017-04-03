#include "func.h"
void send_file(char *p,int new_sfd,char * path)//P=sym->buf
{	
	td t;//小火车
	char buf_set[200]={0};
	memset(&t,0,sizeof(t));

	t.len=strlen(p);//sym->buf的大小buf数组大小

	strncpy(t.buf,p,t.len);//将头车厢p的有意义的内容(共t.len个字节)存放到小火车t.buf里面去

	send_n(new_sfd,(char *)&t,4+t.len);
	int fd;

	printf("the file is:%s\n",t.buf);//此时t.buf存储了文件名
	sprintf(buf_set,"%s/%s",path,t.buf);//此时buf_set存储了整个完整路径
	
	fd=open(buf_set,O_RDONLY);
	if(fd==-1)
	{
		perror("open");
		return;
	}
	while (memset(&t,0,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0)
		//首先将t清空，然后不断从这一文件中读取buf规模那么大的空间放到buf里面，有可能读取的内容小于buf的大小，以t.len为准
		send_n(new_sfd,(char *)&t,t.len+4);//将整个t结构体的内容发给对端sfd，包括t.len
	t.len=0;
	send_n(new_sfd,(char *)&t,t.len+4);

}

	
void recv_file(int new_sfd,char * path)
{
	char buf[1000];
	int fd;
	int len;
	char buf_set[200]={0};
	
	memset(&buf,0,sizeof(buf));
	recv_n(new_sfd,(char*)&len,4);//从accept_sfd里面接收4个字节的内容放到len里面
	recv_n(new_sfd,buf,len);
	
	sprintf(buf_set,"%s/%s",path,buf);

	fd=open(buf_set,O_WRONLY|O_CREAT);

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




