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
    int num;

    printf("Custom File System Program\n");

    while (1) {
        printf(">> ");
        fgets(command, BUFFER_SIZE, stdin);

        if (strncmp(command, "salir", 5) == 0) {
            break;
        }

        if (sscanf(command, "crearArchivo %s", arg1) == 1) {
            crearArchivo(arg1);
        } else if (sscanf(command, "escribirArchivo %s", arg1) == 1) {
            escribirArchivo(arg1);
        } else if (sscanf(command, "borrarArchivo %s", arg1) == 1) {
            borrarArchivo(arg1);
        } else if (sscanf(command, "mostrarArchivo %s %d", arg1, &num) == 2) {
            mostrarArchivo(arg1, atoi(arg2));
        } else if (sscanf(command, "renombrarArchivo %s %s", arg1, arg2) == 2) {
            renombrarArchivo(arg1, arg2);
        } else if (sscanf(command, "crearDirectorio %s", arg1) == 1) {
            crearDirectorio(arg1);
        } else if (strncmp(command, "mostrarDirectorio", 17) == 0) {
            int detailed = strstr(command, "-l") != NULL;
            if (sscanf(command, "mostrarDirectorio %s", arg1) == 1) {
                mostrarDirectorio(arg1, detailed);
            } else {
                mostrarDirectorio(".", detailed);
            }
        } else if (sscanf(command, "borrarDirectorio %s", arg1) == 1) {
            borrarDirectorio(arg1);
        } else if (sscanf(command, "renombrarDirectorio %s %s", arg1, arg2) == 2) {
            renombrarDirectorio(arg1, arg2);
        } else {
            printf("Unknown command: %s", command);
        }
    }

    return 0;
}

// Function definitions

void crearArchivo(const char *path) {
    int fd = open(path, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return;
    }
    close(fd);
}

void escribirArchivo(const char *path) {
    int fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error opening file for writing");
        return;
    }

    char buffer[BUFFER_SIZE];
    while (1) {
        printf("Enter text (type 'FIN' to end): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strncmp(buffer, "FIN", 3) == 0) break;
        write(fd, buffer, strlen(buffer));
    }
    close(fd);
}

void borrarArchivo(const char *path) {
    if (unlink(path) == -1) {
        perror("Error deleting file");
    }
}

void mostrarArchivo(const char *path, int position) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    lseek(fd, position, SEEK_SET);

    char buffer[BUFFER_SIZE];
    int bytesRead;
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    close(fd);
}

void renombrarArchivo(const char *oldPath, const char *newPath) {
    if (rename(oldPath, newPath) == -1) {
        perror("Error renaming file");
    }
}

void crearDirectorio(const char *path) {
    if (mkdir(path, 0755) == -1) {
        perror("Error creating directory");
    }
}

void mostrarDirectorio(const char *path, int detailed) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (detailed) {
            struct stat statbuf;
            if (stat(entry->d_name, &statbuf) == -1) {
                perror("Error getting file stats");
                continue;
            }
            printf("Name: %s Size: %lld\n", entry->d_name, (long long)statbuf.st_size);
        } else {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}

void borrarDirectorio(const char *path) {
    if (rmdir(path) == -1) {
        perror("Error deleting directory");
    }
}

void renombrarDirectorio(const char *oldPath, const char *newPath) {
    if (rename(oldPath, newPath) == -1) {
        perror("Error renaming directory");
    }
}
