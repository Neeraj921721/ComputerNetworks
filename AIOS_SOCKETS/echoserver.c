#include"header.h"
#include<sys/socket.h>
#define PORT 9090

int main(int argc,char *argv[]){
	printf("This is echo server\n......enter 'exit' to exit\n");
	int sfd;
	struct sockaddr_in saddr;
	socklen_t slen=sizeof(saddr);
	int opt=1;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0){
		printf("Socket creation error !\n");
		return -1;
	}
	
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=INADDR_ANY;
	saddr.sin_port=htons(PORT);
	
	int sockret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt));	
	if(sockret < 0){
		perror("setsockopt"); 
      	exit(EXIT_FAILURE); 
	}
			
	int bret=bind(sfd,(struct sockaddr *)&saddr,sizeof(saddr));
	if(bret < 0){
		printf("Bind error !\n");
		exit(EXIT_FAILURE);
	}
	int lret;
	lret=listen(sfd,2);
	if(lret<0){
		printf("Listen error !............\n");
		return -1;
	}
	
	int nsfd=accept(sfd,(struct sockaddr *)&saddr,(socklen_t *)&slen);
	
	while(1)
	{
		char buffer[100];
		fgets(buffer,100,stdin);
		if(strcmp(buffer,"exit") == 0)
		{
			printf("client pid : ");
			char clientpid[50],serverpid[50];
			int n=read(0,clientpid,50);
			clientpid[n]='\0';
			n=read(0,serverpid,50);
			serverpid[n]='\0';
			kill(atoi(serverpid),SIGHUP);			//notify server that it is exiting
			kill(atoi(clientpid),SIGUSR2);		//enter pid of the client as argument
			signal(SIGINT,SIG_DFL);
		}
		else
		{
			send(nsfd,buffer,strlen(buffer)+1,0);
		}
	}
return 0;	
}
