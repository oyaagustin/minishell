#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void crtfile(char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) { 
        perror("Error al crear el archivo");
        return;
    }
    fclose(file); 
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
