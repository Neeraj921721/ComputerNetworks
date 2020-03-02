#include"header.h"

int main(){
    while(1)
    {
        char rbuffer[100];
        char sbuffer[100];
		read(0,rbuffer,100);
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
		write(1,sbuffer,strlen(sbuffer)+1);
    }
return 0;
}
