#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>

void *readmsg(){
	mkfifo("c1ffo",0666);
	while(1){
		int rfd=open("c1ffo",O_RDONLY);	
		char buf[100];
		printf(">>>>");
		int n=read(rfd,buf,100);
		buf[n]='\0';
		printf("%s\n",buf);
		close(rfd);	
	}
}

void *writemsg(){	
	while(1){
		int wfd=open("famousffo",O_WRONLY);
		char buf[100];
		printf(">>>>");	
		fgets(buf,100,stdin);
		write(wfd,buf,strlen(buf)+1);
		close(wfd);
	}
}

int main(){
	pthread_t t1,t2;
	pthread_create(&t1,NULL,&readmsg,NULL);
	pthread_create(&t2,NULL,&writemsg,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
return 0;
}

