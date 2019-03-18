#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/ipc.h>
main()
{
    if( fork() ){
	    int id, semp;
	    struct sembuf s;
	    char* ch;
	    //Create a shared memory
	    if( (id = shmget(2, 20, IPC_CREAT | 0777))==-1 ){
		perror("shmget");
		return;
	    }
	    //Creating a semaphore
	    semp = semget(2, 3,IPC_CREAT|0777);
	    if(semp == -1){
		perror("semget");
		return;
	    }
	    //Giving value to the stuct sembuf members
	    s.sem_num = 0;
	    s.sem_op = 0;
	    s.sem_flg = 0;
	    //Attaches shared memory 
	    if((ch = shmat(id, (void*)NULL, 0))==-1){
		perror("shmat");
		return;
	    }
	    //Infinite loop
	    while(1){
		//Perform operation on selected semaphore
	  	semop(semp, &s, 1);
	   	puts("Enter the message\n");
	    	gets(ch);
	 	//Setting semaphore index with val (semaphore, index, setval, value)
	 	semctl(semp, 0, SETVAL, 1);    	
		semctl(semp, 1, SETVAL, 0);
   		}
    } else {
	    int id, semp, semval;
	    char* ptr=NULL;
	    struct sembuf s;
	    //Create a shared memory
	    if( (id = shmget(2, 20, IPC_CREAT|0777) ) == -1 ){
		perror("shmget");
		return;
	    }
	    
	    ptr = shmat(id, 0, SHM_RDONLY);
	    //Create semaphore
	    semp = semget(2, 3,IPC_CREAT|0777);
	    if(id == -1){
		perror("semget");
		return;
	    }
	    //Set values for the sruct sembuf members
	    s.sem_num = 1;
	    s.sem_op = 0;
	    s.sem_flg = 0;
	    
	    while(1){
		//Perform operation on semaphore based on the id
	      	semop(semp, &s, 1);
		puts("wait...............\n");
	 	puts(ptr);
		fflush(stdout);
		//Semaphore is controlled and given index and value
		semctl(semp, 1, SETVAL, 1);
	 	semctl(semp, 0, SETVAL, 0);
	    }
	    //Detach the shared memory
	    shmdt(ptr);
    }
    return;
}
