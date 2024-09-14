#include "../include/stat.h"
#include <iostream>
#include <boost/math/distributions/students_t.hpp>

variant::variant(std::vector<std::vector<float>> inp_var) : input_data(inp_var) {}

void variant::alf(float t_alpha)
{
	if (t_alpha <= 0 || t_alpha >= 1)
	{
		alpha = 0.05;
	}

	else
	{
		alpha = t_alpha;
	}
}

void variant::spot()
{
	// загальні дані
	for (auto all_data : input_data)
	{
		for (auto sum_lines : all_data)
		{
			data.push_back(sum_lines);
		}
	}

	// визначення суми ряду
	auto sum_ = [](std::vector<float> temp)
	{
		float su_ = 0;
		for (auto s : temp)
		{
			su_ += s;
		}

		return su_;
	};

	// визначення сум варіантів
	for (int i = 0; i < input_data.size(); i++)
	{
		average_lines.push_back(sum_(input_data.at(i)) / input_data.at(i).size());
	}

	// загальна сума
	sum = sum_(data);

	// середнє арифметичне
	average = sum / data.size();

	// дисперсія
	auto disp_ = [this]()
	{
		float ds_ = 0;
		for (auto temp : data)
		{
			ds_ += (pow(temp, 2) - pow(average, 2));
		}

		return (float)(ds_ / (data.size() - 1));
	};

	dispersion = disp_();

	// стандартне відхилення
	deviation = sqrt(dispersion);

	// довірчий інтервал
	auto _conf_interval = [this]()
	{
		boost::math::students_t t_distrub(data.size() - 1);
		float t_value = (float)quantile(complement(t_distrub, (alpha / 2)));

		return (float)((t_value * deviation) / (sqrt(data.size())));
	};

	confidence_interval = _conf_interval();
}
