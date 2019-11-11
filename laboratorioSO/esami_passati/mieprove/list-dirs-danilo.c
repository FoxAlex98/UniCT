// Danilo Santitto x81000689

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<ctype.h>

#define SIZE 1024
#define MUTEX 0
#define FILES 1
#define DIREC 2

int WAIT(int sem_des, unsigned short int num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
	return semop(sem_des, operazioni, 1);
}
int SIGNAL(int sem_des, unsigned short int num_semaforo){
	struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
	return semop(sem_des, operazioni, 1);
}

typedef struct {
	int size;//size che vogliamo sapere in output
	char name[SIZE];//nome che vogliamo sapere per il percorso
} msg;

void reader(int sem, msg* p, const char* path){//figli che leggono i bit da un file ciascuno
	DIR *dir;
	struct dirent *a;
	struct stat buff;
	int flag;

	if((dir = opendir(path)) == NULL) {//apriamo la cartella
		perror("opendir");
		exit(1);
	}

	while((a = readdir(dir)) != NULL) {//apriamo le cartelle, una ad una

		if(strcmp(a->d_name, ".") == 0 || strcmp(a->d_name, "..") == 0)//escludendo . e ..
			continue;
		char tmpPath[SIZE];
		strcpy(tmpPath, path);//prendiamo il percorso
		strcat(tmpPath, a->d_name);//e ci concateniamo il nome della cartella corrente

		if(stat(tmpPath, &buff) == -1) {//controlliamo lo stato
			perror("stat");
			exit(1);
		}

		if(S_ISDIR(buff.st_mode)){//se è una cartella
			WAIT(sem, MUTEX);//mutex sempre quella più interna
			strcpy(p->name, tmpPath);//copiamo il nome
			SIGNAL(sem, MUTEX);
			SIGNAL(sem, DIREC);//risvegliamo il dir_consumer
		}
		else if(S_ISREG(buff.st_mode)){//se invece è un file
			WAIT(sem, MUTEX);
			strcpy(p->name, tmpPath);
			p->size = buff.st_size;//qui abbiamo bisogno di usare size, perchè stiamo parlando di un file
			SIGNAL(sem, MUTEX);
			SIGNAL(sem, FILES);//risvegliamo il file_consumer
		}
		SIGNAL(sem, MUTEX);

	}

	WAIT(sem, MUTEX);
	p->size = -1;//se arriviamo qua, vuol dire che abbiamo finito il nostro compito
	SIGNAL(sem, MUTEX);
	SIGNAL(sem, FILES);//svegliamo file_consumer
	SIGNAL(sem, DIREC);//svegliamo dir_consumer

	exit(0);//possiamo arrestarci
}

void file_consumer(int sem, msg* p, int n){

	while(n > 0){
		WAIT(sem, FILES);//ci fa addormentare se = 0
		WAIT(sem, MUTEX);

		if(p->size == -1)//fa il tutto finchè non ci sono più processi reader 
			n--;
		else	
			printf("%s [File di %d bytes]\n", p->name, p->size);

		SIGNAL(sem, MUTEX);
	}

	exit(0);
}

void dir_consumer(int sem, msg* p, int n){

	while(n > 0){//fa il tutto finchè non ci sono più processi reader
		WAIT(sem, DIREC);//ci addormentiamo se = 0
		WAIT(sem, MUTEX);

		if(p->size == -1)//abbiamo ricevuto il segnale di arresto di un reader
			n--;
		else	
			printf("%s [directory]\n", p->name);
	
		SIGNAL(sem, MUTEX);
	}

	exit(0);
}

int main(int argc, char const *argv[])
{
	int shmem;
	int sem;
	msg* p;

	//controlliamo gli argomenti
	if(argc < 2){
		printf("Numero di parametri non compatibili\n");
		exit(0);
	}
	
	//creiamo la memoria condivisa
	if((shmem = shmget(IPC_PRIVATE, sizeof(msg), IPC_CREAT|0660)) == -1){
		perror("shmget");
		exit(1);
	}

	//attacchiamo la struct alla memoria condivisa
	if((p = (msg*) shmat(shmem, NULL, 0)) == NULL){
		perror("shmat");
		exit(1);
	}

	//creiamo l'array di semafori
	if((sem = semget(IPC_PRIVATE, 3, IPC_CREAT|0660)) == -1){
		perror("semget");
		exit(1);
	}
	
	//settiamo i semafori
	semctl(sem, MUTEX, SETVAL, 1);//mutua esclusività
	semctl(sem, FILES, SETVAL, 0);//per il file_consumer
	semctl(sem, DIREC, SETVAL, 0);//per il dir_consumer
	
	//facciamo n-1 fork, si esclude il primo, perchè rappresenta il comando
	for(int i = 1; i < argc; i++)
		if(fork() == 0) reader(sem, p, argv[i]);

	int file, dir;//salviamo il pid sta volta

	if((file = fork()) == 0) 
		file_consumer(sem, p, argc - 1);//passiamo n file
	if((dir = fork()) == 0) 
		dir_consumer(sem, p, argc - 1);

	//il padre deve aspettare i figli
	waitpid(file, NULL, 0);
	waitpid(dir, NULL, 0);

	//cancelliamo i semafori
	if(semctl(sem, 0, IPC_RMID, 0) == -1){
		perror("semclt");
		exit(0);
	}

	//cancelliamo la parte di memoria condivisa (non c'è bisogno di staccare la struct, tanto distruggiamo tutto)
	if(shmctl(shmem,IPC_RMID,NULL) == -1){
		perror("shmclt");
		exit(0);
	}
	
	exit(0);
}
