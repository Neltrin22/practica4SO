#include <stdio.h>
#include "dataset.h"
#include "model.h"

// Declaraciones de funciones externas
extern int load_dataset(const char *filename, Sample samples[], int max_samples);
void train_model(Sample samples[], int n, NaiveBayesModel *model);
void save_model(const char *filename, NaiveBayesModel *model);

int main() {
    Sample samples[1000];
    int n = load_dataset("features/combined.csv", samples, 1000);

    if (n < 0) {
        return 1;
    }

    printf("Se leyeron %d muestras\n", n);

    NaiveBayesModel model;
    train_model(samples, n, &model);
    save_model("model.dat", &model);

    printf("Modelo entrenado y guardado en model.dat\n");
    return 0;
}
