#include <stdio.h>

int global = 0;

int main(){
	int local=0;
	int p;
	p=fork();
	if (p<0){
		printf("failure in creating child.\n");
	// }else if (p==0){
	// 	printf("child %d\n",getpid());  // child
	// 	printf("parent %d\n",getppid() ); //parent
	}else if (p>0){
		printf("back in parent.\n");
	}else{
		printf("in child gonna execute my program\n");
		char  *args[] = {"./hello"};
		execvp(args[0],NULL);
	}
	

	//system("ps -f");


}