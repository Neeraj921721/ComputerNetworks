#include"header.h"
int main(){
	while(1)
	{
		char buffer[]="HI from popen..";
		write(1,buffer,strlen(buffer)+1);
		sleep(4);
	}
return 0;	
}

