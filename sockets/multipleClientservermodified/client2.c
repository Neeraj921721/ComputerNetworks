#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>	
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>	

#define PORT 8080

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
	
	if((connect(sfd, (struct sockaddr *)&server_addr,server_addrlen)) < 0){
      	printf("\nConnection Failed \n");
     		return -1;
    	}

	while(1){
		printf("enter message : ");
		char buf[1024];
		fgets(buf,1024,stdin);
		send(sfd,buf,strlen(buf)+1,0);
	}
	
return 0;
}
