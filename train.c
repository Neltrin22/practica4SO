// file: train.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dataset.h"
#include "model.h"

void train_model(Sample samples[], int n, NaiveBayesModel *model) {
    int count[2] = {0, 0};

    // Acumuladores
    float sum_shell[2] = {0}, sum_socket[2] = {0};
    float sum_strings[2] = {0}, sum_sq_strings[2] = {0};
    float sum_size[2] = {0}, sum_sq_size[2] = {0};
    float sum_entropy[2] = {0}, sum_sq_entropy[2] = {0};

    // Contar muestras y acumular por clase
    for (int i = 0; i < n; i++) {
        int c = samples[i].label;

        if (c != 0 && c != 1) {
            fprintf(stderr, "⚠ Advertencia: muestra con clase inválida (%d), ignorada.\n", c);
            continue;
        }

        count[c]++;
        sum_shell[c] += samples[i].has_shell;
        sum_socket[c] += samples[i].has_socket;

        sum_strings[c] += samples[i].num_strings;
        sum_sq_strings[c] += samples[i].num_strings * samples[i].num_strings;

        sum_size[c] += samples[i].exec_size;
        sum_sq_size[c] += samples[i].exec_size * samples[i].exec_size;

        sum_entropy[c] += samples[i].entropy;
        sum_sq_entropy[c] += samples[i].entropy * samples[i].entropy;
    }

    printf("Cantidad de muestras:\n");
    printf(" - Clase 0 (benignos): %d\n", count[0]);
    printf(" - Clase 1 (maliciosos): %d\n", count[1]);

    int total = count[0] + count[1];
    if (total == 0) {
        fprintf(stderr, "❌ No hay datos válidos para entrenar.\n");
        exit(1);
    }

    model->prob_class[0] = (float)count[0] / total;
    model->prob_class[1] = (float)count[1] / total;

    // Calcular medias, desviaciones estándar y probabilidades por clase
    for (int c = 0; c <= 1; c++) {
        if (count[c] == 0) {
            fprintf(stderr, "❌ No hay suficientes muestras para la clase %d\n", c);
            exit(1);
        }

        model->prob_shell[c] = sum_shell[c] / count[c];
        model->prob_socket[c] = sum_socket[c] / count[c];

        model->mean_num_strings[c] = sum_strings[c] / count[c];
        model->stddev_num_strings[c] = sqrt((sum_sq_strings[c] / count[c]) - pow(model->mean_num_strings[c], 2));

        model->mean_exec_size[c] = sum_size[c] / count[c];
        model->stddev_exec_size[c] = sqrt((sum_sq_size[c] / count[c]) - pow(model->mean_exec_size[c], 2));

        model->mean_entropy[c] = sum_entropy[c] / count[c];
        model->stddev_entropy[c] = sqrt((sum_sq_entropy[c] / count[c]) - pow(model->mean_entropy[c], 2));
    }
}

void save_model(const char *filename, NaiveBayesModel *model) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("❌ No se pudo guardar el modelo");
        exit(1);
    }

    fwrite(model, sizeof(NaiveBayesModel), 1, fp);
    fclose(fp);
    printf("✅ Modelo guardado en: %s\n", filename);
}
