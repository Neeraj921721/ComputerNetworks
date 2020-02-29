#include"header.h"

#define key 1234

struct smph{
  int sigpid;
};

struct smph* shm;

int main(){
   int shmid;
   shmid=shmget(key,sizeof(struct smph),IPC_CREAT|0666);
   shm=(struct smph*)shmat(shmid,NULL,0);
   while(1){
       printf("Want to send signal : \n");
       char ch;
       scanf("%c",&ch);
       if(ch=='y') kill(shm->sigpid,SIGUSR1);
   }
}
