#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

void list(char *dirName) {
    char *expanded;
    if (strlen(dirName) == 0) {
        expanded = expand_home("~");
    } else {
        expanded = malloc(strlen(dirName) + 1);
        if (expanded == NULL) {
            perror("Error al asignar memoria en lista");
            return;
        }
        strcpy(expanded, dirName);
    }

    if (expanded == NULL) return;

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error al crear el proceso hijo");
        free(expanded);
        return;
    }

    if (pid == 0) {
        // Preparamos los argumentos para execv
        char *args[] = {"ls", "-1", expanded, NULL}; // Lista de argumentos para el comando

        execv("/bin/ls", args); // Ruta absoluta de ls para usar execv
        perror("Error al ejecutar list");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }

    free(expanded);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <directorio>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *dirName = argv[1];

    list(dirName);

    return 0;
}
