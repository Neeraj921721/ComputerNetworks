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
#define PORT 8080

int main(){
	int sfd,nsfd;					//socket file descriptor
	struct sockaddr_in address;		//address structure for server where mesg should reach 
	int opt=1;
	int addrlen=sizeof(address);
		
	sfd=socket(AF_INET,SOCK_STREAM,0);			//creating socket file descriptor
	if(sfd < 0){
		printf("_________________Socket creation error !________________\n");
		return -1;
	}
	
	// Forcefully attaching socket to the port 8080 	
	if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){ 
      	perror("setsockopt"); 
      	exit(EXIT_FAILURE); 
    	}
	address.sin_family=AF_INET;
	address.sin_port=htons(PORT);
	address.sin_addr.s_addr=INADDR_ANY;
	
	if( bind(sfd,(struct sockaddr *)&address,addrlen) < 0 ){
		printf("\nBind failed........\n");
		return -1;
	}
	
	if( listen(sfd,3) < 0 ){
		printf("Listen error !............\n");
		return -1;
	}
	
	nsfd=accept(sfd,(struct sockaddr *)&address,(socklen_t*)&addrlen);
	if(nsfd < 0){
		printf("Accept error !..........\n");
		return -1;
	}
	
	struct pollfd fds[2];
	fds[0].fd=0;
	fds[1].fd=nsfd;
	fds[0].events=0;
	fds[1].events=0;
	fds[0].events |= POLLIN;
	fds[1].events |= POLLIN;	
	
	while(1){
		poll(fds,2,5000);
		if(fds[0].revents & POLLIN){
			char buf[1024];
			fgets(buf,1024,stdin);
			send(nsfd,buf,strlen(buf)+1,0);
			printf("___________________________________message sent_________________________\n");
		}
		if(fds[1].revents & POLLIN){
			char buf[1024];
			recv(nsfd,buf,1024,0);
			printf("message from client : %s \n",buf);
		}
	}
	
	
return 0;
}
