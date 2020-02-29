#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	while(1)
	{
		char buffer[100];
		scanf("%s",buffer);
		fflush(stdin);
		printf("%s\n",buffer);
		fflush(stdout);
	}
return 0;
}
