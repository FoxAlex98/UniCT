#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define percorso "/proc/stat"
#define sampleDefault 30
#define DIMBUFFER 1024

void Sampler(){
	
}

void Analyzer(){

}

void Plotter(){

}

int WAIT(int sem_des, int num_semaforo){ 
	struct sembuf operazioni[1] = {{num_semaforo,-1,0}}; 
	return semop(sem_des, operazioni, 1); }
int SIGNAL(int sem_des, int num_semaforo){ 
	struct sembuf operazioni[1] = {{num_semaforo,+1,0}}; 
	return semop(sem_des, operazioni, 1); }

int main(int argc, char* argv[]){
	int Nsamples=sampleDefault;

	
	if(argc==2)//controllo
		Nsamples=atoi(argv[1]);
		
		
		//inizializzazione di tutto
		
	//suddividiamo i figli
	if(fork()==0)
		Sampler();
	if(fork()==0)
		Analyzer();
	if(fork()==0)
		Plotter();
		
		
		
}
