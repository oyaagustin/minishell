#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void mod(char *params) {
    char *filePath = strtok(params, " ");
    if (filePath == NULL) {
        printf("ERROR: Uso incorrecto de mod. Formato: mod <ruta de archivo> <modo octal>\n");
        return;
    }

    char *modeStr = strtok(NULL, " ");
    if (modeStr == NULL) {
        printf("ERROR: Uso incorrecto de mod. Formato: mod <ruta de archivo> <modo octal>\n");
        return;
    }
    int mode = strtol(modeStr, NULL, 8);

    if (chmod(filePath, mode) == 0) {
        printf("Permisos de '%s' modificados exitosamente a %o.\n", filePath, mode);
    } else {
        perror("Error al modificar los permisos \n");
    }

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: Uso incorrecto de mod. Formato: mod <ruta de archivo> <modo octal>\n");
        return 1;
    }

    char *args = argv[1];  // El primer argumento es la ruta del archivo

    mod(args);

    return 0;
}
