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
char * append(char str[],char c){
	int len = strlen(str);
	char *str1 = malloc(len+1+1);
	strcpy(str1,str);
	str[len] = c;
	str[len+1] = '\0';
	return str1;
}

//Consume product
void consumeProduct(char *fileName,char str[]){
	FILE *buffer = fopen(fileName,"a+");
	FILE *temp = fopen("temp.txt","w");
	
	char ch;
	int len;
	int line = 0,t;

	while((ch = fgetc(buffer)) != EOF){
		if (ch == '\n'){
			line ++;
		}
	}
	line = line - 1;
	rewind(buffer);

	while((ch = fgetc(buffer)) != EOF){
		if (ch == '\n'){
			t++;
		}
		if (t!=line){
			fputc(ch,temp);
		}else{
			len = strlen(str);
			str[len] = ch;
			str[len+1] = '\0';
			
		}
	}
	
	fclose(buffer);
	fclose(temp);
	remove(fileName);
	rename("temp.txt",fileName);

}

//consumer
int main(){
	char ch;
	char str[25] = {'\0'};
	int semid = createSem(3);

	do{
		//entry section 
		wait(semid, FULL);
		wait(semid, MUTEX);

		//critical section
		str[0] = '\0';
		consumeProduct("buffer.txt",str);
		
		printf("%s is consumed\n",str);
		//exit section
		signal(semid, MUTEX);
		signal(semid, EMPTY);

		printf("Want to Consume more ?(Y or N)");
		scanf("%c",&ch);
		getchar();
	}while(ch=='Y'||ch=='y');
	return 0;
}