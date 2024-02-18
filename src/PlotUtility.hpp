#pragma once

#include <sciplot/sciplot.hpp>

#include <algorithm>
#include <type_traits>

inline sciplot::Vec logspace(const double base, const double minExp, const double maxExp, const int intervals)
{
	sciplot::Vec values = sciplot::linspace(minExp, maxExp, intervals);
	std::ranges::transform(
		values,
		std::ranges::begin(values),
		[&](const double exponent) { return std::pow(base, exponent); });
	return values;
}

template <typename Fun>
	requires std::is_invocable_r_v<double, Fun, double>
inline sciplot::Vec array_fun(const sciplot::Vec& inputs, Fun fun)
{
	sciplot::Vec values(std::ranges::size(inputs));
	std::ranges::transform(
		inputs,
		std::ranges::begin(values),
		std::ref(fun));
	return values;
}
