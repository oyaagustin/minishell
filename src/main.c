#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

// Función para extraer y expandir la ruta del comando
char* obtener_ruta(const char *comando, const char *prefijo) {
    const char *ruta_inicio = comando + strlen(prefijo);
    char *ruta_expandida = expand_home(ruta_inicio);
    return ruta_expandida;
}

int main() {
    char *comando = NULL;
    size_t len = 0;

    printf("Mini-shell Sistemas Operativos 2024 \n");

    while (1) {
        printf("\nEscriba \"help\" para conocer los comandos disponibles o \"exit\" para salir \n\n");
        getline(&comando, &len, stdin);
        comando[strcspn(comando, "\n")] = 0;

        if (strcmp(comando, "exit") == 0) {
            free(comando);
            break;
        }

        // Variables para almacenar el ejecutable y los argumentos
        int index = 0;
        char *args[3] = {NULL, NULL, NULL};  // args para execv

        if (strncmp(comando, "help", 4) == 0) {
            args[0] = "./help";
        }
        else if (strncmp(comando, "crtdir", 6) == 0) {
            args[0] = "./crtdir";
            index = 7;
        }
        else if (strncmp(comando, "crtfile", 7) == 0) {
            args[0] = "./src/crtfile";
            index = 8;
        }
        else if (strncmp(comando, "delete", 6) == 0) {
            args[0] = "./delete_file";
            index = 7;
        }
        else if (strncmp(comando, "list", 4) == 0) {
            args[0] = "./list";
            index = 5;
        }
        else if (strncmp(comando, "read", 4) == 0) {
            args[0] = "./read_file";
            index = 5;
        }
        else if (strncmp(comando, "mod", 3) == 0) {
            args[0] = "./mod";
            index = 4;
        } else {
            printf("Comando no reconocido\n\n");
            free(comando);
            comando = NULL;
            continue;
        }

        args[1] = expand_home(comando+index);

        // Crear un proceso hijo para ejecutar el comando con execv
        pid_t pid = fork();
        if (pid == 0) {
            execv(args[0], args);
            perror("execv"); 
            exit(EXIT_FAILURE);
            
        } 
        else if (pid > 0) {
            wait(NULL);
            free(args[1]);
        } 
        else {
            perror("fork");
        }

        free(comando);
        comando = NULL;
    }

    return 0;
}
