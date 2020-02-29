#include<stdio.h>
#include<unistd.h>

int main(){
	while(1){
		char buf[100];
		scanf("%s",buf);
		write(1,buf,sizeof(buf));
	}
return 0;
}
