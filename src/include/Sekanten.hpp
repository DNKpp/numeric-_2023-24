#pragma once

#include "Definitions.hpp"

#include <type_traits>

template <typename Fn>
	requires std::is_invocable_r_v<double, Fn, double>
[[nodiscard]]
std::vector<double> sekanten(Fn f, const double x0, const double x1, const double toly, const int maxIt)
{
	std::vector xk{x0, x1};
	xk.reserve(maxIt + 2);

	double f_prev = std::invoke(f, x0);
	for ([[maybe_unused]] const int i : std::views::iota(0, maxIt))
	{
		const double x_prev = xk[xk.size() - 2];
		const double x_k = xk.back();
		const double fk = std::invoke(f, xk.back());

		xk.emplace_back(x_k) -= fk * (x_k - x_prev) / (fk - f_prev);

		if (blaze::abs(fk - f_prev) <= toly)
		{
			break;
		}

		f_prev = fk;
	}

	return xk;
}
