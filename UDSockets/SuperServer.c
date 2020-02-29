#include<stdlib.h>
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
#include<stdbool.h>
#define SOCK_PATH "skipper"
#define PORT 8080


int main(){
	struct sockaddr_in saddr;
	struct sockaddr_un usaddr;
	socklen_t saddrlen=sizeof(saddr);
	socklen_t usaddrlen=sizeof(usaddr);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	int opt=1;
	saddr.sin_port=htons(PORT);
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=INADDR_ANY;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
	
	int bret=bind(sfd,(struct sockaddr*)&saddr,saddrlen);
	if(bret<0)
		perror("bind failed\n");
	listen(sfd,5);
	
	unlink(SOCK_PATH);
	int usfd=socket(AF_UNIX,SOCK_STREAM,0);
	usaddr.sun_family=AF_UNIX;
	strcpy(usaddr.sun_path,SOCK_PATH);
	
	bret=bind(usfd,(struct sockaddr*)&usaddr,usaddrlen);
	if(bret < 0)
		perror("bind failed\n");
	listen(usfd,5);
	int nusfd;
	if((nusfd=accept(usfd,(struct sockaddr*)&usaddr,&usaddrlen))==-1)
		perror("accept error\n");
	
	while(1)
	{
		int fd=open("data.txt",O_RDWR|O_CREAT);
		int nsfd=accept(sfd,(struct sockaddr*)&saddr,&saddrlen);
		int *fdptr;
		int fds[2];
		fds[0]=nsfd;
		fds[1]=fd;
		
		printf("CONNECTION ESTABLISHED WITH CLIENT\n");
		//pass nsfd and fd to threaded service server
		
		struct msghdr msg;
		struct iovec iov[1];
		struct cmsghdr* cmsg=NULL;
		char data[1];
		char ctrl[CMSG_SPACE(sizeof(fds))];
		data[0]='#';
		iov[0].iov_base=data;
		iov[0].iov_len=sizeof(data);
		
		msg.msg_name=NULL;
		msg.msg_namelen=0;
		msg.msg_iov=iov;
		msg.msg_iovlen=1;
		msg.msg_control=ctrl;
		msg.msg_controllen=sizeof(ctrl);
		
		cmsg=CMSG_FIRSTHDR(&msg);
		cmsg->cmsg_level=SOL_SOCKET;
		cmsg->cmsg_type=SCM_RIGHTS;
		cmsg->cmsg_len=CMSG_LEN(sizeof(fds));		//size of numbers of filedesc you are sending 
		//*((int*)CMSG_DATA(cmsg))=nsfd;
		fdptr=(int*)CMSG_DATA(cmsg);
		memcpy(fdptr,fds,sizeof(fds));
		if((sendmsg(nusfd,&msg,0)==-1))
			perror("send error\n");
	}
return 0;	
}
