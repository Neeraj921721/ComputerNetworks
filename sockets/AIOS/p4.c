#include"header.h"
int main(int argc, char * argv[])
{
	printf("This is kill server from Process 4 please enter K \n");
	while(1)	
	{
		char  ip;
		scanf("%c",&ip);
		if(ip=='K')
		{
			kill(atoi(argv[1]),SIGUSR1);
			sleep(1);	
		}
	}
	return 0;
}
