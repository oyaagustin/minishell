#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char* expand_home(const char *path) {
    char *expanded;
    
    if (path[0] == '~') {
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "No se pudo obtener el directorio home \n");
            return NULL;
        }
        expanded = malloc(strlen(home) + strlen(path));
        if (expanded == NULL) {
            perror("Error al alocar memoria");
            return NULL;
        }
        snprintf(expanded, strlen(home) + strlen(path) + 1, "%s%s", home, path + 1);
    } else {
        expanded = malloc(strlen(path) + 1);
        if (expanded == NULL) {
            perror("Error de asignación de memoria");
            return NULL;
        }
        strcpy(expanded, path);
    }
    return expanded;
}
