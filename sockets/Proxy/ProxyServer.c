#include"header.h"
#include<pthread.h>
#define PORT 8080
#define MAXCLIENTS 3
#define p1 8001
#define p2 8002
#define p3 8003
#define p4 8004
#define p5 8005

int specialsfd[5];
int nsfds[2];

struct X{
	int nsfdid; 
	int portnum;
};

struct X x[2];
int xcnt=0;

int max(int a,int b){
	if(a>b) return a;
	else return b;
}

void* connecttoss1(void *arg){				//Special server 1 handle
	struct sockaddr_in serveraddr;
	socklen_t slen=sizeof(serveraddr);
	
	specialsfd[0]=socket(AF_INET,SOCK_STREAM,0);
	if(specialsfd[0] < 0){
		printf("Special server1 socket error !\n");
		exit(EXIT_FAILURE);
	}
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(p1);
	if(inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr) <= 0){
		printf("Invalid Address / Address not supported ....\n");
		exit(EXIT_FAILURE);
	}
	
	int cret=connect(specialsfd[0],(struct sockaddr *)&serveraddr,slen);
	if(cret < 0){
		printf("Couldn't connect to special server 1\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Proxy server Connected to special server 1....\n");
		
		fd_set readfds;
		FD_ZERO(&readfds);
		struct timeval t;
		t.tv_sec=5000;
		t.tv_usec=0;
		
		while(1)
		{
			int nfds=-1;
			FD_SET(specialsfd[0],&readfds);
			nfds=max(specialsfd[0],nfds);
			for(int i=0;i<2;i++)
			{
				nfds=max(nfds,nsfds[i]);
				if(x[i].portnum == p1)
				{
					FD_SET(nsfds[i],&readfds);
						
				}
			}
			nfds += 1;
			int selret=select(nfds,&readfds,NULL,NULL,&t);
			if(selret == 0){
				printf("Timeout !....\n");
			}
			else if(selret > 0)
			{
				if(FD_ISSET(specialsfd[0],&readfds))
				{
					char buffer[100];
					recv(specialsfd[0],buffer,100,0);
					for(int i=0;i<2;i++)
					{
						if(x[i].portnum == p1)
						{
							send(nsfds[i],buffer,strlen(buffer)+1,0);	
						}
					}
				}
				for(int i=0;i<2;i++)
				{
					if(x[i].portnum == p1)
					{
						if(FD_ISSET(nsfds[i],&readfds))
						{
							char buffer[100];
							recv(nsfds[i],buffer,100,0);
							printf("%s",buffer);
							send(specialsfd[0],buffer,strlen(buffer)+1,0);
						}
					}		
				}
			}
		}
	}
}


void* connecttoss2(void *arg){		//Special server2 handle
	struct sockaddr_in serveraddr;
	socklen_t slen=sizeof(serveraddr);
	
	specialsfd[1]=socket(AF_INET,SOCK_STREAM,0);
	if(specialsfd[1] < 0){
		printf("Special server2 socket error !\n");
		exit(EXIT_FAILURE);
	}
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(p2);
	if(inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr) <= 0){
		printf("Invalid Address / Address not supported ....\n");
		exit(EXIT_FAILURE);
	}
	
	int cret=connect(specialsfd[1],(struct sockaddr *)&serveraddr,slen);
	if(cret < 0){
		printf("Couldn't connect to special server 2\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Proxy server Connected to special server 2....\n");
		
		fd_set readfds;
		FD_ZERO(&readfds);
		struct timeval t;
		t.tv_sec=5000;
		t.tv_usec=0;
		
		while(1)
		{
			int nfds=-1;
			FD_SET(specialsfd[1],&readfds);
			nfds=max(specialsfd[1],nfds);
			for(int i=0;i<2;i++)
			{
				if(x[i].portnum == p2)
				{
					FD_SET(nsfds[i],&readfds);
						
				}
				nfds=max(nfds,nsfds[i]);
			}
			nfds += 1;
			int selret=select(nfds,&readfds,NULL,NULL,&t);
			if(selret == 0){
				printf("Timeout !....\n");
			}
			else if(selret > 0)
			{
				if(FD_ISSET(specialsfd[1],&readfds))
				{
					char buffer[100];
					recv(specialsfd[1],buffer,100,0);
					printf("%s\n",buffer);
					for(int i=0;i<2;i++)
					{
						if(x[i].portnum == p2)
						{
							send(nsfds[i],buffer,strlen(buffer)+1,0);	
						}
					}
				}
				for(int i=0;i<2;i++)
				{
					if(x[i].portnum == p2)
					{
						if(FD_ISSET(nsfds[i],&readfds))
						{
							char buffer[100];
							recv(nsfds[i],buffer,100,0);
							send(specialsfd[1],buffer,strlen(buffer)+1,0);
						}
					}		
				}
			}
		}
	}
}

