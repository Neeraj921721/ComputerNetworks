#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	int pp1[2];
	int pp2[2];
	int ret1=0,ret2=0;

	ret1=pipe(pp1);
	if(ret1 == -1){
		printf("Couldn't open the pipe 1..... exiting \n");
		exit(1);
	}
	
	ret2=pipe(pp2);
	if(ret2 == -1){
		printf("Couldn't open the pipe 2..... exiting \n");
		exit(1);	
	}
	
	int pid=fork();
	
	if(pid != 0){
		close(pp1[0]);
		close(pp2[1]);
		
		char filename[20];
		printf("Enter the file name : ");		
		scanf("%s",&filename);
		printf("Writing File name into pipe 1.........\n");		
		write(pp1[1],filename,sizeof(filename));
		wait(NULL);
		char contents[100];
		printf("Reading contents sent by child process from pipe 2............\n");
		read(pp2[0],contents,sizeof(contents));
		printf("Contents of the file is : \n %s \n",contents);
			
	}
	else{
		close(pp1[1]);	
		close(pp2[0]);
		sleep(10);
		char filename[20];
		printf("Reading the file name by child process from pipe 1.........\n");
		read(pp1[0],filename,sizeof(filename));
		
		printf("Opening the file %s sent by parent process.....\n",filename);
		FILE *fptr=fopen(filename,"r");
		if(fptr == NULL ){
			printf("Couldn't open file.....exiting ....\n");
			exit(-1);
		}
		int buf;
		char contents[100];
		int ind=0;
		printf("Reading the file %s sent by parent process from pipe 1...........\n",filename);
		while( (buf = fgetc(fptr) ) != EOF ){
			contents[ind]=buf;
			ind++;
		}
		printf("Writing the contents of the file into pipe 2.....\n");
		write(pp2[1],contents,sizeof(contents));
		exit(0);
	}
return 0;
}
