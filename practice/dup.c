#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	int fd=open("abc.txt",O_WRONLY | O_APPEND | O_CREAT);
	int new_fd=dup(fd);	// both fd and new_fd can modify the same file...dup assigns lowest possible file descriptor 
	char msg[]="Hi";
	write(fd,msg,sizeof(msg));
	write (new_fd,msg,sizeof(msg));
	close(fd);
	close(new_fd);
return 0;
}

