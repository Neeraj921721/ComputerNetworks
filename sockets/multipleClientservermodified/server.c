#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>
#include <netdb.h>
#define PORT 8080

int main(){
	int sfd=0,nsfd;					//socket file descriptor
	struct sockaddr_in address;		//address structure for server where mesg should reach 
	int opt=1;
	int addrlen=sizeof(address);
		
	sfd=socket(AF_INET,SOCK_STREAM,0);			//creating socket file descriptor
	if(sfd < 0)
	{
		printf("Socket creation error !\n");
		return -1;
	}
	
	// Forcefully attaching socket to the port 8080 	
	if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
	{
      	perror("setsockopt"); 
      	exit(EXIT_FAILURE); 
    	}
	address.sin_family=AF_INET;
	address.sin_port=htons(PORT);
	address.sin_addr.s_addr=INADDR_ANY;
	
	if( bind(sfd,(struct sockaddr *)&address,addrlen) < 0 )
	{
		printf("\nBind failed........\n");
		return -1;
	}
	
	if( listen(sfd,3) < 0 )
	{
		printf("Listen error !............\n");
		return -1;
	}
	
	struct pollfd fds[100];	
	int noofclients=0;
	
	while(1)
	{
		fcntl(sfd,F_SETFL,fcntl(sfd,F_GETFL,0)| O_NONBLOCK);
		nsfd=accept(sfd,(struct sockaddr *)&address,(socklen_t*)&addrlen);
		
		if(nsfd >= 0)
		{
			printf("\n______Connected to the new client______\n");
			fds[noofclients].fd=nsfd;
			fds[noofclients].events=0;
			fds[noofclients].events |= POLLIN;
			noofclients++;	
		}
		int ret=poll(fds,noofclients,50000);
		for(int i=0;i<noofclients;i++)
		{
			if(fds[i].revents & POLLIN)
			{
				char buf[100];
				ssize_t s=recv(fds[i].fd,buf,100,0);
				buf[s]='\0';
				printf("\nmessage from client%d : %s\n",i+1,buf);
				break;
			}
		}
	}
return 0;
}
