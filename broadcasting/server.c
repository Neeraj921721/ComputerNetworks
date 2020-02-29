#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>

int main(){
	FILE *rfp=popen("./p1","r");
	int rfd=fileno(rfp);
	int wfd2=fileno(popen("./p2","w"));
	int wfd3=fileno(popen("./p3","w"));	
	int wfd4=fileno(popen("./p4","w"));
	while(1){
		char *buf=(char *)calloc(1024,sizeof(char));	
		int x=read(rfd,buf,100);
		//printf("%s\n",buf);	
		close(rfd);	
		pclose(rfp);
		
		write(wfd2,buf,strlen(buf)+1);
		close(wfd2);

		
		write(wfd3,buf,strlen(buf)+1);
		close(wfd3);
		
		
		write(wfd4,buf,strlen(buf)+1);		
		close(wfd4);
	}
return 0;
}
