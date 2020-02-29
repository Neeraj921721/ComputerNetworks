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
	int sfd;									//socket file descriptor
	struct sockaddr_in saddr;					//address structure for server where mesg should reach 
	//struct hostent *ptrh;
	int saddrlen=sizeof(saddr);
		
	sfd=socket(AF_INET,SOCK_STREAM,0);					//creating socket file descriptor
	if(sfd < 0){
		printf("________Socket creation error !_______\n");
		return -1;
	}
	//ptrh = gethostbyname("192.168.43.124");
	//memcpy(&server_addr.sin_addr,ptrh->h_addr,ptrh->h_length);
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(PORT);
	
	if(inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr) <= 0){
		printf("Invalid Address / Address not supported ....\n");
		return -1;
	}
	
	if(connect(sfd, (struct sockaddr *)&saddr,saddrlen) < 0){
      	printf("\nConnection Failed \n");
     		return -1;
    	}
	
	struct sockaddr_in getaddr;
	socklen_t len=sizeof(getaddr);
	int r=getsockname(sfd,(struct sockaddr *)&getaddr,&len);
	
	struct pollfd fds[2];
	fds[0].fd=0;
	fds[1].fd=sfd;
	fds[0].events=0;
	fds[1].events=0;
	fds[0].events |= POLLIN;
	fds[1].events |= POLLIN;
	int maxval=0;
	while(1){
		poll(fds,2,5000);
		if(fds[0].revents & POLLIN){
			char buf[1024];
			fgets(buf,1024,stdin);
			int n=strlen(buf);
			buf[n]='\0';
			send(sfd,buf,strlen(buf)+1,0);
		}
		if(fds[1].revents & POLLIN){
			char buf[1024];
			recv(sfd,buf,1024,0);
			printf("message from server : %s \n",buf);
		}
		if(maxval==5) close(sfd);
		maxval++;
	}	
return 0;
}
