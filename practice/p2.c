#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main(){
	int fd=open("sample.txt",O_WRONLY | O_APPEND | O_CREAT);
	if(fd < 0){
		printf("Couldn't create the file ... exiting \n");
		exit(1);
	}

	dup2(fd,1);	//stdout of the process becomes stdin of file
	printf("Hi there ! \n How are you ? \n");
	printf("What do you need ? \n How may I help you ? \n");
	close(fd);
return 0;
}

