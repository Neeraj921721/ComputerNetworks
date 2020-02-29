#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>

void handler1(int signo){
	while(1){
		printf("Hello 2\n");
		sleep(5);
	}
}

void handler2(int signo){
	while(1)
	{
		printf("heloo 3\n");
		sleep(4);
	}
}

int main(){
	signal(SIGUSR1,handler1);
	signal(SIGUSR2,handler2);
	printf("PID : %d",getpid());
	while(1)
	{
		
		printf("Hello 1\n");
		sleep(6);
	}
	
	
return 0;
}
