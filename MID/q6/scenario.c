#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdbool.h>
#include <sys/select.h>
#include <sys/time.h>

int main(){
	char input[10];
	char output[10];
	char buf[2];
	while(1)
	{	
		read(0,input,10);			//read input from c1 
		write(1,input,strlen(input)+1);	//send input to c2
		read(1,output,10);			//read output from c2 
		write(0,output,strlen(output)+1);	//send output to c1
		read(0,buf,2);				//read confirmation from c1
		write(1,buf,strlen(buf)+1);		//send confirmation to c2
		if(buf=="1")
		{
			read(1,input,10);				//read input from c2 
			write(0,input,strlen(input)+1);	//send input to c1
			read(0,output,10);			//read output from c1 
			write(1,output,strlen(output)+1);	//send output to c2
			read(1,buf,2);				//read confirmation from c2
			write(0,buf,strlen(buf)+1);		//send confmirmation to c1
			if(buf=="1")
			{
				printf("Won the competition :)))) \n");
				break;
			}
			else continue;
		}
		else	continue;
	}
return 0;
}