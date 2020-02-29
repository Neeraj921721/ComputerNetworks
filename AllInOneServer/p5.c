#include"header.h"

int main(){
	char *data;
	int x=read(0,data,100);
	data[x]='\0';
	printf("From server(in p5) : [%s]",data);
return 0;
}
