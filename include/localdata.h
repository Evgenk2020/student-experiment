#ifndef LOCALDATA_H
#define LOCALDATA_H

#include <vector>
#include <string>

struct local_data_struct
{
    std::vector<float> _l_data; // динамічний масив для окремого варіанта
    float mid_aver();
};

typedef std::vector<local_data_struct> local_data_dyn_array;

#endif // LOCALDATA_H