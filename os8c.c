#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buff{
	long type;
	long int msg;
}msgout,msgin;

int main(){
	key_t key;
	int msgid;
	msgout.type = 1;
	printf("\nEnter an integer no. : ");
	scanf("%ld",&msgout.msg);

	key = ftok("os8",1);

	msgid = msgget(key,0660 | IPC_CREAT) ;

	msgsnd(msgid,&msgout ,sizeof(msgout),0);

	while(msgrcv(msgid , &msgin , sizeof(msgin),2,0) == -1);
	
	printf("\nBinary equivalent of integer entered : %ld\n\n",msgin.msg);

	msgctl(msgid,IPC_RMID,NULL);
	return 0;
}
