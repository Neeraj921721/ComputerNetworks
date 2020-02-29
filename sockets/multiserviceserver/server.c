#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <poll.h>
#define PORT1 8080
#define PORT2 9090
#define MAXCLIENTS 5

int main(){
	int sfd1;
	int sfd2;
	int opt1=1;
	int opt2=1;
	struct sockaddr_in address1,address2;
	socklen_t addrlen1=sizeof(address1);
	socklen_t addrlen2=sizeof(address2);
	//socket1
	sfd1=socket(AF_INET,SOCK_STREAM,0);
	if(sfd1 < 0){
		printf("Socket1 creation error ! \n");
		return -1;
	}
	
	address1.sin_family=AF_INET;
	address1.sin_port=htons(PORT1);
	address1.sin_addr.s_addr=INADDR_ANY;
	
	int opret;
	opret=setsockopt(sfd1,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt1,sizeof(opt1));
	if(opret < 0){
		perror("setsockopt1"); 
      	exit(EXIT_FAILURE); 
	}
	
	int bret;
	bret=bind(sfd1,(struct sockaddr *)&address1,sizeof(address1));
	if(bret < 0){
		printf("\nBind1 failed........\n");
		return -1;
	}
	//socket2
	sfd2=socket(AF_INET,SOCK_STREAM,0);
	if(sfd2 < 0){
		printf("Scoket2 creation error ! \n");
		return -1;
	}
	
	address2.sin_family=AF_INET;
	address2.sin_port=htons(PORT2);
	address2.sin_addr.s_addr=INADDR_ANY;
	
	opret=setsockopt(sfd2,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt1,sizeof(opt2));
	if(opret < 0){
		perror("setsockopt2"); 
      	exit(EXIT_FAILURE); 
	}
	
	bret=bind(sfd2,(struct sockaddr *)&address2,sizeof(address2));
	if(bret < 0){
		printf("\nBind2 failed........\n");
		return -1;
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
	struct pollfd fds[2];
	fds[0].fd=sfd1;
	fds[1].fd=sfd2;
	fds[0].events=0;
	fds[1].events=0;
	fds[0].events |= POLLIN;
	fds[1].events |= POLLIN;
	
	while(1)
	{
		poll(fds,2,50000);
		if(fds[0].revents & POLLIN)
		{
			int nsfd=accept(fds[0].fd,(struct sockaddr *)&address1,(socklen_t *)&addrlen1);
	struct sockaddr_in clientaddr,serveraddr;
	char myIP[16];
	socklen_t len=sizeof(clientaddr);
	unsigned int myport,serverport;
	int rr=getsockname(sfd1,(struct sockaddr *)&clientaddr,&len);
	inet_ntop(AF_INET,&clientaddr.sin_addr,myIP,sizeof(myIP));
	myport=ntohs(clientaddr.sin_port);
	
	printf("Local ip address: %s\n", myIP);
	printf("Local port : %u\n", myport);
	
	len=sizeof(serveraddr);
	rr=getpeername(nsfd,(struct sockaddr *)&serveraddr,&len);
	printf("FOREIGN IP: %s\n",inet_ntoa(serveraddr.sin_addr));
	printf("FOREIGN Port: %d\n",ntohs(serveraddr.sin_port));
			if(nsfd < 0){	
				printf("accept1 error !");
				return -1;
			}
			printf("CONNECTION ESTABLISHED WITH PORT1...\n");
			pid_t pid=fork();
			if(pid != 0)
			{
				close(nsfd);
			}
			else
			{
				close(sfd1);
				dup2(nsfd,0);
				dup2(nsfd,1);
				char* arg[]={"./ss",NULL};
				execv(arg[0],arg);	
			}	
		}			
		if(fds[1].revents & POLLIN)			
		{
			int nsfd=accept(fds[1].fd,(struct sockaddr *)&address2,(socklen_t *)&addrlen2);
	struct sockaddr_in clientaddr,serveraddr;
	char myIP[16];
	socklen_t len=sizeof(clientaddr);
	unsigned int myport,serverport;
	int rr=getsockname(sfd2,(struct sockaddr *)&clientaddr,&len);
	inet_ntop(AF_INET,&clientaddr.sin_addr,myIP,sizeof(myIP));
	myport=ntohs(clientaddr.sin_port);
	
	printf("Local ip address: %s\n", myIP);
	printf("Local port : %u\n", myport);
	
	len=sizeof(serveraddr);
	rr=getpeername(nsfd,(struct sockaddr *)&serveraddr,&len);
	printf("FOREIGN IP: %s\n",inet_ntoa(serveraddr.sin_addr));
	printf("FOREIGN Port: %d\n",ntohs(serveraddr.sin_port));
			if(nsfd < 0){
				printf("accept2 error !");
				return -1;
			}
			printf("CONNECTION ESTABLISHED WITH PORT2...\n");
			pid_t pid=fork();
			if(pid != 0)
			{
				close(nsfd);
			}
			else
			{
				close(sfd2);
				dup2(nsfd,0);
				dup2(nsfd,1);
				char* arg[]={"./ss",NULL};
				execv(arg[0],arg);	
			}
		}			
	}
	
return 0;
}
