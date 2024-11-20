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

    if (rmdir(dirName) == 0) {
        printf("El directorio '%s' fue eliminado exitosamente.\n", dirName);
    } else {
        perror("Error al intentar eliminar el directorio");
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: Uso incorrecto de delete. Formato: delete <ruta de archivo o directorio>\n");
        return 1;
    }

    char *dirName = argv[1];
    delete_file(dirName);
}
    