void* connecttoss3(void *arg){			//Special server3 handle
	struct sockaddr_in serveraddr;
	socklen_t slen=sizeof(serveraddr);
	
	specialsfd[2]=socket(AF_INET,SOCK_STREAM,0);
	if(specialsfd[2] < 0){
		printf("Special server3 socket error !\n");
		exit(EXIT_FAILURE);
	}
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(p3);
	if(inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr) <= 0){
		printf("Invalid Address / Address not supported ....\n");
		exit(EXIT_FAILURE);
	}

	int cret=connect(specialsfd[2],(struct sockaddr *)&serveraddr,slen);
	if(cret < 0){
		printf("Couldn't connect to special server 3\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Proxy server Connected to special server 3....\n");
		
		fd_set readfds;
		FD_ZERO(&readfds);
		struct timeval t;
		t.tv_sec=5000;
		t.tv_usec=0;
		
		while(1)
		{
			int nfds=-1;
			FD_SET(specialsfd[2],&readfds);
			nfds=max(specialsfd[2],nfds);
			for(int i=0;i<2;i++)
			{
				if(x[i].portnum == p3)
				{
					FD_SET(nsfds[i],&readfds);	
				}
				nfds=max(nfds,nsfds[i]);
			}
			nfds += 1;
			int selret=select(nfds,&readfds,NULL,NULL,&t);
			if(selret == 0){
				printf("Timeout !....\n");
			}
			else if(selret > 0)
			{
				if(FD_ISSET(specialsfd[2],&readfds))
				{
					char buffer[100];
					recv(specialsfd[2],buffer,100,0);
					for(int i=0;i<2;i++)
					{
						if(x[i].portnum == p3)
						{
							send(nsfds[i],buffer,strlen(buffer)+1,0);	
						}
					}
				}
				for(int i=0;i<2;i++)
				{
					if(x[i].portnum == p3)
					{
						if(FD_ISSET(nsfds[i],&readfds))
						{
							char buffer[100];
							recv(nsfds[i],buffer,100,0);
							send(specialsfd[2],buffer,strlen(buffer)+1,0);
						}
					}		
				}
			}
		}
	}
	
}

void* connecttoss4(void *arg){			//Special server4 handle
	struct sockaddr_in serveraddr;
	socklen_t slen=sizeof(serveraddr);
	
	specialsfd[3]=socket(AF_INET,SOCK_STREAM,0);
	if(specialsfd[3] < 0){
		printf("Special server4 socket error !\n");
		exit(EXIT_FAILURE);
	}
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(p4);
	if(inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr) <= 0){
		printf("Invalid Address / Address not supported ....\n");
		exit(EXIT_FAILURE);
	}

	int cret=connect(specialsfd[3],(struct sockaddr *)&serveraddr,slen);
	if(cret < 0){
		printf("Couldn't connect to special server 4\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Proxy server Connected to special server 4....\n");
		
		fd_set readfds;
		FD_ZERO(&readfds);
		struct timeval t;
		t.tv_sec=5000;
		t.tv_usec=0;
		
		while(1)
		{
			int nfds=-1;
			FD_SET(specialsfd[3],&readfds);
			nfds=max(specialsfd[3],nfds);
			for(int i=0;i<2;i++)
			{
				if(x[i].portnum == p4)
				{
					FD_SET(nsfds[i],&readfds);	
				}
				nfds=max(nfds,nsfds[i]);
			}
			nfds += 1;
			int selret=select(nfds,&readfds,NULL,NULL,&t);
			if(selret == 0){
				printf("Timeout !....\n");
			}
			else if(selret > 0)
			{
				if(FD_ISSET(specialsfd[3],&readfds))
				{
					char buffer[100];
					recv(specialsfd[3],buffer,100,0);
					for(int i=0;i<2;i++)
					{
						if(x[i].portnum == p4)
						{
							send(nsfds[i],buffer,strlen(buffer)+1,0);	
						}
					}
				}
				for(int i=0;i<2;i++)
				{
					if(x[i].portnum == p4)
					{
						if(FD_ISSET(nsfds[i],&readfds))
						{
							char buffer[100];
							recv(nsfds[i],buffer,100,0);
							send(specialsfd[3],buffer,strlen(buffer)+1,0);
						}
					}		
				}
			}
		}
	}
	
}

