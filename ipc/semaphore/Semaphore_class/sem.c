#include<stdio.h>
#include<sys/sem.h>
#include<sys/ipc.h>
main(int argc,char **argv)
{
	int id,semval,i,flg;
	struct sembuf v;
	id=semget(1,3,IPC_CREAT|0777);
	if(id==-1)
	{
		perror("semget");
		return;
	}
	v.sem_num=0;
	v.sem_op=0;
	v.sem_flg=0;
	for(i=0;i<26;i++)
	{
		flg = semop(id,&v,1);
		printf("%d \n",i);
		fflush(stdout);
		sleep(2);
		semctl(id,0,SETVAL,1);
		semctl(id,1,SETVAL,0);
		semctl(id,2,SETVAL,1);
	}
}
