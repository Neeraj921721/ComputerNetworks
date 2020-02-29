#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <poll.h>
#include<fcntl.h>
#define PORT 8080

int main(){
	int sfd;
	struct sockaddr_in saddr;
	socklen_t len=sizeof(saddr);
	sfd=socket(AF_INET,SOCK_STREAM,0);

	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(PORT);

	int cret=connect(sfd,(struct sockaddr *)&saddr,len);
	if(cret == 0)
	{
		printf("Connected !\n");
	}
	else perror("connect error !\n");

	printf("hello\n");

	/*char faltu[10]="faltu";
	send(sfd,faltu,strlen(faltu)+1,0);

	struct sockaddr_in clientaddr,serveraddr;
	char myIP[16];
	socklen_t clen=sizeof(clientaddr);
	unsigned int myport,serverport;
	int rr=getsockname(sfd,(struct sockaddr *)&clientaddr,&clen);
	inet_ntop(AF_INET,&clientaddr.sin_addr,myIP,sizeof(myIP));
	myport=ntohs(clientaddr.sin_port);

	printf("Local ip address: %s\n", myIP);
	printf("Local port : %u\n", myport);

	socklen_t slen=sizeof(serveraddr);
	rr=getpeername(sfd,(struct sockaddr *)&serveraddr,&slen);
	printf("Server IP: %s\n",inet_ntoa(serveraddr.sin_addr));
	printf("Server Port: %d\n",ntohs(serveraddr.sin_port));


	char code[1024];
	recv(sfd,code,1024,0);

	int fd=open("source1.c",O_RDONLY|O_CREAT);
	write(fd,code,strlen(code)+1);
	system("gcc source1.c -o source1");

	while(1)
	{
		int a,b;
		printf("Enter a : ");
		scanf("%d",&a);
		printf("Enter b : ");
		scanf("%d",&b);

		char comm[50];
		sprintf(comm,"./source1 %d %d",a,b);
		system(comm);

		char input[10];
		char output[10];
		sprintf(input,"%d %d",a,b);
		input[strlen(input)]='\0';

		send(sfd,input,strlen(input)+1,0);
		recv(sfd,output,10,0);

		int newfd=open("o1.txt",O_RDONLY);
		char newoutput[10];
		read(newfd,newoutput,10);
		char ans[2];
		if( strcmp(newoutput,output) == 0 ){
			ans[0]='1';
			ans[1]='\0';
			send(sfd,ans,strlen(ans)+1,0);		//send confirmation to c2
			//turn for c2
			recv(sfd,input,10,0);
			char arg1[10]="",arg2[10]="";
			int ind=0;
			char h;
			while( input[ind] != ' ' )
			{
				char str[1];
				str[0]=input[ind];
				strcat(arg1,str);
				ind++;
			}
			arg1[ind]='\0';
			while(input[ind] == ' ') ind++;
			while(input[ind] != '\0' )
			{
				char str[1];
				str[0]=input[ind];
				strcat(arg2,str);
				ind++;
			}
			arg2[ind]='\0';
			a=atoi(arg1);
			b=atoi(arg2);

			system("gcc source1.c -o source1");

			sprintf(comm,"./source1 %d %d",a,b);
			system(comm);
			newfd=open("o1.txt",O_RDONLY);

			read(newfd,newoutput,10);
			send(sfd,newoutput,strlen(newoutput),0);
			recv(sfd,ans,2,0);								//recv confirmation from c2
			if(strcmp(ans,"1")==0)
				break;
			else continue;
		}
		else{
			ans[0]='0';
			ans[1]='\0';
			send(sfd,ans,strlen(ans)+1,0);
		}
	}
	*/
return 0;
}
