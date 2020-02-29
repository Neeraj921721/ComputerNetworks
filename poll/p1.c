#include"header.h"

int main(){
	mkfifo("p1ffo",0666);
	int ffofd=open("p1ffo",O_WRONLY | O_NONBLOCK);
	while(1){
		char buffer[1024];
		printf("enter the message : ");
		scanf("%s",buffer);
		write(ffofd,buffer,strlen(buffer));
	}
return 0;
}
