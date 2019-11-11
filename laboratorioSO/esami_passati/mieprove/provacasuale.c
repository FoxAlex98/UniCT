#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define BUFFER 1024
#define DIM_PRED 30
#define PROD 0
#define CONS 1

typedef struct{
	long type;
	unsigned int val;
}shmmsg;

int WAIT(int sem_des, short unsigned int num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
	return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, short unsigned int num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
	return semop(sem_des, operazioni, 1);
}

int figlio(){

}

int main(int argc, char* argv[])
{
	int shm_ds, sem_ds;
	struct stat buff;
	shmmsg *dati;

	if(argc < 2){
		printf("deve avere più di due valori\n");
		exit(0);
	}

	if((stat(argv[1],&buff) == -1) || (!S_ISREG(buff.st_mode))){
		perror("stat");
		exit(1);
	}

	if((shm_ds = shmget(IPC_PRIVATE, BUFFER, IPC_CREAT|0600)) == -1){
		perror("shmget");
		exit(1);
	}

	if((dati = (shmmsg*) shmat(shm_ds, NULL, 0)) == (shmmsg*) -1){
		perror("shmmsg");
		exit(1);
	}

	if((sem_ds = semget(IPC_PRIVATE, 2, IPC_CREAT|0600)) == -1){
		perror("semget");
		exit(1);
	}

	printf("CPU prematurata antani a destra\n");

	if(semctl(sem_ds, PROD, SETVAL, 1) == -1){
		perror("PROD");
		exit(1);
	}

	if(semctl(sem_ds, CONS, SETVAL, 0) == -1){
		perror("CONS");
		exit(1);
	}

	if(semctl(sem_ds, 0, IPC_RMID, 0) == -1){
		perror("semctl");
		exit(1);
	}

	if(shmctl(shm_ds, IPC_RMID, NULL) == -1){
		perror("shmctl");
		exit(1);
	}
}