#ifndef STAT_H
#define STAT_H

#include <vector>

struct variant
{
	float average;             					// середнє
	float sum;                 					// сума
	float dispersion;          					// дисперсія
	float deviation;           					// стандартне відхилення
	float alpha;               					// критерій значущості 0 < alpha < 1
	float confidence_interval; 					// довірчий інтервал
	std::vector<float> data;   					// загальні дані
	std::vector<float> average_lines; 			// середні по варіантах
	std::vector<std::vector<float>> input_data; // вхідні дані

	variant(std::vector<std::vector<float>> inp_var);
	void alf(float t_alpha);
	void spot();
};

#endif // STAT_H