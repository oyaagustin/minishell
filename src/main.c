#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

int main() {
    char *comando = NULL;
    size_t len = 0;

    printf("Mini-shell Sistemas Operativos 2024 \n");

    while (1) {
        printf("\nEscriba \"help\" para conocer los comandos disponibles o \"exit\" para salir \n\n");
        getline(&comando, &len, stdin);
        comando[strcspn(comando, "\n")] = 0;  // Remover el salto de línea

        if (strcmp(comando, "exit") == 0) {
            free(comando);
            break;
        }

        // Calcular el tamaño necesario para la ruta
        size_t ruta_len = strlen("./src/") + strlen(comando) + 1;
        char *ruta = malloc(ruta_len);
        if (!ruta) {
            perror("malloc");
            free(comando);
            exit(EXIT_FAILURE);
        }

        // Construir la ruta completa
        strcpy(ruta, "./");
        strcat(ruta, comando);

        // Crear un proceso hijo para ejecutar el comando con execv
        pid_t pid = fork();
        if (pid == 0) {
            char *args[] = {ruta, NULL};
            execv(ruta, args);
            printf("%s",ruta);
            perror("execv");
            exit(EXIT_FAILURE);
        } 
        else if (pid > 0) {
            wait(NULL);
        } 
        else {
            perror("fork");
        }

        // Limpiar la memoria
        free(ruta);
        free(comando);
        comando = NULL;
    }

    return 0;
}
