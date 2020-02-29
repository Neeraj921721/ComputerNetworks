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
	while(1){
		char *buf=(char *)calloc(1024,sizeof(char));
		int x=read(0,buf,100);
		while(x <= 0) ;
		printf("message recieved by p4 : %s \n",buf);
	}		
return 0;
}
