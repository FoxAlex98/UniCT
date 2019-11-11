//x8100681 alessandro sorbello

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/wait.h>


#define BUFFER 1024


void reader(int pipa, FILE* filef){//pipe e stream del file
	char s[BUFFER];

	FILE* fpipa;

	fpipa = fdopen(pipa, "w");

	while((fgets(s, BUFFER, filef)) != NULL){
		fputs(s, fpipa);
	}

	//fclose(filef);

	exit(0);
}


void filtered(int pipa, int fifa, char* word, bool flag_I, bool flag_V){
	char str[BUFFER];

	FILE* fpipa;
	FILE* ffifa;

	fpipa = fdopen(pipa, "r");
	ffifa = fdopen(fifa, "w");

	while((fgets(str, BUFFER, fpipa)) != NULL){
		
		if(strstr(str,word) != NULL)
			fputs(str, ffifa);
	}
	

	exit(0);
}


void writer(int fifa){
	char str[BUFFER];

	FILE* ffifa;

	ffifa = fdopen(fifa, "r");

	while((fgets(str, BUFFER, ffifa)) != NULL){
		printf("ciao %s\n", str);
	}

	exit(0);
}


int main(int argc, char const *argv[])
{
	bool flag_I,flag_V,flag_F;
	struct stat buff;
	flag_V = flag_I = flag_F = false;
	int pipa[2];
	int fifa;
	FILE* file_des;
	char word[BUFFER];

	remove("./fifa");


	//controllo parametri
	if(argc < 2){
		printf("devono esserci minimo 2 parametri\n");
		exit(0);
	}

	//controllo varianti -i e -v
	for(int i = 1; i < argc-1; i++){
		if(strcmp(argv[i], "-i") == 0)
		flag_I = true;
		else if(strcmp(argv[i], "-v") == 0)
		flag_V = true;	
	}

	if((stat(argv[argc-1], &buff)) != -1 && (S_ISREG(buff.st_mode))){
		flag_F = true;
	}

	if(flag_F){
		file_des = fopen(argv[argc-1], "r");
		strcpy(word,argv[argc-2]);
	}
	else{
		file_des = stdin;
		strcpy(word,argv[argc-1]);
	}

	if(pipe(pipa) == -1){
		perror("pipe");
		exit(1);
	}

	if((fifa = mkfifo("./fifa", 0600)) == -1){
		perror("FIFO");
		exit(1);
	}	



	if(fork() == 0){
		close(pipa[0]);
		reader(pipa[1], file_des);
	}		
	if(fork() == 0){
		close(pipa[1]);
		filtered(pipa[0], fifa, word, flag_I, flag_V);
	}		
		
	close(pipa[0]);
	close(pipa[1]);
	
	if(fork() == 0)
	{
		writer(fifa);
	}



	printf("cpu prematurata antani a destra\n");


	fclose(file_des);
	close(fifa);

	wait(NULL);
	wait(NULL);
	wait(NULL);
}