#pragma once

#include "Definitions.hpp"

#include <type_traits>

template <typename Fn>
	requires std::is_invocable_r_v<double, Fn, double>
[[nodiscard]]
std::vector<double> regulaFalsi(Fn f, double a, double b, const double toly, const int maxIt)
{
	std::vector xk{a, b};
	xk.reserve(maxIt + 2);
	double fa = std::invoke(f, a);
	double fb = std::invoke(f, b);

	for ([[maybe_unused]] const int i : std::views::iota(0, maxIt))
	{
		xk.emplace_back((a * fb - b * fa) / (fb - fa));

		const double fm = std::invoke(f, xk.back());
		if (fa * fm < 0.)
		{
			b = xk.back();
			fb = fm;
		}
		else
		{
			a = xk.back();
			fa = fm;
		}
		if (blaze::abs(fa - fb) <= toly)
		{
			break;
		}
	}

	return xk;
}
