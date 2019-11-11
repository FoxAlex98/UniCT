#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <dirent.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define PADRE 1
#define ANALYZER 2
#define SIZE 1024

typedef struct {
	long type;
	char mex[SIZE];
} path;

typedef struct {
	long type;
	int val;
} value;


//scansiona ricorsivamente le cartelle
void Scanner(const char *s, int coda)//mettiamo s come costante, cosi evitiamo di sporcarla
{
	DIR *dir;
	struct dirent *a;
	struct stat buff;
	path mex;
	dir = opendir(s);
	while ((a = readdir(dir)) != NULL) {//leggiamo il contenuto della cartella spostandoci ogni volta, finchè non ne troviamo una
		if (strcmp(a->d_name, ".") == 0 || strcmp(a->d_name, "..") == 0)//escludiamo la cartella stessa e la cartella padre
			continue;

			char m[SIZE];
			strcpy(m, s);
			strcat(m, "/");
			strcat(m, a->d_name);

		if (stat(m, &buff) == -1)//controlliamo lo stato di m, scrivendo i risultati sul buff
			perror("stat");

		if (S_ISDIR(buff.st_mode))//controlliamo se buff(m) è una cartella
			Scanner(m, coda);//se lo è, richiamiamo ricorsivamente lo scanner
		else if (S_ISREG(buff.st_mode)) {//altrimenti controlliamo se è un file regolare
			printf("Scanner: %s\n", a->d_name);//allora iniziamo la "Scansione"
			mex.type = ANALYZER;//segnaliamo che questo tipo di messaggio deve essere trattato dall'ANALYZER
			strcpy(mex.mex, m);//copiamo il percorso in mex
			msgsnd(coda, &mex, sizeof(mex) - sizeof(long), 0);//e mandiamolo alla coda
		}
	}
	mex.type = ANALYZER;//fine del file
	strcpy(mex.mex, "fine");//lo mandiamo, cosi l'analyzer si ferma
	msgsnd(coda, &mex, sizeof(mex) - sizeof(long), 0);
	exit(0);
}

void Analyzer(int coda)
{
	path mex;
	value cnt;
	char *t;
	int file;
	struct stat buf;
	int flag = 1;
	while (flag) {
		msgrcv(coda, &mex, sizeof(path) - sizeof(long), ANALYZER, 0);//riceviamo i messaggi della coda

		if (!strcmp(mex.mex, "fine")) {//ci fermiamo quando troviamo il messaggio di fine
			flag = 0;
			continue;
		}

		if ((file = open(mex.mex, O_RDONLY)) == -1)	{//apriamo il file
			perror("open");
			exit(1);
		}

		fstat(file, &buf);//controlliamo lo stato del file
		if ((t = (char *)mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, file, 0)) == MAP_FAILED) {//mappiamo la parte di memoria
			perror("mmap");
			exit(1);
		}
		close(file);//chiudiamo il file

		int count = 0;//contatore per i caratteri dell'alfabeto
		int i = 0;
		while (i++ < buf.st_size) {//scorriamo tutto il file
			if (tolower(t[i]) >= 'a' && tolower(t[i]) <= 'z')//usiamo il tolower per unificare i casi di maiuscole e minuscole
				count++;
		}
		printf("Analyzer: %s %d\n", mex.mex, count);//mostriamo il conto dei caratteri

		cnt.type = PADRE;//prepariamo il messaggio per il padre
		cnt.val = count;
		msgsnd(coda, &cnt, sizeof(cnt) - sizeof(long), 0);//passiamo i dati alla coda

		if (munmap(NULL, buf.st_size) == -1) {//togliamo la mappatura
			perror("munmap");
			exit(1);
		}
	}

	cnt.type = PADRE;
	cnt.val = -1;//finale
	msgsnd(coda, &cnt, sizeof(cnt) - sizeof(long), 0);
	exit(0);
}

int main(int argc, char *argv[])
{
	int coda;
	struct stat buff;
	char path[SIZE];

	//controllo argomenti
	if (argc != 2 && argc != 1)	{
		printf("numero di argomenti sbagliato");
		exit(0);
	}

	if (argc == 1)
		strcpy(path, "./");//se non c'è niente come secondo argomento, usiamo la cartella stessa
	else
		strcpy(path, argv[1]);

	if (stat(path, &buff) == -1) {//controlliamo lo stato del percorso
		perror("stat");
		exit(1);
	};

	if (!S_ISDIR(buff.st_mode))	{//porta ad una cartella?
		printf("numero di argomenti sbagliato");
		exit(0);
	}

	//creiamo la coda
	if ((coda = msgget(IPC_PRIVATE, IPC_CREAT | 0660)) == -1) {
		perror("msgget");
		exit(1);
	};

	if (fork() == 0)
		Scanner(argv[1], coda);//primo figlio si occupa dello scanner
	if (fork() == 0)
		Analyzer(coda);//secondo figlio si occupa del analyzer

	//operazioni del padre
	value mex;
	int tot = 0;
	int flag = 1;
	while (flag) {
		msgrcv(coda, &mex, sizeof(path) - sizeof(long), PADRE, 0);//leggiamo i messaggi dalla coda
		if(mex.val == -1) flag = 0;//finchè non troviamo il finale
		else tot += mex.val;
	}
	printf("Padre: totale di %d caratteri alfabetici\n", tot);//conteggio totale

	//chiudiamo la coda
	if (msgctl(coda, IPC_RMID, NULL) == -1)	{
		perror("coda");
		exit(1);
	}
}
