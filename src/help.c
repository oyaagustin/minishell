#include <stdio.h>

void help() {
    printf("\n\nComandos disponibles: \n\n");
    printf("help     - Muestra esta ayuda. \n\n");
    printf("crtdir   - Crea un directorio \n\t* crtdir <ruta de archivo>\n\n");
    printf("crtfile  - Crea un archivo \n\t* crtfile <ruta de archivo>\n\n");
    printf("delete   - Elimina un directorio o archivo\n\t* delete <ruta de archivo>\n");
    printf("        * Puede eliminar carpetas con archivos dentro por lo que se debe tener cuidado a la hora de confirmar \n\n");
    printf("list     - Lista el contenido de un directorio \n\t* list <ruta de archivo>\n\n");
    printf("read     - Muestra el contenido de un archivo \n\t* read <ruta de archivo>\n\n");
    printf("mod      - Modifica permisos de lectura, escritura y ejecución de un archivo \n");
    printf("        * mod <ruta de archivo>, <modo octal>\n");
    printf("        * Ejemplo: mod ~/archivo.txt, 755\n");
    printf("        * Donde el primer dígito son permisos de usuario, el segundo permisos de grupo y el tercero permisos de otros usuarios \n");
    printf("        * Los números son: 4 para lectura, 2 para escritura y 1 para ejecución \n");
    printf("        * Mediante la suma de números es posible otorgar más permisos, ej: 7 garantiza todos los permisos \n\n");
    printf("exit     - Cierra la mini-shell \n\n");
}

int main(){
    help();
}
