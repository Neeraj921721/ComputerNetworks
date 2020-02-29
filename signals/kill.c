#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int signo){
	if(signo == SIGUSR1)
		printf("Message from parent...\n");
	else if(signo == SIGUSR2)
		printf("Message from child...\n");
}

int main(){
	pid_t pid=fork();
	if(pid != 0 ){
		signal(SIGUSR2,handler);
		kill(pid,SIGUSR1);
		raise(SIGUSR2);
		wait(NULL);
	}
	else{
		signal(SIGUSR1,handler);
		kill(getppid(),SIGUSR2);
		raise(SIGUSR1);
		exit(0);
	}
return 0;
}

