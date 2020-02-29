#include"header.h"
#define READ 0
#define WRITE 1
char ClientIds[100][20];
int noclients=0;
int Inout[100]={0};
int Openfd[100];
void SignalHandler(int signo)
{
	printf("Received message from Process 4\n");
	for(int j=0;j<noclients;j++)
	{
		if(Inout[j]==1)
		{
			printf("Client available to echo\n");
			Inout[j]=-1;
			close(Openfd[j]);
			char statement[72]="";
			strcat(statement,"gnome-terminal -- /bin/bash -c './Echoserver ");
			strcat(statement,ClientIds[j]);
			strcat(statement,";'");
			system(statement);
			break;
		}
	}
}
int main()
{
	int mpid=getpid();
	printf(" Server starting-%d-\n",getpid());
	
	int pfd[2]; // Pipe to be used by P1
	
	int ffd,fd,ofd,famfd;
	
	signal(SIGUSR1,SignalHandler);
	
	pipe2(pfd,O_NONBLOCK);
	
	mkfifo("Process2Fifo",0660);
	mkfifo("Famousfifo",0660); 
	
	FILE *fp=popen("./Process3","r");
	FILE *ofp=popen("./Process5","w");
	
	ffd=open("Process2Fifo",O_RDONLY|O_NONBLOCK);
	if(ffd<0)
		perror("Open file error\n");
	
	famfd=open("Famousfifo",O_RDONLY|O_NONBLOCK);
	fd=fileno(fp);
	ofd=fileno(ofp);
	//dup2(ofd,1);   // Dup to process 5 	
	
	
	struct pollfd fds[5];
	for(int i=0;i<5;i++)
	{
		fds[i].events=POLLIN;
		fds[i].revents=0;
	}
	fds[0].fd=0;           // Keyboard input
	fds[1].fd=pfd[READ];   // Pipe from P1
	fds[2].fd=ffd;         // Named pipe from P2
	fds[3].fd=fd;          // Popen from P3
	fds[4].fd=famfd;       // Famous fifo
	int c=fork();
	if(c>0) // Parent    
	{
		sleep(2);
		close(pfd[WRITE]);
		while(1)
		{
			int r=poll(fds,5,2000);
			if(r==0)
			{
				printf("Time out\n");
				
			}
			else
			{
				int fromwhere=-1;
				for(int i=0;i<5;i++)
				{
					if(fds[i].revents&POLLIN)
					{
						fds[i].revents=0;
						fromwhere=i;
						break;	
					}
				}
				char Buffer[1024]="";
				if(fromwhere==0)
				{
					read(0,Buffer,1024);
					for(int j=0;j<noclients;j++)
					{
						if(Inout[j]==1)
						{
							int p=write(Openfd[j],Buffer,strlen(Buffer)+1);
							if(p<0)perror("Client write error:\n");
						}
					}
					printf("%s\n",Buffer);
					printf("From STDIN: %s\n",Buffer);
				}
				else if(fromwhere==3)
				{
					fgets(Buffer,20,fp);
					fgetc(fp);
					fflush(fp);
					for(int j=0;j<noclients;j++)
					{
						if(Inout[j]==1)
						{
							int p=write(Openfd[j],Buffer,strlen(Buffer)+1);
							if(p<0)perror("Client write error:\n");
						}
					}
					printf("%s\n",Buffer);

				}
				else if(fromwhere==4)
				{
					int r=read(fds[4].fd,Buffer,1024);
					printf("Connection established with client %s\n",Buffer);
					if(r<=0) continue;
					if(Buffer[0]=='#')
					{
						int k=1;
						char temp[10]="";
						while(Buffer[k]!='|')
						{
							strncat(temp,&Buffer[k],1);
							k++;
						}
						temp[k-1]='\0';
						printf("Parsed input: %s\n",temp);
						strcpy(ClientIds[noclients],temp);
						Inout[noclients]=1;
						noclients++;
						mkfifo(temp,0660);
						int h=open(temp,O_WRONLY);
						if(h<0)perror(" # Error ");
						Openfd[noclients-1]=h;
					}
					else if(Buffer[0]=='X')
					{	
						int k=1;
						char temp[10]="";
						while(Buffer[k]!='|')
						{
							strncat(temp,&Buffer[k],1);
							k++;
						}
						temp[k-1]='\0';
						for(int j=0;j<noclients;j++)
						{
							if(strcmp(ClientIds[j],temp)==0)
							{
								Openfd[j]=open(temp,O_WRONLY);
								Inout[j]=1;
								break;
							}
						}	
					}
				}
				else if(fromwhere!=-1)
				{
					read(fds[fromwhere].fd,Buffer,1024);
					for(int j=0;j<noclients;j++)
					{
						if(Inout[j]==1)
						{
							int p=write(Openfd[j],Buffer,strlen(Buffer)+1);
							if(p<0)perror("Client write error:\n");
						}
					}
					printf("%s\n",Buffer);
				}
			}
		}
	}
	else     // Child
	{
		pclose(fp);
		for(int i=0;i<3;i++)
		{	
			int pid=fork();
			if(pid==0)   //Grandchild
			{
				if(i==0)
				{
					close(pfd[READ]);
					while(1)
					{
						char Bff[]="Input from process1";
						write(pfd[WRITE],Bff,strlen(Bff)+1);
						for(int j=0;j<0x2fffffff;j++)
						;
					}
					exit(0);
				}
				else if(i==1)
				{
					execlp("./Process2","./Process2",NULL);
					exit(0);
				}	
				else if(i==2)
				{
					char temp[10]="";
					snprintf(temp,10,"%d",mpid);
					char statement[72]="";
					strcat(statement,"gnome-terminal -- /bin/bash -c './Process4 ");
					strcat(statement,temp);
					strcat(statement,";'");
					system(statement);
					exit(0);
				}
			}
		}
		close(pfd[READ]);
		close(pfd[WRITE]);
		exit(0);
	}
}
