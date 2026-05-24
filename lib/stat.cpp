#include "../include/stat.h"
#include <iostream>
#include <cmath>
#include <ranges>
#include <numeric>
#include <boost/math/distributions/students_t.hpp>

variant::variant(local_data_dyn_array inp_var) : input_data(std::move(inp_var)) {}

void variant::alf(double t_alpha)
{
    alpha = (t_alpha <= 0.0 || t_alpha >= 1.0) ? 0.05 : t_alpha;
}

void variant::spot()
{
    // C++23: virtual flat range over all subvectors without memory allocation and copying
    auto joined_view = input_data | std::views::transform([](const auto &s)
                                                          { return std::views::all(s._l_data); }) |
                       std::views::join;

    size_t total_elements = 0;
    sum = 0.0;

    for (double val : joined_view)
    {
        sum += val;
        total_elements++;
    }

    if (total_elements == 0)
    {
        return;
    }

    // 1. Arithmetic mean
    average = sum / static_cast<double>(total_elements);

    // 2. Variance (Exact two-pass formula without pow)
    if (total_elements > 1)
    {
        double ds_ = 0.0;
        for (double val : joined_view)
        {
            double diff = val - average;
            ds_ += diff * diff;
        }

        dispersion = ds_ / static_cast<double>(total_elements - 1);
    }

    else
    {
        dispersion = 0.0;
    }

    // 3. Standard deviation
    deviation = std::sqrt(dispersion);

    // 4. Confidence interval (Student's t-test)
    if (total_elements > 1)
    {
        boost::math::students_t t_distrub(static_cast<double>(total_elements - 1));
        double t_value = quantile(complement(t_distrub, (alpha / 2.0)));
        confidence_interval = (t_value * deviation) / std::sqrt(static_cast<double>(total_elements));
    }

    else
    {
        confidence_interval = 0.0;
    }
}