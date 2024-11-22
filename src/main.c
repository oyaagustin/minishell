#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

int main() {
    char *input = NULL;
    size_t len = 0;

    printf("Mini-shell Sistemas Operativos 2024 \n");

    while (1) {
        printf("\nEscriba \"help\" para conocer los comandos disponibles o \"exit\" para salir \n\n");
        getline(&input, &len, stdin);
        comando[strcspn(input, "\n")] = 0;  // Remover el salto de línea

        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // Separar el comando de la ruta (Completar)
        char *comando = strtok(input, " ");
        char *ruta = expand_home(strtok(NULL, "")); //Expande la ruta home

        // Crear un proceso hijo para ejecutar el comando con execv
        pid_t pid = fork();
        if (pid == 0) {
            char *args[] = {comando, ruta, NULL};
            execv(comando, args);
            perror("Error al cambiar la imagen: ");
            exit(EXIT_FAILURE);
        } 
        else if (pid > 0) {
            wait(NULL);
        } 
        else {
            perror("Error al crear el proceso: ");
        }

        free(input);
        input = NULL;
    }

    return 0;
}
