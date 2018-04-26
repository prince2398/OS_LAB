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
	int semFlag = IPC_CREAT | 0660 ;

	id = semget(key,semNo,semFlag);
	
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
		exit(2);
	}
}


//signal
void signal(int semId, int semNo){
	struct sembuf buff = {semNo, 1, 0};

	if (semop(semId,&buff,1) < 0){
		perror("semop: ");
		exit(2);
	}
}

char *extractPoduct(char *fileName){
	FILE *buffer = fopen(fileName,"a+");
	FILE *temp = fopen("temp.txt","w");
	char *str = NULL;
	char ch;
	size_t len = 0;
	int last = 0;

	fseek(buffer,-11,SEEK_END);
	while(fgetc(buffer)!='\n');
	last = ftell(buffer);
	fseek(buffer,0,SEEK_SET);

	while((ch = fgetc(buffer)) < last){
		fputc(ch,temp);
	}
	while((ch = fgetc(buffer)) != EOF){
		sprintf(str , "%s%c",str,ch);
	}
	fclose(buffer);
	fclose(temp);

	rename("temp.txt",fileName);

	return str;
}

//consumer
int main(){
	char *str,ch;
	int semid = createSem(3);

	do{
		//entry section 
		wait(semid, FULL);
		wait(semid, MUTEX);

		//critical section
		
		str = extractPoduct("buffer.txt");
		if (str[sizeof(str)-1] == '\n'){
			str[sizeof(str)-1] = '\0';
		}
		printf("%s is consumed\n",str);
		//exit section
		signal(semid, MUTEX);
		signal(semid, EMPTY);

		printf("Want to Consume more ?(Y or N)\n");
		scanf("%c",&ch);;
	}while(ch=='Y'||ch=='y');
	return 0;
}