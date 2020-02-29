#include"header.h"
int main()
{
	sleep(1);
	char Buff[1024]="";
	printf("This is client\n");
	int fd=open("Famousfifo",O_WRONLY);
	if(fd<0)
	perror("File open error\n");
	int pid=getpid();
	char temp[10];
	strcpy(temp,"");
	snprintf(temp,10,"%d",pid);
	strcat(Buff,"#");
	strcat(Buff,temp);
	strcat(Buff,"|");
	printf("%s\n",Buff);
	int p=write(fd,Buff,strlen(Buff));
	if(p<0)
	perror("Write error\n");
	sleep(2);
	int f=open(temp,O_RDONLY|O_NONBLOCK);
	if(f<0)
	perror("Clientfifo open error\n");
	while(1)
	{
		char Buffer[1024];
		strcpy(Buffer,"");
		int r=read(f,Buffer,1024);
		if(r<=0) continue;
		else printf("%s\n",Buffer);
	}
	return 0;
	
}
