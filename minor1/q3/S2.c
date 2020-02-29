#include"header.h"
#define PORT2 8082
#define MAXCLIENTS 5

int nsfds[MAXCLIENTS];
int noofclients=0;
int sfd;

void hdfn(int signo){
	close(sfd);
	for(int i=0;i<noofclients;i++)
	{
		close(nsfds[i]);
	}
	signal(SIGINT,SIG_DFL);
}

int main(int argc,char *argv[]){
	signal(SIGINT,hdfn);
	struct sockaddr_in saddr;
	socklen_t len=sizeof(saddr);
	
	sfd=atoi(argv[1]);	
	fd_set rfds;
	FD_ZERO(&rfds);
	struct timeval t;
	t.tv_sec=50000;
	t.tv_usec=0;
	
	int flag=0;
	while(1)
	{
		int nsfd=-1;
		if(flag==0)
		{
			fcntl(sfd,F_SETFL,fcntl(sfd,F_GETFL,0)|O_NONBLOCK);
			nsfd=accept(sfd,(struct sockaddr *)&saddr,(socklen_t *)&len);
			if(nsfd>=0)
			{
				printf("CONNECTED TO THE NEW CLIENT....\n");
				struct sockaddr_in clientaddr,myaddr;
				char myIP[16];
				socklen_t len=sizeof(myaddr);
				unsigned int myport,clientport;
				int rr=getsockname(sfd,(struct sockaddr *)&myaddr,&len);
				inet_ntop(AF_INET,&myaddr.sin_addr,myIP,sizeof(myIP));
				myport=ntohs(myaddr.sin_port);
	
				printf("Serevr ip  : %s\n", myIP);
				printf("Server port : %u\n", myport);
	
				len=sizeof(clientaddr);
				rr=getpeername(nsfd,(struct sockaddr *)&clientaddr,&len);
				printf("Client IP: %s\n",inet_ntoa(clientaddr.sin_addr));
				printf("Client Port: %d\n",ntohs(clientaddr.sin_port));
				
				nsfds[noofclients]=nsfd;
				noofclients++;
			}
			if(noofclients == MAXCLIENTS)
			{
				flag=1;
				kill(getppid(),SIGUSR2);
			}
		}
		
		int nfd=-10;
		for(int i=0;i<noofclients;i++)
		{
			nfd=(nfd>nsfds[i])?nfd:nsfds[i];
			FD_SET(nsfds[i],&rfds);	
		}
		int srt=select(nfd+1,&rfds,NULL,NULL,&t);
		if(srt==0)
		{
			printf("Timeout\n");
		}
		else if(srt>0)
		{
			for(int i=0;i<noofclients;i++)
			{
				if(FD_ISSET(nsfds[i],&rfds))
				{
					char buffer[100];
					recv(nsfds[i],buffer,100,0);
					strcat(buffer," from server 2 ");
					send(nsfds[i],buffer,strlen(buffer)+1,0);
				}
			}
		}
	}
return 0;
}
