#include"header.h"

int main(){
	char ch[5];
	do{
		printf("Want to request a connection : ");
		scanf("%s",ch);
		if(strcmp(ch,"yes") == 0 ){
			break;
		}
		printf("waiting............\n");
	}while(1);
	
	printf("Requesting connection .......\n");
	int reqfd=open("famousffo",O_WRONLY);
	char clientpid[100];
	snprintf(clientpid,10,"%d",getpid());
	write(reqfd,pid,strlen(pid));
	char nsfd[10];
	strcpy(nsfd,clientpid);
	int x=open(nsfd,O_RDONLY | O_NONBLOCK);
	if(x<0) printf("error !\n");
	while(1){
		char msg[1024];
		strcpy(msg,"");
		int r=read(nsfd,O_RDONLY | O_NONBLOCK);
		if(r<0) continue;
		printf("%s",msg);
	}
	
return 0;
}

