#include<stdio.h>
#include<stdlib.h>

int main(){
	system("gcc client.c -o client");
	system("gcc SuperServer.c -o SuperServer");
	system("gcc ThreadedServiceServer.c -lpthread -o ThreadedServiceServer");
return 0;
}
