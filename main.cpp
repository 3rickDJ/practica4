#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define BUFFER_SIZE 1024

void crearArchivo(const char *path);
void escribirArchivo(const char *path);
void borrarArchivo(const char *path);
void mostrarArchivo(const char *path, int position);
void renombrarArchivo(const char *oldPath, const char *newPath);

void crearDirectorio(const char *path);
void mostrarDirectorio(const char *path, int detailed);
void borrarDirectorio(const char *path);
void renombrarDirectorio(const char *oldPath, const char *newPath);

int main() {
    char command[BUFFER_SIZE];
    char arg1[BUFFER_SIZE], arg2[BUFFER_SIZE], arg3[BUFFER_SIZE];

    printf("Custom File System Program\n");
    while(1) {
        printf(">> ");
        fgets(command, BUFFER_SIZE, stdin);
        if(strncmp(command, "salir", 5) == 0 ) {
            break;
        }
        if (sscanf(command, "crearArchivo %s", arg1) == 1) {
            crearArchivo(arg1);
        }
        else if (sscanf(command, "escribirArchivo %s", arg1) == 1) {
            escribirArchivo(arg1);
        }
        else if (sscanf(command, "borrarArchivo %s", arg1) == 1) {
            borrarArchivo(arg1);
        }
        else if (sscanf(command, "mostrarArchivo %s %d", arg1, &arg2) == 2) {
            mostrarArchivo(arg1, atoi(arg2));
        }
        else if (sscanf(command, "renombrarArchivo %s %s", arg1, arg2) == 2) {
            renombrarArchivo(arg1, arg2);
        }
        else if (sscanf(command, "crearDirectorio %s", arg1) == 1) {
            crearDirectorio(arg1);
        }
        else if (sscanf(command, "mostrarDirectorio", 17) == 0) {
            int detailed = strstr(command, "-l") != NULL;
            if (sscanf(command, "mostrarDirectorio %s", arg1) == 1 {
                    mostrarDirectorio(arg1, detailed);
                    } else {
                    mostrarDirectorio(".", detailed);
                    }
        }
        else if (sscanf(command, "borrarDirectorio %s", arg1) == 1){
            borrarDirectorio(arg1);
        }
        else if (sscanf(command, "renombrarDirectorio %s %s", arg1, arg2) == 2){
            renombrarDirectorio(arg1, arg2);
        } else {
            printf("Unknown command: %s", command);
        }
    }
    return 0;
}


void crearArchivo(const char *path){
    int df = open(path, O_CREAT | O_WRONLY, 0644)
}
void escribirArchivo(const char *path);
void borrarArchivo(const char *path);
void mostrarArchivo(const char *path, int position);
void renombrarArchivo(const char *oldPath, const char *newPath);

void crearDirectorio(const char *path);
void mostrarDirectorio(const char *path, int detailed);
void borrarDirectorio(const char *path);
void renombrarDirectorio(const char *oldPath, const char *newPath);
