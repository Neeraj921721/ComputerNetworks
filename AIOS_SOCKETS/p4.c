#include"header.h"
int main(int argc,char *argv[]){
	printf("This is P4 Press K to send a signal to Server \n");
	while(1){
		char sig;
		scanf("%c",&sig);
		if(sig=='K'){
			kill(atoi(argv[1]),SIGINT);	
		}
	}
	return 0;
}
