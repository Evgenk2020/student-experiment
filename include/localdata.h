#ifndef LOCALDATA_H
#define LOCALDATA_H

#include <vector>

struct local_data_struct
{
    std::vector<double> _l_data{};
    [[nodiscard]] double mid_aver() const noexcept;
};

using local_data_dyn_array = std::vector<local_data_struct>;

#endif // LOCALDATA_H