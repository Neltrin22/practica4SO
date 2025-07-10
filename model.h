// file: model.h
#ifndef MODEL_H
#define MODEL_H

typedef struct {
    float prob_class[2]; // P(benigno), P(malicioso)

    // para características booleanas
    float prob_shell[2];  // P(has_shell=1 | clase)
    float prob_socket[2]; // P(has_socket=1 | clase)

    // para características continuas
    float mean_num_strings[2];
    float stddev_num_strings[2];

    float mean_exec_size[2];
    float stddev_exec_size[2];

    float mean_entropy[2];
    float stddev_entropy[2];
} NaiveBayesModel;

#endif
