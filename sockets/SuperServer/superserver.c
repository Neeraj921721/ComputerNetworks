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
#define PORT1 8080
#define MAXCLIENTS 3

int main(){
	int sfd1,sfd2;
	struct sockaddr_in saddr1,saddr2;
	socklen_t saddrlen1=sizeof(saddr1);
	socklen_t saddrlen2=sizeof(saddr2);
	
	int opt1=1,opt2=1;
	
	sfd1=socket(AF_INET,SOCK_STREAM,0);
	if(sfd1<0){
		printf("Socket1 creation error !\n");
		return -1;	
	}
	
	saddr1.sin_family=AF_INET;
	saddr1.sin_addr.s_addr=INADDR_ANY;
	saddr1.sin_port=htons(PORT1);

	int sockret=setsockopt(sfd1,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt1,sizeof(opt1));	
	if(sockret < 0){
		perror("setsockopt1"); 
      	exit(EXIT_FAILURE); 
	}
			
	int bret=bind(sfd1,(struct sockaddr *)&saddr1,saddrlen1);
	if(bret < 0){
		printf("Bind1 error !\n");
		exit(EXIT_FAILURE);
	}

	sfd2=socket(AF_INET,SOCK_STREAM,0);
	if(sfd2<0){
		printf("Socket1 creation error !\n");
		return -1;	
	}
	
	saddr2.sin_family=AF_INET;
	saddr2.sin_addr.s_addr=INADDR_ANY;
	saddr2.sin_port=htons(PORT2);

	sockret=setsockopt(sfd2,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt2,sizeof(opt2));	
	if(sockret < 0){
		perror("setsockopt1"); 
      	exit(EXIT_FAILURE); 
	}
			
	bret=bind(sfd2,(struct sockaddr *)&saddr2,sizeof(saddr2));
	if(bret < 0){
		printf("Bind2 error !\n");
		exit(EXIT_FAILURE);
	}

	int lret;
	lret=listen(sfd1,MAXCLIENTS);
	if(lret<0){
		printf("Listen1 error !............\n");
		return -1;
	}
	lret=listen(sfd2,MAXCLIENTS);
	if(lret<0){
		printf("Listen2 error !............\n");
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
				int nsfd=accept(sfd1,(struct sockaddr *)&saddr1,(socklen_t *)&saddrlen1);
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
				int nsfd=accept(sfd2,(struct sockaddr *)&saddr2,(socklen_t *)&saddrlen2);
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
					close(sfd2);
					dup2(nsfd,0);
					dup2(nsfd,1);
					char *arg[]={"./ss",NULL};
					execv(arg[0],arg);
				}
			}
		}		
	}
return 0;
}
