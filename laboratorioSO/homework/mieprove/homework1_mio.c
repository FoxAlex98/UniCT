/*
    Homework n.1

    Scrivere un programma in linguaggio C che permetta di copiare un numero
    arbitrario di file regolari su una directory di destinazione preesistente.

    Il programma dovra' accettare una sintassi del tipo:
     $ homework-1 file1.txt path/file2.txt "nome con spazi.pdf" directory-destinazione
*/


#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFSIZE 4096
#define MODE 0660

void controlloiniziale(int argc){
	if(argc==1)
	   printf("devi mettere minimo 2 argomenti, ovvero la sorgente e la destinazione\n");
	else if(argc==2)
		printf("devi inserire anche la sorgente/destinazione\n");
	if(argc>2) return;
	   exit(1);
}

int main(int argc, char *argv[])
{
  int sd,dd,size;
  char buffer[BUFSIZE];
  char *p1,*p2;

  controlloiniziale(argc);
  //printf("%s\n%s\n%s\n",argv[0],argv[1],argv[2]);
  for(int i=1;i<argc-1;i++){
	printf("carico il file ");
	printf("%s\t--> ", argv[i]);
	if((sd=open(argv[i],O_RDONLY))==-1){
		printf("aspe, c'è qualcosa che non va\n");
		perror(argv[i]);
		exit(1);
	}

  	strncpy(buffer,argv[argc-1],BUFSIZE);
	size=strlen(buffer);
	strncpy(buffer+size,"/",BUFSIZE-size);
	size++;
	
	p1=p2=argv[i];
	while(*p2!='\0'){
	 if(*p2=='/') p1=p2+1;
		p2++;	
	}
	strncpy(buffer + size, p1, BUFSIZE - size);

	printf("%s\n", buffer);
	if((dd=open(buffer, O_WRONLY|O_CREAT|O_TRUNC, MODE))==-1){
	 perror(buffer);
	 exit(1);
	}

	do {
            // legge fino ad un massimo di BUFSIZE byte dalla sorgente
            if ((size = read(sd, buffer, BUFSIZE)) == -1) {
                perror(argv[1]);
                exit(1);
            }
            // scrive i byte letti
            if (write(dd, buffer, size) == -1) {
                perror(argv[2]);
                exit(1);
            }
        } while (size == BUFSIZE);

	close(sd);
	close(dd);	
	
  }


}
