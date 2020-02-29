#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<stdbool.h>
#include<unistd.h>
#include<poll.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(){
	mkfifo("r2ffo",0666);
	mkfifo("getpid",0666);
	int reportfd=open("r1ffo",O_WRONLY);
	int telecastpid=open("getpid",O_RDONLY);
	while(1){
		printf("Enter message : ");
		char buf[100];
		fgets(buf,100,stdin);
		char ch[1];
		printf("Want to start Live Telecast......? : ");
		fgets(ch,1,stdin);
		if(ch[0]=='y'){
			char temp[10];
			int x=read(telecastpid,temp,10);
			temp[x]='\0';
			strcat(temp," ");
			strcat(temp,buf);
			write(reportfd,temp,strlen(temp));
			printf("Live Telecast requested......\n");
		}
		else{
			write(reportfd,buf,strlen(buf));
		}
	}
return 0;
}
