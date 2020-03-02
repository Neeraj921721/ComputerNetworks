#include"header.h"
#define port1 8081          // for tcp clients
#define port2 8082          // for threaded tcp clients
#define port3 8083          // for udp clients
#define MAX 5
#define services 3
#define max(a,b) (a>b)?a:b

int sfd1,sfd2,sfd3;
int nsfd1,nsfd2;

void *ThreadedServiceServer(void *arg){
    //int nsfd=*((int*)arg);          // casting arg to int * and then storing value at arg to nsfd
    char rbuffer[100];
    char sbuffer[100];
    while(1)
    {
        recv(nsfd2,rbuffer,100,0);
        for(int i=0;i<strlen(rbuffer);i++)
        {
            int xx=rbuffer[i];
            if(xx>= 97 && xx<=122)
            {
                sbuffer[i]=(char)(xx-32);
            }
            else sbuffer[i]=rbuffer[i];
        }
        sbuffer[strlen(sbuffer)]='\0';
        send(nsfd2,sbuffer,strlen(sbuffer)+1,0);
    }
}

int main(){
    struct sockaddr_in saddrt,saddru;
    socklen_t slent=sizeof(saddrt);
    socklen_t slenu=sizeof(saddru);
    int opt=1;

    sfd1=socket(AF_INET,SOCK_STREAM,0);
    saddrt.sin_family=AF_INET;
	saddrt.sin_port=htons(port1);
	saddrt.sin_addr.s_addr=INADDR_ANY;
    setsockopt(sfd1,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
    bind(sfd1,(struct sockaddr *)&saddrt,slent);

    sfd2=socket(AF_INET,SOCK_STREAM,0);
    saddrt.sin_family=AF_INET;
	saddrt.sin_port=htons(port2);
	saddrt.sin_addr.s_addr=INADDR_ANY;
    setsockopt(sfd2,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
    bind(sfd2,(struct sockaddr *)&saddrt,slent);

    sfd3=socket(AF_INET,SOCK_DGRAM,0);
    saddru.sin_family=AF_INET;
	saddru.sin_port=htons(port3);
	saddru.sin_addr.s_addr=INADDR_ANY;
    bind(sfd3,(struct sockaddr *)&saddru,slenu);

    listen(sfd1,MAX);
    listen(sfd2,MAX);

    fd_set readfds;
    FD_ZERO(&readfds);
    struct timeval t;
    t.tv_sec=5000;
    t.tv_usec=0;

    while(1)
    {
        listen(sfd2,MAX);
        FD_SET(sfd1,&readfds);
        FD_SET(sfd2,&readfds);
        FD_SET(sfd3,&readfds);
        int nfds=max(sfd1,max(sfd2,sfd3));
        select(nfds+1,&readfds,NULL,NULL,&t);

        if(FD_ISSET(sfd1,&readfds))
        {
            nsfd1=accept(sfd1,(struct sockaddr *)&saddrt,(socklen_t *)&slent);

            pid_t pid=fork();
            if(pid!=0)
            {
                close(nsfd1);
            }
            else
            {
                close(sfd1);
                close(sfd2);
                close(sfd3);
                dup2(nsfd1,0);
                dup2(nsfd1,1);
                char *arg[2];
                strcpy(arg[0],"./forkedserver");
                arg[1]=NULL;
                execv(arg[0],arg);
            }
        }
        if(FD_ISSET(sfd2,&readfds))
        {
            nsfd2=accept(sfd2,(struct sockaddr *)&saddrt,(socklen_t *)&slent);
            pthread_t t;
            //int *arg=(int*)malloc(sizeof(int));
            //*arg=nsfd2;
            pthread_create(&t,NULL,ThreadedServiceServer,NULL/*arg*/);
        }
        if(FD_ISSET(sfd3,&readfds))
        {
            char rbuffer[100];
            char sbuffer[100];
            recvfrom(sfd3,rbuffer,100,MSG_WAITALL,(struct sockaddr *)&saddru,(socklen_t*)&slenu);
            printf("%s\n",rbuffer);
            for(int i=0;i<strlen(rbuffer);i++)
            {
                int xx=rbuffer[i];
                if(xx>= 97 && xx<=122)
                {
                    sbuffer[i]=(char)(xx-32);
                }
                else sbuffer[i]=rbuffer[i];
            }
            sbuffer[strlen(sbuffer)]='\0';
            sendto(sfd3,sbuffer,strlen(sbuffer)+1,MSG_CONFIRM,(struct sockaddr *)&saddru,slenu);
        }
    }
return 0;
}
