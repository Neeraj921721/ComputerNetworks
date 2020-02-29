#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	while(1)
	{
		sleep(5);
		printf(" from p4 ");
		fflush(stdout);
	}
return 0;
}
