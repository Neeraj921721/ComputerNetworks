#include"header.h"

int clientwaitqueue[100000]={-1};
int visited[100000]={0};
int cnt=0;
void handler(int signo){
   printf("Signal recieved by server....\n");
   int i;
   for( i=0;i<100000;i++)
   {
       if(clientwaitqueue[i] != -1)
       break;
   }
   int pid=queue[i];
   queue[i]=-1;
   vis[pid]=-1;
   char p[100];
   sprintf(p,"%d",pid);
   char statement[72]="";
   strcat(statement,"gnome-terminal -- /bin/bash -c './es ");
   strcat(statement,p);
   strcat(statement,"'");
   system(statement);
}


int main(){
	printf("Server starting...serverpid=%d\n",getpid());
	int savestdin=dup(0);
	int savestdout=dup(1);
	int ppfd[2];
	int ret=pipe(ppfd);
	if(ret == -1){
		printf("Couldn't create pipe......exiting\n");
		exit(1);
	}
	int ffofd=open("p2ffo",O_RDONLY | O_NONBLOCK);
	int p3popenfd=fileno(popen("./p3","r"));
	signal(SIGUSR1,handler);
	int p5popenfd=fileno(popen("./p5","w"));
	
	mkfifo("famousffo",0666);
	int famousffofd=open("famousffo",O_RDONLY | O_NONBLOCK);
	
	struct pollfd fds[5];
	fds[0].fd=0;
	fds[1].fd=pp[0];
	fds[0].events=0;
	fds[1].events=0;
	fds[2].events=0;
	fds[3].events=0;
	fds[4].events=0;
	fds[0].events |= POLLIN;
	fds[1].events |= POLLIN;
	fds[2].events |= POLLIN;
	fds[3].events |= POLLIN;
	fds[4].events |= POLLIN;
	
	int timeout=10000;
	pid_t pid=fork();
	if(pid != 0){
		close(pp[1]);
		int ffd=open("ffo",O_RDONLY | O_NONBLOCK);
		fds[2].fd=ffd;

		
		fds[3].fd=fd;
		int readreqfd=open("famousffo",O_RDONLY | O_NONBLOCK);
		fds[4].fd=readreqfd;
		
		
		
		
	
	
	}else{
		sleep(2);
		close(pp[0]);
		while(1){
			char *msg="message from p1\n";
			write(pp[1],msg,sizeof(msg)); 
			sleep(3);			
		}	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
return 0;
}
