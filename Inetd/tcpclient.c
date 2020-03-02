#include"header.h"

int main(){
	struct sockaddr_in saddr;
    socklen_t slen=sizeof(saddr);

	char portnum[10];
	printf("Enter the port number : " );
	fflush(stdout);
	fgets(portnum,10,stdin);
	fflush(stdin);
	int port=atoi(portnum);

    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(port);
    saddr.sin_addr.s_addr=INADDR_ANY;

	connect(sfd,(struct sockaddr *)&saddr,slen);

	//printing the local port and loocl ip
	struct sockaddr_in myaddr;
	socklen_t mylen=sizeof(myaddr);
	getsockname(sfd,(struct sockaddr *)&myaddr,(socklen_t *)&mylen);
	char myip[16];
	unsigned int myport;
	inet_ntop(AF_INET,&myaddr.sin_addr,myip,sizeof(myip));
	myport=ntohs(myaddr.sin_port);
	printf("Local ip : %s\n Local port : %d\n\n",myip,myport);
	//printing the foreign ip and foreign port
	struct sockaddr_in getaddr;
	socklen_t getlen=sizeof(getaddr);
	getpeername(sfd,(struct sockaddr *)&getaddr,(socklen_t *)&getlen);
	printf("Server ip : %s\n Server port : %d\n\n",inet_ntoa(getaddr.sin_addr),ntohs(getaddr.sin_port));

	fd_set readfds;
    FD_ZERO(&readfds);
    struct timeval t;
    t.tv_sec=5000;
    t.tv_usec=0;
	while(1)
	{
		FD_SET(0,&readfds);
        FD_SET(sfd,&readfds);
        int nfds=sfd+1;
        select(nfds,&readfds,NULL,NULL,&t);
        if(FD_ISSET(0,&readfds))
        {
            char buffer[100];
            fgets(buffer,100,stdin);
            send(sfd,buffer,strlen(buffer)+1,0);
        }
        if(FD_ISSET(sfd,&readfds))
        {
            char buffer[100];
            recv(sfd,buffer,100,0);
			printf("%s\n",buffer);
        }
	}
return 0;
}
