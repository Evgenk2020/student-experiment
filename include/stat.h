#ifndef STAT_H
#define STAT_H

#include "../include/localdata.h"
#include <vector>

struct variant
{
    double average{};                  // середнє
    double sum{};                      // сума
    double dispersion{};               // дисперсія
    double deviation{};                // стандартне відхилення
    double alpha{};                    // критерій значущості 0 < alpha < 1
    double confidence_interval{};      // довірчий інтервал
    local_data_dyn_array input_data{}; // єдиний контейнер даних в пам'яті

    variant(local_data_dyn_array inp_var);
    void alf(double t_alpha);
    void spot();
};

#endif // STAT_H