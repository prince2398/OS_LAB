#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>

#define MUTEX 0
#define FULL 1
#define EMPTY 2


union semun{
	int val; 
	struct semid_ds *buf;
	ushort *array;
}un;

//create a semaphore
int createSem(int semNo){
	int id;
	key_t key = ftok("os10",1);

	id = semget(key,semNo,IPC_CREAT | 0660);
	
	if (id<0){
		perror("semget: ");
		exit(1);	
	}

	return id;
}

//initialize the semaphore 
void initializeSem(int semId, int semNo, int value){
	un.val = value ;

	if (semctl(semId,semNo,SETVAL, un)<0){
		perror("semctl: ");
		exit(1);
	}

}

//wait
void wait(int semId,int semNo){
	struct sembuf buff = {semNo, -1, 0};

	if (semop(semId,&buff,1) < 0){
		perror("semop: ");
		exit(1);
	}
}

//signal
void signal(int semId, int semNo){
	struct sembuf buff = {semNo, 1, 0};

	if (semop(semId,&buff,1) < 0){
		perror("semop: ");
		exit(1);
	}
}

//producer 
int main(){
	char ch, *str = "Product";
	char *no, *endl;
	endl[0] = '\n';
	int semid = createSem(3);
	initializeSem(semid, MUTEX, 1);
	initializeSem(semid, FULL, 0);
	initializeSem(semid, EMPTY, 10);

	int i = 0;

	do{
		//entry section 
		wait(semid, EMPTY);
		wait(semid, MUTEX);

		//***critical section***
		FILE *buffer = fopen("buffer.txt","a+");
		
		//produce
		i = i + 1;
		sprintf(str,"%s %d\n",str,i);

		//write in buffer
		fwrite(str, sizeof(str),1,buffer);

		fclose(buffer);

		printf("Product %d is produced.\n",i);

		//exit section
		signal(semid, MUTEX);
		signal(semid, FULL);

		printf("Want to Produce more ?(Y or N): ");
		scanf("%c",&ch);
	}while(ch=='Y'||ch=='y');


	return 0;
}