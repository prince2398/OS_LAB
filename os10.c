#include <sys/sem.h>
#include <sys/sem.h>
#include <stdio.h>

union semun{
	int val; 
	struct semid_dss *buf;
	ushort *array;
}u1,u2,u3;

int main(){
	key_t key;
	int sem_id;
	int n ;

	printf("\nEnter buffer size i.e. maximum no. of product produces : ");
	scanf("%d",&n);

	key = ftok("os10",1);

	sem_id = semget(key , 3, IPC_CREAT |0660);
	
	u1.val = 0;
	int mutex = semctl(sem_id , 0 , SETVAL ,u1 );
	
	u2.val = n;
	int empty = semctl(sem_id , 1 , SETVAL ,u2 );
	
	u3.val = 0;
	int full = semctl(sem_id , 2 , SETVAL ,u3 );

	int p = fork();
	
	if (p == 0){
		//producer
		
		struct sembuf is_full = { 2, 0, IPC_NOWAIT };
		semop(sem_id , is_full , 1);

		struct sembuf is_lock = { 0, 0, IPC_NOWAIT };
		semop(sem_id , is_lock , 1);

		// struct sembuf sem_lock = { 0, 0, IPC_NOWAIT };
		// if (semop(sem_id ,&sem_lock , 1 ) == -1){
		// 	printf("Producer: buffer busy...Consumer is consuming\n");
		// }else{

			//CS
			struct sembuf sem_lock = { 0, 1, IPC_NOWAIT };
		 	semop(sem_id ,&sem_lock , 1 );
		 	struct sembuf desc_empty = { 1, -1, IPC_NOWAIT };
			semop(sem_id , &desc_empty , 1 );
			struct sembuf inc_full = { 2, 1, IPC_NOWAIT };
			semop(sem_id , &inc_full, 1);
			struct sembuf sem_unlock = { 0, -1, IPC_NOWAIT };
			semop(sem_id, sem_unlock , 1);
	//	}

	}else if(p > 1){
		//consumer
		struct sembuf is_empty = { 1, 0, IPC_NOWAIT };
		semop(sem_id ,is_empty , 1);

		struct sembuf is_lock = { 0, 0, IPC_NOWAIT };
		semop(sem_id , is_lock , 1);
		//CS
		struct sembuf sem_lock = { 0, 1, IPC_NOWAIT };
		semop(sem_id ,&sem_lock , 1 );
		struct sembuf desc_full = { 2, -1, IPC_NOWAIT };
		semop(sem_id , &desc_full, 1);
		struct sembuf inc_empty = { 1, 1, IPC_NOWAIT };
		semop(sem_id , &inc_empty , 1 );
		struct sembuf sem_unlock = { 0, -1, IPC_NOWAIT };
		semop(sem_id, sem_unlock , 1);
		
	}else{
		printf("\n Forking error ... ");
	}
	return 0;
}