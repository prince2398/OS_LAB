#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
	char *msg1 = "Child : Hello I Want to find sum of 2,3.";
	char *msg2 = "Parent : Sum is 5.";
	int p,p1[2],p2[2];

	if (pipe(p1) == -1){
		fprintf(stderr, "Pipe Failed" );
		return 1 ; 
	}
	
	if (pipe(p2) == -1){
		fprintf(stderr, "Pipe Failed" );
		return 1 ; 
	}

	p = fork();
	
	if(p==0){
		char buff[100];
		write(p1[1],msg1,strlen(msg1));
		wait(NULL);
		
		read(p2[0],buff,100);
		printf("%s\n",msg2);

		printf("Child : Here I exit.\n");
		exit(0);

	
	}else if(p>0){
		char buff[100];
		read(p1[0],buff,100);
		printf("%s \n",buff);
		
		write(p2[1],msg2,strlen(msg2));
		close(p2[1]);
	}
	return 0;
}
