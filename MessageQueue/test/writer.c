#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>

struct msgbuffer{
	long type;
	char data[1024];
};

struct msgbuffer mbuff;

int main(){
	key_t key=ftok("progfile",65);
	int msgqid=msgget(key,0666 | IPC_CREAT);
	mbuff.type=1;
	printf("Enter the message(in writer) : ");
	char buffer[1024];
	fgets(buffer,1024,stdin);
	strcpy(mbuff.data,buffer);
	msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
	printf("Message sent : %s\n",buffer);
return 0;
}

