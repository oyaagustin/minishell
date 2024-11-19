#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void delete_file(char *dirName){

    if (dirName[0] == '\0') {
        printf("ERROR: parámetro de ruta vacío \n");
        return;
    }

    if (strcmp(dirName, getenv("HOME")) == 0) {
        printf("Error: ¿Por qué querrías eliminar el directorio home?\n");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error al crear el proceso delete");
        return;
    }

    if (pid == 0) {
        // Proceso hijo ejecuta 'rm' para eliminar el archivo o directorio
        execlp("rm", "rm", "-ri", dirName, (char *)NULL);
        perror("Error al intentar eliminar");
        exit(EXIT_FAILURE);
    } else {
        // Proceso padre espera a que el hijo termine
        wait(NULL);
        printf("\nOperación finalizada con éxito. \n");
    }

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: Uso incorrecto de delete. Formato: delete <ruta de archivo o directorio>\n");
        return 1;
    }

    char *dirName = argv[1];
    delete_file(dirName);
}
    
