#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>


int main(){
	char ch[5];
	int savestdin=dup(0);
	int savestdout=dup(1);	
	int pp[2];
	int ret=pipe(pp);
	if(ret == -1){
		printf("Couldn't create pipe .. exiting ..\n");
		exit(1);
	}
	dup2(pp[0],0);
	dup2(pp[1],1);
	close(pp[0]);
	close(pp[1]);//?
	fflush(stdin);//
	fflush(stdout);
	int fdin=fileno(popen("./p2","r"));
	dup2(savestdin,0);
	int fdout;
	dup2(1,fdout);//wromg
	dup2(savestdout,1);
	
	do{
		char msg[100];
		printf("Enter the message : ");
		scanf("%s",msg);
		printf("message sent : (by p1) : %s\n",msg);
		
		write(fdout,msg,strlen(msg)+1);
		
		sleep(2);
		
		char mssg[100];	
		int size=read(fdin,mssg,100);
		mssg[size]='\0';
			
		printf("message recieved  : (from p2) : %s\n",mssg);
		printf("Do you want to send messages... : ");
		scanf("%s",ch);
	}while((strcmp("yes",ch)) == 0);
return 0;
}
