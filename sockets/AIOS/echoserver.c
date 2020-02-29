#include"header.h"
int main(int argc, char * argv[])
{
	printf("This is an echo server dealing with client %s\n Type EXIT to exit ",argv[1]);
	int fd=open("Famousfifo",O_WRONLY);
	int pfd=open(argv[1],O_WRONLY);
	while(1)
	{
		char Temp[1024];
		strcpy(Temp,"");
		scanf("%s",Temp);
		printf("%s--\n",Temp);
		if(strcmp(Temp,"EXIT")==0)
		{
			char Str[100];
			strcpy(Str,"");
			strcat(Str,"X");
			strcat(Str,argv[1]);
			strcat(Str,"|");
			write(fd,Str,strlen(Str));
		}
		else
		write(pfd,Temp,strlen(Temp)+1);
	}
}
