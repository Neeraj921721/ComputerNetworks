#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int signo){
	printf("Hello Signal \n");
}

int main(){
	signal(SIGUSR1,signal_handler);
	printf("CHecking signal .... \n");
	raise(SIGUSR1);
return 0;
}

