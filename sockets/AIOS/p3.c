#include"header.h"
int main()
{
	int t=5;
	while(t--)
	{
		for(int j=0;j<0x2fffffff;j++)
		;
		write(1,"Input from process3\n",20);
	}
	return 0;
}

