#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>

#define PORT 8080

int main(){
	int sfd;
	char buffer[1024];
	char msg[1024];
	struct sockaddr_in saddr,caddr;
	socklen_t saddrlen=sizeof(saddr);
	socklen_t caddrlen=sizeof(caddr);
	
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd<0){
		printf("Socket creation Failed !\n");
		return -1;
	}
	//setting saddr and caddr all fields to 0
	memset(&saddr,0,saddrlen);
	memset(&caddr,0,caddrlen);
	// setting local ip and local port
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=INADDR_ANY;	
	saddr.sin_port=htons(PORT);
	
	int bret=bind(sfd,(struct sockaddr *)&saddr,saddrlen);
	if(bret<0){
		printf("Socket bind failed !\n");
		exit(EXIT_FAILURE);
	}

	struct pollfd fds[2];
	fds[0].fd=0;
	fds[1].fd=sfd;
	fds[0].events=0;
	fds[1].events=0;
	fds[0].events |= POLLIN;
	fds[1].events |= POLLIN;
	while(1){
		poll(fds,2,50000);
		if(fds[0].revents & POLLIN){
			
			fgets(msg,1024,stdin);
			sendto(sfd,(char *)msg,strlen(msg),MSG_CONFIRM,(struct sockaddr *)&caddr,caddrlen);
			printf("__________message sent____________\n");	
		}
		if(fds[1].revents & POLLIN){\
			int n=recvfrom(sfd,(char *)buffer,1024,MSG_WAITALL,(struct sockaddr *)&caddr,(socklen_t *)&caddrlen);
			buffer[n]='\0';
			printf("message from client : %s\n",buffer);
		}
	}
return 0;
}
