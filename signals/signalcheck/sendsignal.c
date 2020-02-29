#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(int argc,char *argv[]){
	char ch;
	printf("Enter :");
	scanf("%c",&ch);
	if(ch=='s')
	{
		kill(atoi(argv[1]),SIGUSR1);
		sleep(2);
	}
	printf("Enter :");
	scanf("%c",&ch);
	if(ch=='s')
	{
		kill(atoi(argv[1]),SIGUSR2);
	}
return 0;
}
