#include"header.h"

int main(){
	mkfifo("p2ffo",0660);
	int p2ffofd=open("p2ffo",O_WRONLY);
	while(1)	
	{
		printf("Enter : ");
		char buffer[50];
		fgets(buffer,50,stdin);
		if(write(p2ffofd,buffer,strlen(buffer)+1) < 0){
			printf("write error !\n");
			exit(-1);
		}
		printf("\nmessage sent\n");
	}
	close(p2ffofd);
return 0;
}
