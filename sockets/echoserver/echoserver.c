#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

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
	
	printf("\n__________Server Ready__________\n");
	while(1){
		char buf[1024];
		recv(nsfd,buf,1024,0);
		send(nsfd,buf,1024,0);
	}
return 0;
}