void* connecttoss5(void *arg){				//Special Server 5 handle
	struct sockaddr_in serveraddr;
	socklen_t slen=sizeof(serveraddr);
	
	specialsfd[4]=socket(AF_INET,SOCK_STREAM,0);
	if(specialsfd[4] < 0){
		printf("Special server 5 socket error !\n");
		exit(EXIT_FAILURE);
	}
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(p5);
	if(inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr) <= 0){
		printf("Invalid Address / Address not supported ....\n");
		exit(EXIT_FAILURE);
	}
	
	int cret=connect(specialsfd[4],(struct sockaddr *)&serveraddr,slen);
	if(cret < 0){
		printf("Couldn't connect to special server 5\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Proxy server Connected to special server 5....\n");
		
		fd_set readfds;
		FD_ZERO(&readfds);
		struct timeval t;
		t.tv_sec=5000;
		t.tv_usec=0;
		
		while(1)
		{
			int nfds=-1;
			FD_SET(specialsfd[4],&readfds);
			nfds=max(specialsfd[4],nfds);
			for(int i=0;i<2;i++)
			{
				if(x[i].portnum == p5)
				{
					FD_SET(nsfds[i],&readfds);	
				}
				nfds=max(nfds,nsfds[i]);
			}
			nfds += 1;
			int selret=select(nfds,&readfds,NULL,NULL,&t);
			if(selret == 0){
				printf("Timeout !....\n");
			}
			else if(selret > 0)
			{
				if(FD_ISSET(specialsfd[4],&readfds))
				{
					char buffer[100];
					recv(specialsfd[4],buffer,100,0);
					for(int i=0;i<2;i++)
					{
						if(x[i].portnum == p5)
						{
							send(nsfds[i],buffer,strlen(buffer)+1,0);	
						}
					}
				}
				for(int i=0;i<2;i++)
				{
					if(x[i].portnum == p5)
					{
						if(FD_ISSET(nsfds[i],&readfds))
						{
							char buffer[100];
							recv(nsfds[i],buffer,100,0);
							send(specialsfd[4],buffer,strlen(buffer)+1,0);
						}
					}		
				}
			}
		}
	}
}

/*main function*/

int main(){
	pthread_t tid[5];
	pthread_create(&tid[0],NULL,connecttoss1,NULL);
	pthread_create(&tid[1],NULL,connecttoss2,NULL);
	pthread_create(&tid[2],NULL,connecttoss3,NULL);
	pthread_create(&tid[3],NULL,connecttoss4,NULL);
	pthread_create(&tid[4],NULL,connecttoss5,NULL);
	sleep(10);
	
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
	bret=bind(sfd,(struct sockaddr *)&saddr,len);
	if(bret < 0){
		printf("\nBind failed........\n");
		exit(EXIT_FAILURE);
	}
	int lret;
	lret=listen(sfd,MAXCLIENTS);
	if(lret<0){
		printf("Listen error !............\n");
		exit(EXIT_FAILURE);
	}
	
	while(1)
	{
		//fcntl(sfd,F_SETFL,fcntl(sfd,F_GETFL,0)|O_NONBLOCK);
		int nsfd=accept(sfd,(struct sockaddr *)&saddr,(socklen_t *)&len);
		char portnum[5];
		if(nsfd>=0)
		{
			printf("CONNECTION ESTABLISHED with client!....\n");
			nsfds[xcnt]=nsfd;
			recv(nsfd,portnum,5,0);
			printf("%s\n",portnum);			//to be removed
			x[xcnt].nsfdid=nsfd;
			x[xcnt].portnum=atoi(portnum);
			xcnt++;		
		}
	}
	for(int i=0;i<5;i++)
		pthread_join(tid[i],NULL);
return 0;
}
