#ifndef STAT_H
#define STAT_H

#include "../include/localdata.h"

struct variant
{
	float average;             				// середнє
	float sum;                 				// сума
	float dispersion;          				// дисперсія
	float deviation;           				// стандартне відхилення
	float alpha;               				// критерій значущості 0 < alpha < 1
	float confidence_interval; 				// довірчий інтервал
	std::vector<float> data;   				// ою'єднані загальні дані
	local_data_dyn_array input_data; 		// вхідні дані

	variant(local_data_dyn_array inp_var);
	void alf(float t_alpha);
	void spot();
};

#endif // STAT_H