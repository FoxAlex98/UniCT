//X81000681 Alessandro Sorbello

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

#define DIM_ALF 26
#define BUFFER 2048

typedef struct {
	int type;
	unsigned long contatori[DIM_ALF];
}msg;

void figlio(char *path, int coda, int pos){
	int file_ds;
	msg messaggio;
	struct stat buff;

	char *mappa;

	messaggio.type = 1;
	for(int i = 0; i < DIM_ALF; i++){
		messaggio.contatori[i] = 0;
	}

	if(stat(path,&buff) == -1 || !S_ISREG(buff.st_mode)){
		messaggio.type = 2;
		msgsnd(coda,&messaggio,sizeof(messaggio)-sizeof(long), 0);
		exit(1);
	}

	if(((file_ds = open(path, O_RDONLY)) == -1) || ((mappa = (char *) mmap(NULL, buff.st_size, PROT_READ, MAP_SHARED, file_ds, 0)) == MAP_FAILED)){
		messaggio.type = 2;
		msgsnd(coda, &messaggio, sizeof(messaggio)-sizeof(long), 0);
		exit(1);
	}

	for(int i = 0; i < buff.st_size; i++){
		if(mappa[i] >= 'a' && mappa[i] <= 'z')
			messaggio.contatori[mappa[i] - 'a']++;
		else if(mappa[i] >= 'A' && mappa[i] <= 'Z')
				messaggio.contatori[mappa[i] - 'A']++;		
	}

	printf("processo T-%d\n con path %s alla riscossa", pos, path);

	for(int i = 0; i < DIM_ALF; i++)
		printf("%c: %ld \t", 'a'+i, messaggio.contatori[i]);
	printf("\n");

	if(msgsnd(coda, &messaggio, sizeof(messaggio),0) == -1)
		perror("msgsnd");

	exit(0);
}



int main(int argc, char *argv[])
{
	int coda_ds;
	msg mex;
	unsigned long totale[DIM_ALF];

	if(argc < 2){
		printf("È necessario inserire almeno un file\n");
		exit(0);
	}

	//creazione coda
	if((coda_ds = msgget(IPC_PRIVATE, IPC_CREAT|0660)) == -1 ){
		perror("msgget");
		exit(1);
	}

	printf("CPU prematurata antani a destra\n");

	for(int i = 0; i < DIM_ALF; i++){
		totale[i] = 0;
	}

	//creiamo i figli
	for(int i = 1; i < argc; i++){
		if(fork() == 0)
			figlio(argv[i], coda_ds, i);
	}

	for(int i = 0; i < argc-1; i++){
		if(msgrcv(coda_ds, &mex, sizeof(mex) - sizeof(long), 0, 0) == -1)
			perror("msgrcv");
		if(mex.type == 2){
				printf("avvenuto errore nel figlio\n");
				continue;
			}

			
		
		for(int j = 0; j < DIM_ALF; j++){
			totale[j] += mex.contatori[j];
		}
	}

	int max = 0;

	printf("processo padre\n");
	for(int i = 0; i < DIM_ALF; i++){
		if(totale[i] > max){
			max = i;
		} 
		printf("%c: %ld\t", 'a'+ i, totale[i]);
	}
	printf("\n");

	printf("la lettera più usata è %c con %ld occorrenze\n", 'a' + max, totale[max]);

	//cancellazione coda
	if(msgctl(coda_ds, IPC_RMID, NULL) == -1){
		perror("msgctl");
		exit(1);
	}
}