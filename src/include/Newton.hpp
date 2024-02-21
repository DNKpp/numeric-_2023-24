#pragma once

#include "Definitions.hpp"

#include <concepts>

template <typename Fn>
	requires std::is_invocable_r_v<double, Fn, double>
[[nodiscard]]
std::vector<double> newtonSkalar(Fn f, auto df, const double x0, const double toly, const int maxIt)
{
	std::vector xk{x0};
	xk.reserve(maxIt + 1);
	for ([[maybe_unused]] const int i : std::views::iota(0, maxIt))
	{
		const double xi = xk.back();
		xk.emplace_back(xi - std::invoke(f, xi) / std::invoke(df, xi));
		if (blaze::abs(xk.back() - xi) <= toly)
		{
			break;
		}
	}

	return xk;
}
