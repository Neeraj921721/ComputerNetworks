#include "header.h"

int main(){
	//int savestdin=dup(0);	
	char msg[20];	
	read(0,msg,sizeof(msg));
	printf(" msg = %s\n",msg);
	int fd=open("abc.txt",O_WRONLY | O_APPEND | O_CREAT);	
	//dup2(fd,0);	
	char mssg[20];	
	int x=read(fd,mssg,20);
	mssg[x]='\0';		
	printf(" msg = %s\n",mssg);	
	//dup2(savestdin,0);	
return 0;
}
