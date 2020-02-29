#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>

int main (){
	int pp1[2];
	int pp2[2];
	int ret1=pipe(pp1);
	if(ret1 == -1){
		printf("Couldn't open pipe1..\n");
		exit(1);	
	}	
	int ret2=pipe(pp2);
	if(ret2 == -1){
		printf("Couldn't open pipe2..\n");
		exit(1);	
	}
	pid_t pid=fork();
	if(pid != 0){
		close(pp1[0]);
		close(pp2[1]);
		printf("We are in parent process...\n");
		dup2(pp1[1],1);
		char msg[]="We are in parent process this is message for child process...";
		printf("message from parent process \n");
		wait(NULL);
		dup2(pp2[0],0);
		char mssg[10];
		scanf("%s",mssg);
		printf("Message got from child process is %s\n",mssg);		
	}else{
		close(pp1[1]);
		close(pp2[0]);
		printf("We are in child process...\n");
		
		dup2(pp2[0],0);
		char mssg[10];
		scanf("%s",mssg);
		printf("Message got from parent process is %s\n",mssg);
	
		dup2(pp2[1],1);
		printf("this is message from child process \n");
		exit(0);
	}
	
return 0;
}
