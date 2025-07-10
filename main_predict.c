#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
#include "model.h"
#include "predict.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s archivo_a_analizar\n", argv[0]);
        return 1;
    }

    // Ejecutar el script de extracción
    char command[256];
    snprintf(command, sizeof(command), "./scripts/extract_sample.sh %s", argv[1]);
    system(command);

    // Cargar la muestra
    Sample s;
    Sample temp_samples[1];
    if (load_dataset("features/temp_sample.csv", temp_samples, 1) <= 0) {
        fprintf(stderr, "No se pudo cargar la muestra\n");
        return 1;
    }
    s = temp_samples[0];

    // Cargar el modelo
    NaiveBayesModel model;
    if (load_model("model.dat", &model) != 0) {
        return 1;
    }

    // Predecir
    int result = predict(&model, &s);
    printf("El archivo '%s' fue clasificado como: %s\n", s.filename,
           result ? "MALICIOSO ❌" : "BENIGNO ✅");

    return 0;
}
