 ///
 /// @file    func.h
 /// @author  doctor-fun(fxf432@163.com)
 /// @date    2017-04-01 15:47:30
 ///
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
typedef struct childdata{//子线程
	pid_t pid;
	int fdw;
	short busy;
}cdata,*pcdata;
typedef struct tdata{//除头车厢以外的其他车厢
	int len;//头车厢内容大小
	char buf[1000];
}td,*ptd;
typedef struct first_send_sym//
{
	int num;
	char buf[100];
}fss,*pfss;
void make_child(pcdata,int);
void set_init(int,char*,char*);
void send_fd(int fdw,int fd);
void recv_fd(int fdr,int* fd);

void sent_file(char *P,int new_fd,char *path);
void recv_file(int new_sfd,char *path);
void set_int(int sfd,char* ip,char* port);
void sned_n(int fd,char * buf,int len);
void recv_n(int fd,char * buf,int len);
	
void cd_c(char **path,char * name,int new_sfd);
void pwd_c(int new_sfd,char * path);
void remove_c(char *name,int new_sfd,char * path1);
void ls_c(int new_sfd,char * path);
void select_func(pfss sym,int new_sfd,char * path);


