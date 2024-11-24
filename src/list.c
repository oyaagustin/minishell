#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "utils.h"

void list(char *dirName) {
    // Utilización de dirent para listar el contenido del directorio
    DIR *dir = opendir(dirName);
    if (dir == NULL) {
        perror("No se pudo abrir el directorio");
        return;
    }

    struct dirent *content;
    while ((content = readdir(dir)) != NULL) {
        if (strcmp(content->d_name, ".") == 0 || strcmp(content->d_name, "..") == 0) {
            continue;
        }
        printf("- %s\n", content->d_name);
    }

    if (closedir(dir) != 0) {
        perror("Error al cerrar el directorio");
    }
}

int main(int argc, char *argv[]) {
    char *dirName = (argc < 2) ? expand_home("~") : argv[1]; //Si la ruta está vacía entonces utiliza el directorio home

    list(dirName);

    if (argc < 2) {
        free(dirName); 
    }
    
    return 0;
}
