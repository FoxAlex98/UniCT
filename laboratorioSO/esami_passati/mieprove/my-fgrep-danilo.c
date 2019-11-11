//Danilo Santitto X81000689

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<ctype.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>

#define SIZE 1024

void reader(int pipefd, FILE* f){
	FILE* pipos = fdopen(pipefd, "w");

	char line[SIZE];

	while(fgets(line, SIZE, f) != NULL)
		fputs(line, pipos);

	fclose(f);
	printf("reader\n");
	exit(0);
}

void filterer(int pipefd, int fifofd, const char* word, const bool selI, const bool selV){
	FILE* fifos = fdopen(fifofd, "w");
	FILE* pipos = fdopen(pipefd, "r");

	char line[SIZE];
	bool found;
	while(fgets(line, SIZE, pipos) != NULL){
		found = false;
		if(strstr(line, word) != NULL)
			found = true;

		if((!selV && found) || (selV && !found))
			fputs(line, fifos);
	}

	printf("filterer\n");
	exit(0);
}

void writer(int fifofd){

	char line[SIZE];
	FILE* fifos = fdopen(fifofd, "r");

	while(fgets(line, SIZE, fifos) != NULL)
		printf("%s", line);		
	

	printf("writer\n");
	exit(0);
}

int main(int argc, char const *argv[]){
	bool selI = false;
	bool selV = false;
	char word[SIZE];
	int pipefd[2];
	int fifofd;
	FILE* file;
	struct stat buff;
	char fifoPath[] = "./mkfifo";

	remove(fifoPath);

	stat(argv[argc-1], &buff);
	if(S_ISREG(buff.st_mode)){
		if((file = fopen(argv[argc -1], "r")) == NULL){
			perror("openFile");
			exit(1);
		}
		strcpy(word, argv[argc - 2]);
	}
	else{
		file = stdin;		
		strcpy(word, argv[argc - 1]);
	}

	for(int i = 1; i < argc - 1; i++){
		if(strcmp(argv[i],"-i") == 0)  
			selI = true;
		else if(strcmp(argv[i],"-v") == 0)
			selV = true;
	}

	if(pipe(pipefd) == -1){
		perror("pipe");
		exit(1);
	}

	if((fifofd = mkfifo(fifoPath, 0700)) == -1){
		perror("fifo");
		exit(1);
	}


	if(fork() == 0){
		close(pipefd[0]);
		reader(pipefd[1], file);
	} 
	if(fork() == 0){
		close(pipefd[1]);
		filterer(pipefd[0], fifofd, word, selI, selV);
	}

    close(pipefd[0]);
    close(pipefd[1]);

	if(fork() == 0) writer(fifofd);


	wait(NULL);
	wait(NULL);
	wait(NULL);

	close(fifofd);

	exit(0);
}