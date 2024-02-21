#pragma once

#include "Definitions.hpp"

#include <type_traits>

template <typename Fn>
	requires std::is_invocable_r_v<double, Fn, double>
[[nodiscard]]
std::vector<double> bisektion(Fn f, double a, double b, const double tolx)
{
	std::vector xk{a, b};
	double fa = std::invoke(f, a);
	while (tolx < blaze::abs(a - b))
	{
		xk.emplace_back(std::midpoint(a, b));

		const double fm = std::invoke(f, xk.back());
		if (fa * fm < 0.)
		{
			b = xk.back();
		}
		else
		{
			a = xk.back();
			fa = fm;
		}
	}

	return xk;
}
