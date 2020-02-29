#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int signo){
	static int i=0;
	i++;
	if(i==10){
		printf("SIG_DFL gets executed...exiting....\n");
		signal(SIGINT,SIG_DFL);
	}
	printf("You pressed the Ctrl-C %d times \n",i);
}

int main(){
	signal(SIGINT,signal_handler);
	while(1){
		printf("\nWaiting for you to press Ctrl-C \n");
		sleep(2);
	}
return 0;
}

