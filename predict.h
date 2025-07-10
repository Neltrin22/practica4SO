#ifndef PREDICT_H
#define PREDICT_H

#include "dataset.h"
#include "model.h"

int load_model(const char *filename, NaiveBayesModel *model);
int predict(const NaiveBayesModel *model, Sample *sample);

#endif
