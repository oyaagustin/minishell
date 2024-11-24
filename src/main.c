#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

#define COMMANDS_DIR "./"  // Changed from "./bin/" since we're already in the bin directory when running

int main() {
    char *input = NULL;
    size_t len = 0;
    ssize_t read;

    printf("Mini-shell Sistemas Operativos 2024 \n");

    while (1) {
        printf("\nEscriba \"help\" para conocer los comandos disponibles o \"exit\" para salir \n\n");
        
        read = getline(&input, &len, stdin);
        if (read == -1) {
            perror("Error reading input");
            continue;
        }

        input[strcspn(input, "\n")] = 0;  // Remover el salto de línea

        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Separar el comando de la ruta
        char *comando = strtok(input, " ");
        if (comando == NULL) {
            continue;  // Skip empty input
        }

        char *ruta = NULL;
        char *ruta_temp = strtok(NULL, "");
        if (ruta_temp != NULL) {
            ruta = expand_home(ruta_temp);
            if (ruta == NULL) {
                fprintf(stderr, "Error expanding home path\n");
                continue;
            }
        }
        
        char *comando_dir = expand_command_path(comando, COMMANDS_DIR);
        if (comando_dir == NULL) {
            fprintf(stderr, "Error expanding command path\n");
            free(ruta);
            continue;
        }
        
        // Crear un proceso hijo para ejecutar el comando con execv
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            char *args[] = {comando_dir, ruta, NULL};
            execv(comando_dir, args);
            perror("Error al ejecutar el comando");
            exit(EXIT_FAILURE);
        } 
        else if (pid > 0) {
            // Parent process
            wait(NULL);
        } 
        else {
            perror("Error al crear el proceso");
        }

        // Free allocated memory
        free(ruta);
        free(comando_dir);
    }

    free(input);  // Free input buffer
    return 0;
}
