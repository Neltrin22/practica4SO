// file: dataset.h
#ifndef DATASET_H
#define DATASET_H

typedef struct {
    char filename[100]; 
    int has_shell;
    int has_socket;
    int num_strings;
    int exec_size;
    float entropy;
    int label;
} Sample;

int load_dataset(const char *filename, Sample samples[], int max_samples);

#endif
