#include<stdio.h>
int global=0;
int main()
{
	int local=0;
	int p;
	p=fork();
	 	if(p==0)
	{
		local++;
		global++;

		printf("\t\tIN CHILD LOCAL=%d GLOBAL=%d\n",local,global);
	}
	else
	{
		if(p>0)
		{
			printf("\t\tIN PARENT LOCAL=%d GLOBAL=%d\n",local,global);
		}
		else
		{
			printf("ERROR CREATION OF CHILD");
		}	
	}
}
