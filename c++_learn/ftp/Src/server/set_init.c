 ///
 /// @file    set_init.c
 /// @author  doctor-fun(fxf432@163.com)
 /// @date    2017-04-02 19:12:56
 ///
#include "func.h"
void set_init(int sfd,char* ip,char* port)
{
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(port));
	ser.sin_addr.s_addr=inet_addr(ip);
	int ret;
	ret=bind(sfd,(struct sockaddr *)&ser,sizeof(ser));
	if(-1==ret)
	{	
		perror("bind");
		return;
	}

}
