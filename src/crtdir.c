#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void crtdir(char *dirName){
    if (mkdir(dirName, 0777) == 0) {
        printf("Directorio '%s' creado con éxito.\n", dirName);
    } else {
        perror("Error al crear el directorio");
    }

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: Uso incorrecto de crtdir. Formato: crtdir <ruta del directorio>\n");
        return 1;
    }

    char *dirName = argv[1];
    crtdir(dirName);
    return 0;
}
