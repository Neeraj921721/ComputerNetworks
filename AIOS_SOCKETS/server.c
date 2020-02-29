#include"header.h"
#define PORT 8080
#define MAXCLIENTS 5

int clientID[100000]={0};
int queue[100000]={0};
int queuecnt=0;


int max(int a,int b){
	return ((a>b)?a:b);
}

void handler(int signo){
	printf("Signal recieved from p4...\n");
	int i;
	for(i=0;i<queuecnt;i++)
	{
		if(queue[i] != -1)
		{
			break;
		}
	}
	int nsfd=queue[i];
	queue[i]=-1;
	
	int clientpidfd=open("clientpidffo",O_RDONLY);
	char clientpid[50];
	int n=read(clientpidfd,clientpid,50);
	clientpid[n]='\0';
	kill(atoi(clientpid),SIGUSR1);	//enter pid of the client as argument to notify to connect to echoserver
   	system("gnome-terminal -- /bin/bash -c './echoserver';");
}

int main(){
	int serverpid=getpid();
	printf("Server starting....%d....\n",serverpid);
	int ppfd[2];
	signal(SIGINT,handler);  			//p4 sends signal
	pipe(ppfd);
	int p3fd=fileno(popen("./p3","r"));
	int p2ffofd=open("p2ffo",O_RDONLY|O_NONBLOCK);
	if(p2ffofd < 0) printf("p2ffo open error !\n");
	
	int sfd;
	struct sockaddr_in saddr;
	socklen_t saddrlen=sizeof(saddr);
	int opt=1;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd < 0){
		printf("Socket1 creation error ! \n");
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
	
	int savestdin=dup(0);
	int savestdout=dup(1);
	
	fd_set readfds;
	FD_ZERO(&readfds);
		
	int nfds=1+max(0,max(ppfd[0],max(p2ffofd,p3fd)));
	struct timeval t;
	t.tv_sec=5000;
	t.tv_usec=0;
	
	pid_t pid=fork();
	if(pid != 0)
	{
		close(ppfd[1]);
		while(1)
		{
			FD_SET(sfd,&readfds);
			FD_SET(0,&readfds);
			FD_SET(p2ffofd,&readfds);
			FD_SET(p3fd,&readfds);
			FD_SET(ppfd[0],&readfds);
			int selret=select(nfds,&readfds,NULL,NULL,&t);
			if(selret == 0){
				printf("Timeout !\n");
			}
			else if(selret > 0){
				if(FD_ISSET(ppfd[0],&readfds))
				{
					char buffer[1024];
					int n=read(ppfd[0],buffer,1024);
					buffer[n]='\0';
					printf("From sdtin : %s \n",buffer);
					for(int i=0;i<100000;i++)
					{
						if(clientID[i]==1)
						{
							send(nfds,buffer,strlen(buffer)+1,0);
						}
					}	
				}
				if(FD_ISSET(sfd,&readfds))
				{
					int nsfd=accept(sfd,(struct sockaddr *)&saddr,(socklen_t *)&saddrlen);
					if(nsfd < 0)
					{
						printf("accept error !\n");
						return -1;
					}
					printf("CONNECTION ESTABLISHED with client!....\n");
					clientID[nsfd]=1;
					queue[queuecnt++]=nsfd;
				}
				if(FD_ISSET(0,&readfds))
				{
					char buffer[1024];
					int n=read(0,buffer,1024);
					buffer[n]='\0';
					printf("From sdtin : %s \n",buffer);
					for(int i=0;i<100000;i++)
					{
						if(clientID[i]==1)
						{
							send(nfds,buffer,strlen(buffer)+1,0);
						}
					}
				}
				if(FD_ISSET(p2ffofd,&readfds))
				{
					char buffer[1024];
					int n=read(p2ffofd,buffer,1024);
					buffer[n]='\0';
					printf("From fifo : %s \n",buffer);
					for(int i=0;i<100000;i++)
					{
						if(clientID[i]==1)
						{
							send(nfds,buffer,strlen(buffer)+1,0);
						}
					}
				}
				if(FD_ISSET(p3fd,&readfds))
				{
					char buffer[1024];
					int n=read(p3fd,buffer,1024);
					buffer[n]='\0';
					printf("From popen : %s \n",buffer);
					for(int i=0;i<100000;i++)
					{
						if(clientID[i]==1)
						{
							send(nfds,buffer,strlen(buffer)+1,0);
						}
					}
				}
			}
		}
	}
	else
	{
		close(ppfd[0]);
		while(1)
       	{
       	    char msg[]="from p1 through pipe";
       	    sleep(3);
      	    write(ppfd[1],msg,strlen(msg)+1);
      	}				
	}
	close(ppfd[0]);
	close(ppfd[1]);
return 0;
}
