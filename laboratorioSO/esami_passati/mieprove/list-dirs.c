#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define MUTEX 0
#define FILES 1
#define DIRS 2
#define SIZE 1024

typedef struct{
	unsigned long dim;
	char nome[SIZE];
}shm_data;

int WAIT(int sem_des, short unsigned num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
	return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, short unsigned num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
	return semop(sem_des, operazioni, 1);
}


void fileconsumer(){

}

void dirconsumer(){

}

void reader(const char *path, shm_data dati, int sem){
	DIR* dir;
	struct stat buff;
	struct dirent *a;
	dir = opendir(path);

	while(a = readdir(dir) != NULL){
			if(strcmp(a->d_name,".") == 0 || strcmp(a->d_name, "..") == 0)
				continue;

				if((stat(a->d_name, &buff) == -1)
				{
					perror("stat");
					exit(1);
				}

				if(S_ISDIR(buff.st_mode)))
				{
						WAIT(sem,MUTEX);
						dati.dim = 0;
						strcpy(dati.nome,path);
						SIGNAL(sem,MUTEX);
						SIGNAL(sem,DIRS);
				}
				else{
						WAIT(sem,MUTEX);
						dati.dim = buff.st_size;
						strcpy(dati.nome,path);
						SIGNAL(sem,MUTEX);
						SIGNAL(sem,FILES);
				}
			
			}		


}


int main(int argc, char const *argv[])
{
	int shm_des, sem_des;
	shm_data *dati;

	if(argc<2){
		printf("numero argomenti sbagliato\n");
		exit(0);
	}

	if((shm_des = shmget(IPC_PRIVATE, sizeof(shm_data), IPC_CREAT|0600)) == -1){
		perror("shmget");
		exit(1);
	}

	if((dati = (shm_data*) shmat(shm_des, NULL, 0)) == NULL){
		perror("shmat");
		exit(1);
	}

	if((sem_des = semget(IPC_PRIVATE, 3, IPC_CREAT|0600)) == -1){
		perror("semget");
		exit(1);
	}

	semctl(sem_des, MUTEX, SETVAL, 1);
	semctl(sem_des, FILES, SETVAL, 0);
	semctl(sem_des, DIRS, SETVAL, 0);

	printf("cpu prematurata antani a destra\n");

	for(int i = 1; i<argc;i++){
		if(fork()==0)
			reader(argv[i], *dati, sem_des);
	}

	if(fork() == 0)
		fileconsumer();
	if(fork() == 0)
		dirconsumer();

	if((semctl(sem_des, 0, IPC_RMID, 0)) == -1){
		perror("semctl");
		exit(1);
	}

	if((shmctl(shm_des, IPC_RMID, NULL)) == -1){
		perror("shmctl");
		exit(1);
	}

}