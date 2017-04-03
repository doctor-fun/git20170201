 ///
 /// @file    func_without_send.c
 /// @author  doctor-fun(fxf432@163.com)
 /// @date    2017-04-02 10:32:23
#include "head.h"
void set_init_client(int *sfd,char *ip,char *port)
{
	int ret;
	*sfd=socket(AF_INET,SOCK_STREAM,0);//将描述符进行赋值；初始化一个网络流套接字
	if(-1==*sfd)
	{
		printf("socket\n");
		return;
	}
	struct sockaddr_in p;//服务器网络地址变量
	p.sin_family=AF_INET;//服务器网络地址类型为ipv4
	p.sin_port=htons(atoi(port));//服务器网络端口
	p.sin_addr.s_addr=inet_addr(ip);//服务器网络ip
	unsigned int len=sizeof(p);

	ret=connect(*sfd,(struct sockaddr*)&p,len);

	if(ret==-1)
	{	
		perror("connect");
		close(*sfd);
		return;
	}

}
void str_to_new(Pfss sym)
{
	char buf[100]={0};
	char *p=(char *)calloc(1,100);

	read(STDIN_FILENO,buf,sizeof(buf));
	strncpy(p,buf,strlen(buf)-1);
	printf("{}{}%s\n",p);//提示输入的命令流是什么
	switch (buf[0])
	{
	case 'c':{sym->num=1;while(*(p++)!=32){}
				 strcpy(sym->buf,p);break;}
	case 'l':{sym->num=2;break;}
	case 'g':{sym->num=4;while(*(p++)!=32){}
				 strcpy(sym->buf,p);break;}
	case 'r':{
				 sym->num=5;
				 while (*(p++)!=32)
				 {
				 }
				 strcpy(sym->buf,p);//此时P指向第一个空格后面的字节序号，从而将命令和语句分开，
				 //并将后面语句的内容存到小火车的buf里面;
				 break;
			 }
	case 'p':{
				if(buf[1]=='w')
				{sym->num=6;break;}
				if(buf[1]=='u')
				{sym->num=3;while(*(p++)!=' ')
					{} strcpy(sym->buf,p);
					break;}
			 }
	default:{printf("Error\n");break;}
	}
}


