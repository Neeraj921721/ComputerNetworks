#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<poll.h>

int main(){
	int stdi=dup(0);
	int stdo=dup(1);
	int p2fd=fileno(popen("./p2","r"));
	int p3fd=fileno(popen("./p3","r"));
	int p4fd=fileno(popen("./p4","r"));
	int p5fd=fileno(popen("./p5","w"));
	dup2(stdi,0);
	dup2(stdo,1);
	struct pollfd fds[3];
	fds[0].fd=p2fd;
	fds[1].fd=p3fd;
	fds[2].fd=p4fd;
	
	fds[0].events=0;
	fds[1].events=0;
	fds[2].events=0;
	
	fds[0].events |= POLLIN;
	fds[1].events |= POLLIN;
	fds[2].events |= POLLIN;
	dup2(p5fd,1);
	while(1)
	{
		poll(fds,3,50000);
		if(fds[0].revents & POLLIN)
		{
			dup2(p2fd,0);
			char buffer[100];
			scanf("%s",buffer);
			fflush(stdin);
			printf("%s\n",buffer);
			fflush(stdout);
		}
		if(fds[1].revents & POLLIN)
		{
			dup2(p3fd,0);
			char buffer[100];
			scanf("%s",buffer);
			fflush(stdin);
			printf("%s\n",buffer);
			fflush(stdout);
		}
		if(fds[2].revents & POLLIN)
		{
			dup2(p4fd,0);
			char buffer[100];
			scanf("%s",buffer);
			fflush(stdin);
			printf("%s\n",buffer);
			fflush(stdout);
		}
	}	
return 0;
}
