#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	while(1)
	{
		sleep(3);
		printf(" from p3");
		fflush(stdout);
	}
return 0;
}
