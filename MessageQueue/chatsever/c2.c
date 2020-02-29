#include"mqueue.h"
#include<pthread.h>
struct msgbuffer{
	long type;
	char data[100];
};
struct msgbuffer mbuff;

void *readmsg(){
	key_t key=ftok("famousmsgq",65);
	int msgqid=msgget(key,0666|IPC_CREAT);	
	while(1){
		sleep(1);
		msgrcv(msgqid,&mbuff,sizeof(mbuff),2,0);
		printf("_______message recieved : %s ______\n",mbuff.data);
	}
}

void *writemsg(){
	key_t key=ftok("famousmsgq",65);
	int msgqid=msgget(key,0666|IPC_CREAT);
	mbuff.type=5;
	while(1){
		printf("enter : ");
		char buf[100];
		fgets(buf,100,stdin);
		strcpy(mbuff.data,buf);
		msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
		printf("__________message sent : %s  ________\n",buf);
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
