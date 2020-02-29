#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main (){
	printf("We are in p1.....\n");
	FILE *fp=popen("./p2","w");
	//dup2(fileno(fp),1);
	printf("Message from p1..\n");
	int fdp=pclose(fp);	
	printf("We are in p1.....\n");	
return 0;
}
