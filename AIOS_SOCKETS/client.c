#include"header.h"
#include<string.h>
#define PORT1 8080		// for server
#define PORT2 9090		//for echoserver

int sfd1,sfd2,sfd3;
struct sockaddr_in saddr1,saddr2;
socklen_t saddrlen2=sizeof(saddr2);
socklen_t saddrlen1=sizeof(saddr1);

void handler2(int signo){		//AGAIN CONNECTION TO SERVER
	close(sfd2);
	sfd1=sfd3;
	while(1)
	{
		char buf[1024];
		recv(sfd1,buf,1024,0);
		printf("message from server : %s \n",buf);
	}
}

void handler1(int signo){		//CONNECTED TO ECHOSERVER
	sfd3=sfd1;
	close(sfd1);
	sfd2=socket(AF_INET,SOCK_STREAM,0);
	/*if(sfd2<0){
		printf("Echoserver Socket creation error !\n");	
	}*/
	saddr2.sin_family=AF_INET;
	saddr2.sin_port=htons(PORT2);
	
	int bret=bind(sfd2,(struct sockaddr *)&saddr2,sizeof(saddr2));
	/*if(bret < 0){
		printf("Bind2 error !\n");
		exit(EXIT_FAILURE);
	}*/
	
	int cret=connect(sfd2,(struct sockaddr *)&saddr1,saddrlen1);
	/*if(cret < 0){
      	printf("\nConnection Failed \n");
     		return -1;
    	}*/
	
	while(1)
	{
		signal(SIGUSR2,handler2);		//echo server exits
		char buf[1024];
		recv(sfd2,buf,1024,0);
		printf("message from server : %s \n",buf);
	}
} 

int main(){
	mkfifo("clientpidffo",0660);
	int clientpidfd=open("clientpidffo",O_WRONLY);
	char clientpid[50];
	sprintf(clientpid,"%d",getpid());
	write(clientpidfd,clientpid,strlen(clientpid)+1);
	sfd1=socket(AF_INET,SOCK_STREAM,0);
	if(sfd1<0){
		printf("Server Socket creation error !\n");
		return -1;
	}
	
	saddr1.sin_family=AF_INET;
	saddr1.sin_port=htons(PORT1);
	
	int bret=bind(sfd1,(struct sockaddr *)&saddr1,sizeof(saddr1));
	if(bret < 0){
		printf("Bind with main server error !\n");
		return -1;
	}
	
	int cret=connect(sfd1,(struct sockaddr *)&saddr1,saddrlen1);
	if(cret < 0){
      	printf("\nConnection with main server Failed \n");
     		return -1;
    	}
	
	signal(SIGUSR1,handler1);		//SERVER SEND SIGUSR1 if server recieves signal from p4
	
	while(1)
	{
		char buf[1024];
		recv(sfd1,buf,1024,0);
		printf("message from server : %s \n",buf);
	}
return 0;	
}
