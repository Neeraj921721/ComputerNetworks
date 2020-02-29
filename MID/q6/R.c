#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdbool.h>
#include <sys/select.h>
#include <sys/time.h>
#include<fcntl.h>
#define PORT 8080

int main(){
	struct sockaddr_in saddr1,saddr2;
	socklen_t len1=sizeof(saddr1);
	socklen_t len2=sizeof(saddr2);
	int opt=1;
	
	int nsfd[2];
	int sfd[2];
	sfd[0]=socket(AF_INET,SOCK_STREAM,0);
	saddr1.sin_family=AF_INET;
	saddr1.sin_addr.s_addr=INADDR_ANY;
	saddr1.sin_port=htons(PORT);
	int sret=setsockopt(sfd[0],SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
	int bret=bind(sfd[0],(struct sockaddr *)&saddr1,len1);
	
	sfd[1]=socket(AF_INET,SOCK_STREAM,0);
	saddr2.sin_family=AF_INET;
	saddr2.sin_addr.s_addr=INADDR_ANY;
	saddr2.sin_port=htons(PORT);
	sret=setsockopt(sfd[1],SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
	bret=bind(sfd[1],(struct sockaddr *)&saddr2,len2);
	listen(sfd[0],100);
	listen(sfd[1],100);
	
	while(1)
	{
		//printf("hi\n");
		nsfd[0]=accept(sfd[0],(struct sockaddr *)&saddr1,(socklen_t *)&len1);
		if(nsfd[0] < 0){
			printf("accept error !\n");
			return -1;
		}
		printf("CONNECTION EASTABLISHED WITH CLIENT1\n");
		
		nsfd[1]=accept(sfd[1],(struct sockaddr *)&saddr2,(socklen_t *)&len2);
		if(nsfd[0] < 0){
			printf("accept error !\n");
			return -1;
		}
		printf("CONNECTION EASTABLISHED WITH CLIENT2\n");
		
		//char faltu[10];
		//recv(nsfd[0],faltu,10,0);
		//recv(nsfd[1],faltu,10,0);
		
		char buffer[1024];
		int fd1=open("sourcecode1.txt",O_RDONLY);
		if(fd1 == -1){
			printf("File not found\n");
			exit(EXIT_FAILURE);
		}
		read(fd1,buffer,1024);
		send(nsfd[0],buffer,strlen(buffer)+1,0);
		close(fd1);
		int fd2=open("sourcecode2.txt",O_RDONLY);
		if(fd2 == -1){
			printf("File not found\n");
			exit(EXIT_FAILURE);
		}
		read(fd2,buffer,1024);
		send(nsfd[1],buffer,strlen(buffer)+1,0);
		close(fd2);
		
		pid_t pid = fork();
		if(pid != 0)
		{
			dup2(nsfd[0],0);
			dup2(nsfd[1],1);
			close(nsfd[0]);
			close(nsfd[1]);
		}
		else
		{
			close(sfd[0]);
			close(sfd[1]);
			char *argv[2];
			argv[0]="./scenario";
			argv[1]="NULL";
			execv(argv[0],argv);
		}
		*/
	}
return 0;
}
