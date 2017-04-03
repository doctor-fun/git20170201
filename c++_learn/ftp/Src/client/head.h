 ///
 /// @file    head.h
 /// @author  doctor-fun(fxf432@163.com)
 /// @date    2017-04-01 22:38:19
 ///
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
struct mark{
	int pid;
	int busy;
	int fd;
};
typedef struct tdata{
	int len;
	char buf[1000];
}td,*ptd;
typedef struct first_send_sym
{
	int num;
	char buf[100];
}fss,*Pfss;
void init_net(int*,char *,char*);
void send_file(char *,int);
void recv_file(int);
void send_n(int fd,char *buf,int len);
void recv_n(int fd,char *buf,int len);
void str_to_new(Pfss sys);
void set_init_client(int *,char * ,char *);

void cd_c(char ** path,char * name,int new_sfd);
void pwd_c(int new_sfd,char *path);
void remove_c(char *name,int new_sfd,char *path1);
void ls_c(int new_sfd,char *path);
void select_func(Pfss sym,int new_sfd,char *path);

