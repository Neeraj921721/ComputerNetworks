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
	msgrcv(msgqid,&mbuff,sizeof(mbuff),1,0);	//id,struct mbuff,&struct mbuff,sizeof mbuff,type,flag
	printf("message recieved : %s\n",mbuff.data);
return 0;
}

