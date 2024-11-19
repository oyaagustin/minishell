#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void crtfile(char *fileName) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error en el proceso crtfile");
        return;
    }

    if (pid == 0) {
        execlp("touch", "touch", fileName, (char *)NULL);
        perror("Error al intentar crear el archivo");
        exit(EXIT_FAILURE); 
    } else {
        wait(NULL);
        printf("Archivo '%s' creado con éxito.\n", fileName);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: Uso incorrecto de crtfile. Formato: crtfile <ruta de archivo>\n");
        return 1;
    }

    char *fileName = argv[1];
    crtfile(fileName);
    return 0;
}
