#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<pthread.h>
#include<string.h>

#define SOCK_PATH "skipper"

void* service_fn(void* arg)
{
	int *fdptr;
	fdptr=(int*)arg;
	int nsfd=fdptr[0];
	int fd=fdptr[1];
	write(fd,"Hello neeraj",strlen("Hello neeraj"));
	//capitalize all char
	
	while(1)
	{
		char ch[100];
		recv(nsfd,ch,100,0);
		for(int i=0;i<strlen(ch);i++)
		{
			ch[i]=toupper(ch[i]);
		}
		send(nsfd,ch,strlen(ch)+1,0);
	}
}
int main()
{
	struct sockaddr_un saddr;
	socklen_t len=sizeof(saddr);
	int usfd=socket(AF_UNIX,SOCK_STREAM,0);
	saddr.sun_family=AF_UNIX;
	strcpy(saddr.sun_path,SOCK_PATH);
	if(connect(usfd,(struct sockaddr*)&saddr,len)==-1)
	perror("connect error\n");
	int nsfds[100];
	int service=0;
	while(1)
	{
		int *fdptr;
		struct msghdr msg;
		struct iovec iov[1];
		struct cmsghdr* cmsg=NULL;
		char data[1];
		char ctrl[CMSG_SPACE(1*sizeof(int))];
		data[0]='#';
		iov[0].iov_base=data;
		iov[0].iov_len=sizeof(data);
		
		msg.msg_name=NULL;
		msg.msg_namelen=0;
		msg.msg_iov=iov;
		msg.msg_iovlen=1;
		msg.msg_control=ctrl;
		msg.msg_controllen=sizeof(ctrl);
		
		if(recvmsg(usfd,&msg,0)>=0)
		{
		int nsfd,fd;
		for(cmsg=CMSG_FIRSTHDR(&msg);cmsg!=NULL;cmsg=CMSG_NXTHDR(&msg,cmsg))
		{
			if(cmsg->cmsg_level==SOL_SOCKET&&cmsg->cmsg_type==SCM_RIGHTS)
			{
				//nsfd=*((int*)CMSG_DATA(cmsg));
				fdptr=(int*)CMSG_DATA(cmsg);
				nsfd=fdptr[0];
				fd=fdptr[1];
				break;
			}
		}
		nsfds[service++]=nsfd;
		
		int *arg;
		arg=(int*)malloc(2*sizeof(int));
		arg[0]=nsfd;
		arg[1]=fd;
		pthread_t tid;
		pthread_create(&tid,NULL,service_fn,arg);
		}
	}
}
