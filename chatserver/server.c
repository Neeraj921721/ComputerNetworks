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
	int rfd;
	int wfd1,wfd2,wfd3,wfd4;
	mkfifo("famousffo",0666);
	while(1){
		char buf[100];
		rfd=open("famousffo",O_RDONLY);
		int n=read(rfd,buf,100);
		buf[n]='\0';
		close(rfd);
		switch(buf[0]){
			case '1' :
				{
					wfd2=open("c2ffo",O_WRONLY);
					wfd3=open("c3ffo",O_WRONLY);
					wfd4=open("c4ffo",O_WRONLY);
					write(wfd2,buf,strlen(buf)+1);
					write(wfd3,buf,strlen(buf)+1);
					write(wfd4,buf,strlen(buf)+1);
					close(wfd2);
					close(wfd3);
					close(wfd4);
				}
			break;
			case '2' : 
				{
					wfd1=open("c1ffo",O_WRONLY);
					wfd3=open("c3ffo",O_WRONLY);
					wfd4=open("c4ffo",O_WRONLY);
					write(wfd1,buf,strlen(buf)+1);
					write(wfd3,buf,strlen(buf)+1);
					write(wfd4,buf,strlen(buf)+1);
					close(wfd1);
					close(wfd3);
					close(wfd4);
				}
			break;
			case '3' : 
				{
					wfd1=open("c1ffo",O_WRONLY);
					wfd2=open("c2ffo",O_WRONLY);
					wfd4=open("c4ffo",O_WRONLY);
					write(wfd1,buf,strlen(buf)+1);
					write(wfd2,buf,strlen(buf)+1);
					write(wfd4,buf,strlen(buf)+1);
					close(wfd1);
					close(wfd2);
					close(wfd4);
				}
			break;
			case '4' : 
				{
					wfd1=open("c1ffo",O_WRONLY);
					wfd2=open("c2ffo",O_WRONLY);
					wfd3=open("c3ffo",O_WRONLY);
					write(wfd1,buf,strlen(buf)+1);
					write(wfd2,buf,strlen(buf)+1);
					write(wfd3,buf,strlen(buf)+1);
					close(wfd1);
					close(wfd2);
					close(wfd3);	
				}
			break;
		}
	}
return 0;
}


