#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void read_file(char *fileName){
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error al crear el proceso read");
        return;
    }

    if (pid == 0) {
        // Proceso hijo ejecuta 'cat' para mostrar el contenido del archivo
        execlp("cat", "cat", fileName, (char *)NULL);
        perror("Error al intentar leer el archivo");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
   
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: Uso incorrecto de read_file. Formato: read_file <ruta de archivo>\n");
        return 1;
    }

    char *fileName = argv[1];  // El primer argumento es el nombre del archivo
    read_file(fileName);
    
    return 0;
}
