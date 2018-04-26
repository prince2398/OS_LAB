#include <stdio.h>

int main(){
	int i;
	for (i = 0; i < 5; ++i)
	{
		if (fork()==0)
		{
			printf("child %d from parent %d\n",getpid() ,getppid());
			exit(0);
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		wait(NULL);
	}
}