#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buff{
	long type;
	long int msg;
}msgout,msgin;

long int inttobin(long int num){	
	if (num == 0){
		return 0;
	}else{
		return (num%2 + 10*inttobin(num/2));
	}
}

int main(){
	key_t key;
	int msgid;

	key = ftok("os8",1);

	msgid = msgget(key,0660 | IPC_CREAT) ;

	printf("\nServer running....\n");

	while(msgrcv(msgid,&msgin,sizeof(msgin),1,0) == -1);

	msgout.msg = inttobin(msgin.msg);
	msgout.type = 2 ;

	msgsnd(msgid , &msgout, sizeof(msgout),0);

	printf("\nTask completed...Shutting down Server....bye!\n");

	return 0;
}