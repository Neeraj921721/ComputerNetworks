#include"header.h"

int sfd;

void hdfn(int signo){
	close(sfd);
	signal(SIGINT,SIG_DFL);
}

int main(){
	signal(SIGINT,hdfn);
	struct sockaddr_in saddr;
	socklen_t saddrlen=sizeof(saddr);
	sfd=socket(AF_INET,SOCK_STREAM,0);
	
	int portnum;
	printf("enter port number : ");
	scanf("%d",&portnum);
	
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(portnum);
	
	if(inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr) <= 0){
		printf("Invalid Address / Address not supported ....\n");
		return -1;
	}
	
	int cret=connect(sfd,(struct sockaddr *)&saddr,saddrlen);
	if(cret == -1){
      	printf("\nConnection with Server Failed \n");
     		return -1;
    	}
    	if(cret>=0)
    	{
    		printf("CONNECTION ESTABLISHED WITH SERVER\n");
    		
    		struct sockaddr_in clientaddr,serveraddr;
		char myIP[16];
		socklen_t len=sizeof(clientaddr);
		unsigned int myport,serverport;
		int rr=getsockname(sfd,(struct sockaddr *)&clientaddr,&len);
		inet_ntop(AF_INET,&clientaddr.sin_addr,myIP,sizeof(myIP));
		myport=ntohs(clientaddr.sin_port);
		
		printf("Local ip address: %s\n", myIP);
		printf("Local port : %u\n", myport);
		
		len=sizeof(serveraddr);
		rr=getpeername(sfd,(struct sockaddr *)&serveraddr,&len);
		printf("FOREIGN IP: %s\n",inet_ntoa(serveraddr.sin_addr));
		printf("FOREIGN Port: %d\n",ntohs(serveraddr.sin_port));
		while(1)
		{
			char sbuffer[100],rbuffer[100];
			fgets(sbuffer,100,stdin);
			send(sfd,sbuffer,strlen(sbuffer)+1,0);
			recv(sfd,rbuffer,100,0);
			printf("%s",rbuffer);
		}
    	}
return 0;
}
