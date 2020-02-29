#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	while(1)
	{
		sleep(2);
		printf(" from p2 ");
		fflush(stdout);
	}
return 0;
}
