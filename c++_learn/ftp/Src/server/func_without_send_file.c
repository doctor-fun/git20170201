 ///
 /// @file    func_without_sen.c
 /// @author  doctor-fun(fxf432@163.com)
 /// @date    2017-04-01 16:02:49
 #include "func.h"
void cd_c(char **path,char *name,int new_sfd)//new_sfd为accept后所产生的连接sfd；
	//路径,文件名,连接句柄
{
	DIR* dir;//dir
	char buf[200];
	char buf_set[200]={0};

	sprintf(buf,"%s%s%s",*path,"/",name);//路径拼接函数，将buf真正的路径拼接起来

	dir=opendir(buf);//打开这个路径

	if(NULL==dir)
	{	
		perror("opendir");
		sprintf(buf_set,"ERROR\n->Now PWD=%s\n",*path);//将错误消息存进buf_set里面
		send(new_sfd,buf_set,strlen(buf_set)-1,0);//向new_sfd对端的缓冲区传送错误信息
		return;
	}
	else
	{
		strcpy(*path,buf);//strcpy会将*path内容清空，将Buf的内容拷贝进*path当中
		sprintf(buf_set,"Success PWD=%s\n",*path);//拼接函数，将成功打开的信息与路径连接成字符串
		send(new_sfd,buf_set,strlen(buf_set)-1,0);//将成功打开某个地址的信息传给对端
		return;
	}
		
}
void pwd_c(int new_sfd,char * path)
{	
	char buf_set[200]={0};
	sprintf(buf_set,"%s\n",path);
	send(new_sfd,buf_set,strlen(buf_set)-1,0);
}
void remove_c(char* name,int new_sfd,char * path1)
{
	int ret;
	char buf_set[200]={0};
	char *path=calloc(1,200);//返回一个指向新开辟空间的指针
	sprintf(path,"%s/%s",path1,name);

	ret=remove(path);

	if(ret==0)
	{
		sprintf(buf_set,"Success>>%s<<\n",path);	
		send(new_sfd,buf_set,strlen(buf_set)-1,0);
	}
	else
	{
		perror("remove");
		sprintf(buf_set,"Delete Error!\n");
		send(new_sfd,buf_set,strlen(buf_set)-1,0);
	}
}
void ls_c(int new_sfd,char * path)
{
	struct stat buf;//因为stat函数第二个入口参数为一个指向stat的指正，所以要先初始化一个stat结构
	char a[10]={0};
	char b[10]={0};
	char c[10]={0};
	char d[10]={0};
	char e[10]={0};
	int f,g,h;
	char final[100]={0};
	char buf_set[1000]={0};
	DIR *dir;//目录描述符,（句柄）

	dir=opendir(path);//返回一个目录描述符

	struct dirent *p;//readdir将顺序读取dir下的文件项，返回一个指向描述该文件部分信息的一个简单结构体指针，
	while((p=readdir(dir))!=NULL)
	{
		if(strcmp(p->d_name,".")==0||strcmp(p->d_name,"..")==0)
		{}
		else
		{
			memset(&buf,0,sizeof(buf));//状态结构体清空
			int ret;
			ret=stat(p->d_name,&buf);//提取d_name文件的状态放到buf中
			if(-1==ret)
			{
				perror("stat");
				return;

			}
			sscanf(ctime(&buf.st_mtime),"%s%s%s%s%s",a,b,c,d,e);//从(ctime(&buf.st_mtime）这个当前时间字符串中按格式读取年等信息放到a,b,c,d,e
			//st_mtim文件数据的最后修改时间
			sscanf(d,"%d:%d:%d",&f,&g,&h);
			sprintf(final,"%s %s %d:%d",b,c,f,g);
			sprintf(buf_set,"%s\nsize=%d  last_modify_time:%s\n",p->d_name,buf.st_size,final);
			send(new_sfd,buf_set,strlen(buf_set),0);
			memset(buf_set,0,sizeof(buf_set));//文件信息缓冲区清空
		}
	}
}
void select_func(pfss sym,int new_sfd,char * path)
{
	switch(sym->num)
	{
		case 1:{cd_c(&path,(char*)sym->buf,new_sfd);break;}
		case 2:{ls_c(new_sfd,path);break;}
		case 3:{recv_file(new_sfd,path);break;}
		case 4:{send_file(sym->buf,new_sfd,path);break;}
		case 5:{remove_c(sym->buf,new_sfd,path);break;}
		case 6:{pwd_c(new_sfd,path);break;}
		default:{break;}

	}

}
