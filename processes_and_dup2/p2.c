#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main (){
	char msg[20];
	scanf("%s",&msg);
	printf("We are in p2 .....Hello sir , how are you \n");
	printf("Message from p1 is %s\n",msg);
return 0;
}
