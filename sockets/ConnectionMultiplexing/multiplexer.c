#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>
#include <netdb.h>
#include <poll.h>
#include <sys/select.h>
#include <sys/time.h>
#define PORT 8080
#define MAXCLIENTS 3

int main(){
	int sfd1,sfd2;
	struct sockaddr_in saddr;
	socklen_t saddrlen=sizeof(saddr);
	int opt=1;
	
	sfd1=socket(AF_INET,SOCK_STREAM,0);
	if(sfd1<0){
		printf("Socket1 creation error !\n");
		return -1;	
	}
	
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=INADDR_ANY;
	saddr.sin_port=htons(PORT);

	int sockret=setsockopt(sfd1,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt));	
	if(sockret < 0){
		perror("setsockopt1"); 
      	exit(EXIT_FAILURE); 
	}
			
	int bret=bind(sfd1,(struct sockaddr *)&saddr,sizeof(saddr));
	if(bret < 0){
		printf("Bind1 error !\n");
		exit(EXIT_FAILURE);
	}

	sfd2=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd2<0){
		printf("Socket1 creation error !\n");
		return -1;	
	}
	
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=INADDR_ANY;
	saddr.sin_port=htons(PORT);
			
	bret=bind(sfd2,(struct sockaddr *)&saddr,sizeof(saddr));
	if(bret < 0){
		printf("Bind2 error !\n");
		exit(EXIT_FAILURE);
	}

	int lret=listen(sfd1,MAXCLIENTS);
	if(lret<0){
		printf("Listen1 error !............\n");
		return -1;
	}
	
	fd_set readfds;
	FD_ZERO(&readfds);
	int nfds=((sfd1>sfd2)?sfd1:sfd2)+1;
	struct timeval t;
	t.tv_sec=50;
	t.tv_usec=0;
	while(1){
		FD_SET(sfd1,&readfds);
		FD_SET(sfd2,&readfds);
		int selret=select(nfds,&readfds,NULL,NULL,&t);
		if(selret == 0){
			printf("Timeout !\n");
		}
		else if(selret > 0){
			if(FD_ISSET(sfd1,&readfds))
			{
				int nsfd=accept(sfd1,(struct sockaddr *)&saddr,(socklen_t *)&saddrlen);
				if(nsfd < 0){
					printf("accept error !\n");
					return -1;
				}
				printf("CONNECTION ESTABLISHED !....\n");
				pid_t pid=fork();
				if(pid != 0){
					close(nsfd);
				}
				else{
					close(sfd1);
					dup2(nsfd,0);
					dup2(nsfd,1);
					char *arg[]={"./ss",NULL};
					execv(arg[0],arg);
				}
			}
			if(FD_ISSET(sfd2,&readfds))
			{
				 char buffer[100];
				 int n=recvfrom(sfd2,(char *)buffer,1024,MSG_WAITALL,(struct sockaddr *)&saddr,&saddrlen);
				 printf("\nConnection from udp client\n");
				 buffer[n]='\0';
			sendto(sfd2,(char *)buffer,strlen(buffer),MSG_CONFIRM,(struct sockaddr *)&saddr,saddrlen);	
				printf("____message sent____\n");		 
			}
		}		
	}
return 0;
}
