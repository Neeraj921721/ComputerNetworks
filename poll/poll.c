#include"header.h"
int main(){
	struct pollfd fds[3];
	int savestdin=dup(0);
	int savestdout=dup(1);
	
	int p1ffofd=open("p1ffo",O_RDONLY | O_NONBLOCK);
	int p2popenfd=fileno(popen("./p2","r"));
	
	fds[0].fd=0;
	fds[1].fd=p1ffofd;
	fds[2].fd=p2popenfd;	
	
	fds[0].events=POLLIN;
	fds[1].events=POLLIN;
	fds[2].events=POLLIN;	
	
	dup2(savestdin,0);
	dup2(savestdout,1);
	int timeout=4000;
	while(1){				
		int tout=poll(fds,3,-1);
		if(tout==0){
			printf("timeout...\n");
		}
		fflush(stdin);
		fflush(stdout);	
		if(fds[0].revents & POLLIN){
			char buffer1[1024];
			int x=read(savestdin,buffer1,1024);
			if(x < 0){
				printf("read error from keyboard..stdin closed !!\n");
			}
			printf("(from keyboard)[%s]\n",buffer1);
		}
		if(fds[1].revents & POLLIN){
			char buffer2[1024];
			int x=read(p1ffofd,buffer2,1024);
			if(x < 0){
				printf("read error from fifo..fifo doesn't have any data !!\n");
			}
			printf("(from p1)[%s]\n",buffer2);
		}
		if(fds[2].revents & POLLIN){
			char buffer3[1024];
			int x=read(p2popenfd,buffer3,1024);
			if(x < 0){
				printf("read error from fifo..fifo doesn't have any data !!\n");
			}
			printf("(from p2)[%s]\n",buffer3);
		}
	}
	close(p1ffofd);
	close(p2popenfd);
return 0;
}
