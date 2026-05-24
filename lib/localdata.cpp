#include "../include/localdata.h"
#include <numeric>
#include <limits>

double local_data_struct::mid_aver() const noexcept
{
    if (_l_data.empty())
    {
        return std::numeric_limits<double>::quiet_NaN();
    }

    const double sum = std::accumulate(_l_data.begin(), _l_data.end(), 0.0);
    return sum / static_cast<double>(_l_data.size());
}