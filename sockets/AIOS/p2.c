#include"header.h"
int main(int argc, char * argv[])
{
	int fd=open("Process2Fifo",O_WRONLY);
	int cnt=0;
	int t=5;
	while(t--)
	{	
		for(int j=0;j<0x2fffffff;j++);
		char x[30]="Input from Process2\n";
		write(fd,x,strlen(x));
	}
	return 0;
}
