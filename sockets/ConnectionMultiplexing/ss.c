#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char* argv[]){
	while(1){
		char buf[100];
		read(0,buf,100);
		strcat(buf," from server ");
		write(1,buf,strlen(buf)+1);	
	}
return 0;	
}

