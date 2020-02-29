#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<stdbool.h>
#include<poll.h>
#include<fcntl.h>

int main(){
	int repfd=open("r1ffo",O_WRONLY);
	if(repfd < 0){
		printf("Couldn't open the fifofile to write.....\n");
		exit(1);
	}
	while(1){
		printf("Enter message : ");
		char buf[100];
		fgets(buf,100,stdin);
		printf("________________R1 writes___________________\n");
		write(repfd,buf,strlen(buf));
	}
	close(repfd);
return 0;
}
