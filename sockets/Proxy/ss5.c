#include"header.h"
#define PORT 8005
#define MAXCLIENTS 2

int main(){
	int sfd;
	struct sockaddr_in saddr;
	socklen_t len=sizeof(saddr);
	int opt=1;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd < 0){
		printf("Socket creation error ! \n");
		return -1;
	}
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(PORT);
	saddr.sin_addr.s_addr=INADDR_ANY;
	int opret;
	opret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt));
	if(opret < 0){
		perror("setsockopt"); 
      	exit(EXIT_FAILURE); 
	}
	int bret;
	bret=bind(sfd,(struct sockaddr *)&saddr,sizeof(saddr));
	if(bret < 0){
		printf("\nBind failed........\n");
		return -1;
	}
	int lret;
	lret=listen(sfd,MAXCLIENTS);
	if(lret<0){
		printf("Listen error !............\n");
		return -1;
	}
	
	int nsfd=accept(sfd,(struct sockaddr *)&saddr,(socklen_t *)&len);
	if(nsfd < 0){
		printf("Could't connect to the ProxyServer\n");
		exit(EXIT_FAILURE);
	}
	else 
	{
		printf("CONNECTION ESTABLISHED WITH PROXY SERVER....\n");
		while(1)
		{
			char buffer[100];
			recv(nsfd,buffer,100,0);
			strcat(buffer,"from special server 1");
			send(nsfd,buffer,strlen(buffer)+1,0);
		}
	}
return 0;
}
