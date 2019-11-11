/*
    Homework n.5

    Estendere l'esempio 'nanoshell.c' ad una shell piu' realistica in cui
    si possono:
    - passare argomenti al comando invocato (per semplicita', assumiamo
    che questi non contengano spazi);
    - usare la redirezione dei canali di input/output/error;
    - mandare un comando in esecuzione in background (con la '&' finale).

    Esempi di invocazione che la shell dovrebbe supportare sono:
    $ cal 3 2015
    $ cp /etc/passwd /etc/hosts /tmp
    $ cat </dev/passwd >/tmp/passwd
    $ cat filechenonesiste 2>/dev/null
    $ ls -R /etc/ &
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LEN_BUFFER 2048
#define DELIM   " "
#define MAX_ARGS 30

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main(int argc, char *argv[]) {
    char commandline[LEN_BUFFER];
    int pid, len, i, fd;
    char *token;
    char *args[MAX_ARGS];
    char bckg_exec;
    char *path_stdout, *path_stdin, *path_stderr;

    while (1) {
        printf("> ");
        fgets(commandline, LEN_BUFFER, stdin);
        len = strlen(commandline);
        if ( commandline[len-1] == '\n')
            commandline[len-1] = '\0';

        if ((strcmp(commandline, "exit") == 0) || (strcmp(commandline, "quit") == 0))
            break;

        if ((token = strtok(commandline, DELIM)) == NULL) {
            fprintf(stderr, "la riga di comando sembra malformata!\n");
            continue;
        }
        i = 0;
        bckg_exec = 0;
        path_stdout = path_stdin = path_stderr = NULL;
        do {
            /* controlla se si tratta del simbolo '&' che indica una esecuzione
               in background del comando  */
            if ((strlen(token) == 1) && token[0] == '&') {
                bckg_exec = 1;
                continue;
            }

            /* controlla se si tratta di una redirezione dei canali */
            if (token[0] == '<') {
                if (path_stdin == NULL) {
                    path_stdin = strdup(token+1);
                    if (!access(path_stdin, R_OK)) {
                        fprintf(stderr, "impossibile accedere in lettura al file specificato come standard input!\n");
                        free(path_stdin);
                        continue;
                    }
                } else {
                    fprintf(stderr, "doppia redirezione dello standard input!\n");
                    continue;
                }
                continue;
                /* TO FIX: sintassi inesatta, qui implementa '>2' piuttosto che '2>' */
            } else if (token[0] == '>') {
                if (token[1] == '2') {
                    if (path_stderr == NULL) {
                        path_stderr = strdup(token+2);
                    } else {
                        fprintf(stderr, "doppia redirezione dello standard error!\n");
                        continue;
                    }
                } else {
                    if (path_stdout == NULL) {
                        path_stdout = strdup(token+1);
                    } else {
                        fprintf(stderr, "doppia redirezione dello standard output!\n");
                        continue;
                    }
                }
                continue;
            }

            args[i++] = strdup(token);
        } while ((token = strtok(NULL, DELIM)) != NULL);
        args[i] = NULL;

        pid = fork();

        if ( pid == -1 ) {
            perror("fork");
            exit(1);
        }
        if ( pid == 0 ) {
            /* applica l'eventuale redirezione dei canali nel figlio */
            if (path_stdin != NULL) {
                fd = open(path_stdin, O_RDONLY);
                close(STDIN);
                dup(fd);
            }
            if (path_stderr != NULL) {
                fd = open(path_stderr, O_WRONLY|O_CREAT|O_TRUNC, 0666);
                close(STDERR);
                dup(fd);
            }
            if (path_stdout != NULL) {
                fd = open(path_stdout, O_WRONLY|O_CREAT|O_TRUNC, 0666);
                close(STDOUT);
                dup(fd);
            }

            execvp(args[0], args);
            fprintf(stderr, "Errore nell'esecuzione di '%s'\n", args[0]);
            exit (2);
        } else if (!bckg_exec)
            wait(NULL);

        /* libero la memoria allocata dinamicamente nel padre */
        if (path_stdin != NULL) free(path_stdin);
        if (path_stderr != NULL) free(path_stderr);
        if (path_stdout != NULL) free(path_stdout);
        i = 0;
        while (args[i] != NULL)
            free(args[i++]);
    }
    exit(0);
}

