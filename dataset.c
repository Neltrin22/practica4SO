#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"

#define MAX_SAMPLES 1000
#define LINE_LENGTH 512

int load_dataset(const char *filename, Sample samples[], int max_samples) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error abriendo el archivo CSV");
        return -1;
    }

    char line[LINE_LENGTH];
    int count = 0;

    // NO saltes encabezado si temp_sample.csv no lo tiene
    // fgets(line, LINE_LENGTH, fp); // Descomenta solo si hay encabezado

    while (fgets(line, LINE_LENGTH, fp) && count < max_samples) {
        printf("DEBUG leyendo línea: %s", line); // mostrar línea cruda

        char *token;
        int col = 0;

        Sample s = {0};
        token = strtok(line, ",");

        while (token != NULL) {
            printf("DEBUG col[%d]: %s\n", col, token);
            switch (col) {
                case 0:
                    strncpy(s.filename, token, sizeof(s.filename));
                    s.filename[sizeof(s.filename) - 1] = '\0';
                    break;
                case 1: s.has_shell = atoi(token); break;
                case 2: s.has_socket = atoi(token); break;
                case 3: s.num_strings = atoi(token); break;
                case 4: s.exec_size = atoi(token); break;
                case 5: s.entropy = atof(token); break;
                case 6:
                    if (token[0] == '?') {
                        s.label = -1;
                    } else {
                        s.label = atoi(token);
                    }
                    break;
            }
            token = strtok(NULL, ",");
            col++;
        }

        printf("DEBUG columnas procesadas: %d\n", col);

        if (col >= 7) {
            samples[count++] = s;
            printf("✅ muestra agregada: %s\n", s.filename);
        } else {
            fprintf(stderr, "⚠ Línea inválida (col=%d): %s", col, line);
        }
    }

    fclose(fp);
    printf("DEBUG total muestras cargadas: %d\n", count);
    return count;
}
