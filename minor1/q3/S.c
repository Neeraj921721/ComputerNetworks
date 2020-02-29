#include"header.h"
#define PORT1 8081
#define PORT2 8082
#define PORT3 8083
#define MAXCLIENTS 5 

int sfd1,sfd2,sfd3;

void hdfn(int signo){
	close(sfd1);
	close(sfd2);
	close(sfd3);
	signal(SIGINT,SIG_DFL);
}

void handler(int signo){
	if(signo==SIGUSR1)
	{
		printf("S1\n");
	}
	if(signo==SIGUSR2)
	{
		printf("S2\n");
	}
	if(signo==SIGHUP)
	{
		printf("S3\n");
	}
}

	

int main(){
	signal(SIGUSR1,handler);
	signal(SIGUSR2,handler);
	signal(SIGHUP,handler);
	signal(SIGINT,hdfn);
	
	struct sockaddr_in saddr1,saddr2,saddr3;
	socklen_t len1=sizeof(saddr1);
	socklen_t len2=sizeof(saddr2);
	socklen_t len3=sizeof(saddr3);
	
	int opt1=1,opt2=1,opt3=1;
	
	sfd1=socket(AF_INET,SOCK_STREAM,0);
	saddr1.sin_family=AF_INET;
	saddr1.sin_port=htons(PORT1);
	saddr1.sin_addr.s_addr=INADDR_ANY;
	setsockopt(sfd1,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt1,sizeof(opt1));	
	bind(sfd1,(struct sockaddr *)&saddr1,sizeof(saddr1));
	
	sfd2=socket(AF_INET,SOCK_STREAM,0);
	saddr2.sin_family=AF_INET;
	saddr2.sin_port=htons(PORT2);
	saddr2.sin_addr.s_addr=INADDR_ANY;
	setsockopt(sfd2,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt2,sizeof(opt2));	
	bind(sfd2,(struct sockaddr *)&saddr2,sizeof(saddr2));

	sfd3=socket(AF_INET,SOCK_STREAM,0);
	saddr3.sin_family=AF_INET;
	saddr3.sin_port=htons(PORT3);
	saddr3.sin_addr.s_addr=INADDR_ANY;
	setsockopt(sfd3,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt3,sizeof(opt3));	
	bind(sfd3,(struct sockaddr *)&saddr3,sizeof(saddr3));
	
	listen(sfd1,MAXCLIENTS);
	listen(sfd2,MAXCLIENTS);
	listen(sfd3,MAXCLIENTS);
	
	
	fd_set readfds;
	FD_ZERO(&readfds);
	struct timeval t;
	t.tv_sec=50000;
	t.tv_usec=0;
	
	int flag1=0,flag2=0,flag3=0;
	
	while(1)
	{
		int nfds=-10;
		FD_ZERO(&readfds);
		if(flag1==0)
		{
			FD_SET(sfd1,&readfds);
			nfds=(nfds>sfd1)?nfds:sfd1;
		}
		if(flag2==0)
		{
			FD_SET(sfd2,&readfds);
			nfds=(nfds>sfd2)?nfds:sfd2;
		} 
		if(flag3==0)
		{
			FD_SET(sfd3,&readfds);
			nfds=(nfds>sfd3)?nfds:sfd3;
		}
		
		int sret=select(nfds+1,&readfds,NULL,NULL,&t); 
		if(sret==0)
		{
			printf("timeout\n");
		}
		else if(sret > 0)
		{
			if(flag1==0 && FD_ISSET(sfd1,&readfds))
			{
				flag1=1;
				pid_t pid=fork();
				if(pid == 0)
				{
					char sockfd[50];
					sprintf(sockfd,"%d",sfd1);
					char *arg[] = {"./S1",sockfd,NULL};					
					execv(arg[0],arg);
				}
			}
			if(flag2==0 && FD_ISSET(sfd2,&readfds))
			{
				flag2=1;
				pid_t pid=fork();
				if(pid == 0)
				{
					char sockfd[50];
					sprintf(sockfd,"%d",sfd2);
					char *arg[] = {"./S2",sockfd,NULL};					
					execv(arg[0],arg);
				}
			}
			if(flag3==0 && FD_ISSET(sfd3,&readfds))
			{
				flag3=1;
				pid_t pid=fork();
				if(pid == 0)
				{
					char sockfd[50];
					sprintf(sockfd,"%d",sfd3);
					char *arg[] = {"./S3",sockfd,NULL};					
					execv(arg[0],arg);
				}
			}
		}
	}
return 0;
}
