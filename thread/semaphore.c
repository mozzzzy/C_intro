#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/sem.h>
#include <sys/wait.h>

/*semaphore operation (semaphore set id, semaphore num, semaphore operation)*/
void MySemop(int p_semid, int p_semnum, int p_op){
	struct sembuf sops[1];
		//sops =>unsigned short sem_num;  /*semaphore number*/
		//	 short	  sem_op;   /*semaphore operation*/
		//	 short	  sem_flg;  /*operation flag */

	sops[0].sem_num = p_semnum;	//semaphore number
	sops[0].sem_op = p_op;	//semaphore operation
	sops[0].sem_flg = 0;

	if (semop(p_semid, sops, 1) == -1){	//semop(int semid， struct sembuf *sops， unsigned nsops);
						//	semid : semaphore id
						//	sops  : set a structucture "sembuf"
						//	nsops : 1 -> 1 pluss, -1 -> 1 minus
		perror("MySemop");
		exit(1);
	}

}


int main(){

	/*create semaphore set has 2 semaphore*/
	int semid;
	if ((semid = semget(IPC_PRIVATE, 2, 0600)) == -1){
		perror("main : semget");
		return 1;
	}

	/*insert 0 into all semaphore*/
	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	} ctl_arg;
	unsigned short vals[2] = {0, 0};
	ctl_arg.array = vals;
	if (semctl(semid, 0, SETALL, ctl_arg) == -1){
		perror("main : semctl");
		return 1;
	}


	/*create process*/
	//child process1
	if(fork()==0){
		MySemop(semid, 0, -1);
		printf("child process1 : COMPLETE GETTING SEM0\n");

		MySemop(semid, 0, 1);
		printf("child process1 : COMPLETE RELEASE SEM0\n");
		

	}else{
	//parent process
		/*create process*/
		//child process2
		if(fork()==0){
			MySemop(semid, 0, 1);
			printf("child process2 : COMPLETE RELEASE SEM0\n");
		//parent process
		}else{
			wait(0);
			if (semctl(semid, 0, IPC_RMID, ctl_arg) == -1){
				perror("main : semctl");
				return 1;  
			}
			printf("parent process : COMPLETE DELETE SEM0\n");
		}
	}


	

	return 0;
}
