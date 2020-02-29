#include"header.h"

int main(){
	mkfifo("p2ffo",0666);
	char *data;
	scanf("%s",data);
	int wfd=open("p2ffo",O_WRONLY);
	while(1){
		printf("Enter the data(in p2) : ");
		fgets(data,strlen(data)+1,stdin);
		write(wfd,data,strlen(dsata)+1);	
	}
return 0;
}
