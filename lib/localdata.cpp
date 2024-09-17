#include "../include/localdata.h"

float local_data_struct::mid_aver()
{
    float mid = 0;

    for (auto a : _l_data)
    {
        mid += a;
    }

    return (mid / _l_data.size());
}