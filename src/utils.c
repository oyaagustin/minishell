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
            perror("Error de asignación de memoria");
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

char* expand_command_path(const char* command, const char *commands_dir) {
    size_t dir_len = strlen(commands_dir);
    size_t command_len = strlen(command);
    char* command_path = malloc(dir_len + command_len + 1);
    
    if (command_path == NULL) {
        perror("Error de asignación de memoria");
        return NULL;
    }
    
    strcpy(command_path, commands_dir);
    strcat(command_path, command);
    return command_path;
}

