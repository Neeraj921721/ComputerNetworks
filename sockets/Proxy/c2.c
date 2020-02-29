#include"header.h"
#define PORT 8080

int main(){
	int sfd;
	struct sockaddr_in saddr;
	socklen_t saddrlen=sizeof(saddr);
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0){
		printf("Server Socket creation error !\n");
		return -1;
	}
	
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(PORT);
	if(inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr) <= 0){
		printf("Invalid Address / Address not supported ....\n");
		return -1;
	}

	int cret=connect(sfd,(struct sockaddr *)&saddr,saddrlen);
	if(cret < 0){
      	printf("\nConnection with Proxy server Failed \n");
     		return -1;
    	}
    	else
    	{
    		printf("Connected to Proxy...\n");
    		printf("Enter special server Port : ");
    		char ssport[5];
    		fgets(ssport,5,stdin);
    		send(sfd,ssport,strlen(ssport)+1,0);
		fd_set readfds;
		FD_ZERO(&readfds);
		struct timeval t;
		t.tv_sec=500;
		t.tv_usec=0;
		int nfds=sfd+1;
		while(1)
		{
			FD_SET(0,&readfds);
			FD_SET(sfd,&readfds);
			int selret=select(nfds,&readfds,NULL,NULL,&t);
			if(selret == 0){
				printf("Timeout...\n");
			}
			else if(selret > 0)
			{
				char buffer[100];
				if(FD_ISSET(0,&readfds))
				{
					printf("enter : ");
					fgets(buffer,100,stdin);
					send(sfd,buffer,strlen(buffer)+1,0);
					printf("to server : %s",buffer);
				}
				if(FD_ISSET(sfd,&readfds))
				{
					recv(sfd,buffer,100,0);
					printf("from server : %s",buffer);
				}
			}
		}
    	}
return 0;
}
