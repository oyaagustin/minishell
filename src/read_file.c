#include <stdio.h>
#include <stdlib.h>

void read_file(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        printf("%s", line);
    }

    free(line);
    if (fclose(file) != 0) {
        perror("Error al cerrar el archivo");
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
