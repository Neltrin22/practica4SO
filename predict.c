#include <stdio.h>
#include <math.h>
#include "predict.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int load_model(const char *filename, NaiveBayesModel *model) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error al cargar el modelo");
        return -1;
    }
    fread(model, sizeof(NaiveBayesModel), 1, fp);
    fclose(fp);
    return 0;
}

float gaussian_prob(float x, float mean, float stddev) {
    if (stddev == 0) return 1.0;
    float exponent = exp(-pow(x - mean, 2) / (2 * pow(stddev, 2)));
    return (1.0 / (sqrt(2 * M_PI) * stddev)) * exponent;
}

int predict(const NaiveBayesModel *model, Sample *s) {
    float log_prob[2];

    for (int c = 0; c < 2; c++) {
        log_prob[c] = log(model->prob_class[c]);

        log_prob[c] += s->has_shell * log(model->prob_shell[c]) +
                       (1 - s->has_shell) * log(1 - model->prob_shell[c]);

        log_prob[c] += s->has_socket * log(model->prob_socket[c]) +
                       (1 - s->has_socket) * log(1 - model->prob_socket[c]);

        log_prob[c] += log(gaussian_prob(s->num_strings, model->mean_num_strings[c], model->stddev_num_strings[c]));
        log_prob[c] += log(gaussian_prob(s->exec_size, model->mean_exec_size[c], model->stddev_exec_size[c]));
        log_prob[c] += log(gaussian_prob(s->entropy, model->mean_entropy[c], model->stddev_entropy[c]));
    }

    return (log_prob[1] > log_prob[0]) ? 1 : 0;
}
