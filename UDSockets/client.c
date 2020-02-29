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
#define PORT 8080

int main(){
	struct sockaddr_in saddr;
	socklen_t len=sizeof(saddr);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(PORT);
	connect(sfd,(struct sockaddr*)&saddr,len);
	
	while(1)
	{
		char buffer[100];
		fgets(buffer,100,stdin);
		fflush(stdin);
		send(sfd,buffer,strlen(buffer)+1,0);
		recv(sfd,buffer,100,0);
		write(1,buffer,strlen(buffer)+1);
		fflush(stdout);
	}
}

