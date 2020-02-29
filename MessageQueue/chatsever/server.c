#include"mqueue.h"

struct msgbuffer{
	long type;
	char data[100];
};
struct msgbuffer mbuff,mbuffer;

int main(){
	printf("______Server started________\n");
	key_t key;
	key=ftok("famousmsgq",65);
	
	int msgqid=msgget(key,0666|IPC_CREAT);
	while(1)
	{
		if(msgrcv(msgqid,&mbuffer,sizeof(mbuffer),5,0) !=-1)
		{
		char buffer[100];
		strcpy(buffer,mbuffer.data);
		switch(mbuff.data[0]-'0'){
			case 1:
				{	
					mbuff.type=2;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					mbuff.type=3;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					mbuff.type=4;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					break;
				}
			case 2:
				{
					mbuff.type=1;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					mbuff.type=3;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					mbuff.type=4;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					break;
				}
			case 3:
				{
					mbuff.type=1;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					mbuff.type=2;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					mbuff.type=4;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					break;
				}
			case 4:	
				{
					mbuff.type=1;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					mbuff.type=2;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					mbuff.type=3;
					strcpy(mbuff.data,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
					break;
				}
		}
		}	
	}
	printf("______________Server Down_________________\n");
return 0;
}
