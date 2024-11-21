#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "utils.h"

void list(char *dirName) {
    //Expansión del directorio home
    char *expanded;
    if (strlen(dirName) == 0) {
        expanded = expand_home("~");
    } else {
        expanded = malloc(strlen(dirName) + 1);
        if (expanded == NULL) {
            perror("Error al asignar memoria en lista");
            return;
        }
        strcpy(expanded, dirName);
    }

    if (expanded == NULL) return;
    
    //Utilización de dirent para listar el contenido del directorio
    DIR *dir = opendir(expanded);
    if (dir == NULL) {
        perror("No se pudo abrir el directorio");
        free(expanded);
        return;
    }

    struct dirent *content;
    while ((content = readdir(dir)) != NULL) {
        if (strcmp(content->d_name, ".") == 0 || strcmp(content->d_name, "..") == 0){
            continue;
        }
        printf("- %s\n", content->d_name);
    }

    if (closedir(dir) != 0) {
        perror("Error al cerrar el directorio");
    }
    
    free(expanded);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <directorio>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *dirName = argv[1];

    list(dirName);

    return 0;
}
