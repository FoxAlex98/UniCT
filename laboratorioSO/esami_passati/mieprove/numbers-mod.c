//Alessandro Sorbello X81000681

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>


#define SIZE 1024
#define DIM 10
#define MUTEX 0
#define EMPTY 1
#define FULL 2

typedef struct{
	long x;
	char type;
}shared_data;

int WAIT(int sem_id, unsigned short int sem_num) {
    struct sembuf ops[1] = {{sem_num, -1, 0}};
    return semop(sem_id, ops, 1);
}

int SIGNAL(int sem_id, unsigned short int sem_num) {
    struct sembuf ops[1] = {{sem_num, +1, 0}};
    return semop(sem_id, ops, 1);
}



int main(int argc, char const *argv[])
{

	int sha_des, sem_des;
	shared_data *dati;
	struct stat buff;
	long modulo;
	FILE *fil;

	//setup


	//controlliamo gli argomenti
	if(argc!=3){
		printf("numero di parametri sbagliato\n");
		exit(0);
	}

	//lo stato
	if((stat(argv[1],&buff) == -1) && (!S_ISREG(buff.st_mode))){
		perror("stat");
		exit(1);
	}

	//controllo del modulo
	if((modulo = atol(argv[2])) < 2){
		printf("il modulo deve essere superiore a 1\n");
		exit(0);
	}

	//creiamo la parte di memoria condivisa
	if((sha_des = shmget(IPC_PRIVATE, sizeof(shared_data) * DIM, IPC_CREAT|0600)) == -1){
		perror("shmget");
		exit(1);
	}

	//attacchiamo i dati
	if((dati = (shared_data*) shmat(sha_des, NULL, 0)) == NULL){
		perror("shmat");
		exit(1);
	}

	//creiamo i semafori
	if((sem_des = semget(IPC_PRIVATE, 3, IPC_CREAT|0600)) == -1){
		perror("semget");
		exit(1);
	}

	if(semctl(sem_des, MUTEX, SETVAL, 1) == -1){
		perror("setval MUTEX");
		exit(1);
	}

	if(semctl(sem_des, EMPTY, SETVAL, DIM) == -1){
		perror("setval EMPTY");
		exit(1);
	}

	if(semctl(sem_des, FULL, SETVAL, 0) == -1){
		perror("setval FULL");
		exit(1);
	}


	//fine setup


	printf("CPU prematurata antani a destra\n");

	if((fil = fopen(argv[1], 'r')) == NULL){
		perror("open");
		exit(1);
	}

	//feof fread 

	//for(int i = 0; i < DIM ; i++)



	//inizio distruzione

	if(close(fil) == -1){
		perror("close");
		exit(1);
	}

	if(semctl(sem_des, 0, IPC_RMID, 0) == -1){
		perror("semctl");
		exit(1);
	}

	//distruggiamo la parte di memoria condivisa
	if((shmctl(sha_des, IPC_RMID, NULL)) == -1){
		perror("shmctl");
		exit(1);
	}

	//fine distruzione
}