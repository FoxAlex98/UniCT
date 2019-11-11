#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){
  	pid_t pid;

	if(argc<2)
	{
	 printf("metti un altro parametro oltre %s\n",argv[0]);
	 exit(1);
	}

	printf("iniziamo\n");

	pid=fork();

	if(pid==0){
	  printf("sono il figlio\n");
	  printf("il mio pid è %d, mentre quello di mio padre è %d\n",pid,getppid());
	}
	else{
	  printf("sono il padre\n");
	  printf("il mio pid è %d, mentre quello di mio figlio è %d, invece quello di mio padre è %d\n",getpid(),pid,getppid());
	}
	
	printf("e faccio il mio lavoro\n");
}
