#include <stdio.h>

void main(int argc,char const *argv[] ){
	int p = fork();
	if(p<0)
		printf("failure to create child\n");
	else if(p==0){	
		printf("Executing client.c program in child process %d of parent process %d\n",getpid(),getppid());
		char *args[]={"./client",argv[1],NULL};
		execvp(args[0],&args);
	}

	wait(NULL);

}


