#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<poll.h>
#include<fcntl.h>
#include<sys/stat.h>

struct msgbuffer{
	long type;
	char txt[100];
};

int main(){
	mkfifo("r1ffo",0666);
	int r1fd,r2fd,r3fd;
	r1fd=open("r1ffo",O_RDONLY);	
	r2fd=open("r2ffo",O_RDONLY);
	r3fd=open("r3ffo",O_RDONLY);
	
	struct pollfd fds[3];
	fds[0].fd=r1fd;
	fds[1].fd=r2fd;
	fds[2].fd=r3fd;
	fds[0].events=0;
	fds[1].events=0;
	fds[2].events=0;
	
	fds[0].events |= POLLIN;
	fds[1].events |= POLLIN;
	fds[2].events |= POLLIN;
	
	key_t key=ftok("writetoreader",65);
	int msgqid=msgget(key,0666 | IPC_CREAT);
	
	while(1){
		int pret=poll(fds,3,5000);
		if(pret > 0){
			char buffer[100];
			struct msgbuffer mbuff;
			if(fds[0].revents & POLLIN){
				int x=read(r1fd,buffer,100);
				buffer[x]='\0';
				if(buffer[0]=='/' && buffer[1]=='d'){
					mbuff.type=2;
					strcpy(mbuff.txt,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
   					system("gnome-terminal --working-directory=/home/neeraj/Desktop/CN/NIT_NEWS --c './D'");
				}
				else{
					mbuff.type=1;
					strcpy(mbuff.txt,buffer);
					msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
				}
			}
			if(fds[1].revents & POLLIN){
				int x=read(r2fd,buffer,100);
				buffer[x]='\0';
				mbuff.type=1;
				strcpy(mbuff.txt,buffer);
				msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
			}
			if(fds[2].revents & POLLIN){
				int x=read(r3fd,buffer,100);
				buffer[x]='\0';
				mbuff.type=1;
				strcpy(mbuff.txt,buffer);
				msgsnd(msgqid,&mbuff,sizeof(mbuff),0);
			}
		}			
	}
	close(r1fd);
	close(r2fd);
	close(r3fd);
return 0;
}
