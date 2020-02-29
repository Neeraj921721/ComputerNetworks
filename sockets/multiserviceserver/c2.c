#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>	
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>	

#define PORT 9090

int main(){
	int sfd;									//socket file descriptor
	struct sockaddr_in server_addr;					//address structure for server where mesg should reach 
	int server_addrlen=sizeof(server_addr);
		
	sfd=socket(AF_INET,SOCK_STREAM,0);					//creating socket file descriptor
	if(sfd < 0){
		printf("_________________Socket creation error !________________\n");
		return -1;
	}
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	
	if(inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr) <= 0){
		printf("Invalid Address / Address not supported ....\n");
		return -1;
	}
	
	if(connect(sfd, (struct sockaddr *)&server_addr,server_addrlen) < 0){
      	printf("\nConnection Failed \n");
     		return -1;
    	}
	
	struct pollfd fds[2];
	fds[0].fd=0;
	fds[1].fd=sfd;
	fds[0].events=0;
	fds[1].events=0;
	fds[0].events |= POLLIN;
	fds[1].events |= POLLIN;
	
	while(1){
		poll(fds,2,5000);
		if(fds[0].revents & POLLIN){
			char buf[1024];
			printf("c2 : ");
			fgets(buf,1024,stdin);
			send(sfd,buf,strlen(buf)+1,0);
		}
		if(fds[1].revents & POLLIN){
			char buf[1024];
			recv(sfd,buf,1024,0);
			printf("message from server : %s \n",buf);
		}
	}
	
	
return 0;
}
