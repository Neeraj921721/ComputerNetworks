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

struct msgbuffer{
	long type;
	char txt[100];
};

int main(){
	struct msgbuffer mbuff;
	int wfd=open("documentfile.txt",O_WRONLY | O_CREAT);
	key_t key=ftok("writetoreader",0);
	int msgqid=msgget(key,0666 | IPC_CREAT);
	msgrcv(msgqid,&mbuff,sizeof(mbuff),2,0);
	write(wfd,mbuff.txt,strlen(mbuff.txt));
return 0;
}
