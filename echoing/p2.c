#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>

int main(){
	char buf[100];
	int x=read(0,buf,100);
	buf[x]='\0';
	printf("%s",buf);
	write(1,buf,strlen(buf)+1);
return 0;
}
