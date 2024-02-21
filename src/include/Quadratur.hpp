#pragma once

#include <ranges>
#include <type_traits>
#include <range/v3/numeric/accumulate.hpp>

template <typename Fn>
	requires std::is_invocable_r_v<double, Fn, double>
[[nodiscard]]
inline double leftRectangleSum(Fn fn, const double a, const double b, const int m)
{
	const double h = (b - a) / m;

	return h * ranges::accumulate(
				std::views::iota(0, m)
				| std::views::transform([=](const int i) { return a + i * h; }),
				0.,
				{},
				std::ref(fn));
}

template <typename Fn>
	requires std::is_invocable_r_v<double, Fn, double>
[[nodiscard]]
inline double midpointSum(Fn fn, const double a, const double b, const int m)
{
	const double h_half = (b - a) / (2. * m);
	return leftRectangleSum(std::ref(fn), a + h_half, b + h_half, m);
}

template <typename Fn>
	requires std::is_invocable_r_v<double, Fn, double>
[[nodiscard]]
inline double trapezoidSum(Fn fn, const double a, const double b, const int m)
{
	const double h = (b - a) / m;

	const double inner = ranges::accumulate(
		std::views::iota(1, m)
		| std::views::transform([=](const int i) { return a + i * h; }),
		0.,
		{},
		std::ref(fn));
	const double border = 0.5 * (std::invoke(fn, a) + std::invoke(fn, b));
	return h * (inner + border);
}

template <typename Fn>
	requires std::is_invocable_r_v<double, Fn, double>
[[nodiscard]]
inline double simpsonSum(Fn fn, const double a, const double b, const int m)
{
	const double h = (b - a) / m;

	const double prefixSum = std::invoke(fn, a);
	const double postfixSum = std::invoke(fn, b);
	const double innerLeftSum = 2 * ranges::accumulate(
									std::views::iota(1, m)
									| std::views::transform([=](const int i) { return a + i * h; }),
									0.,
									{},
									std::ref(fn));
	const double innerMidpointSum = 4 * ranges::accumulate(
										std::views::iota(0, m)
										| std::views::transform(
											[=](const int i)
											{
												const double left = a + i * h;
												return std::midpoint(left, left + h);
											}),
										0.,
										{},
										std::ref(fn));

	return h * (prefixSum + innerLeftSum + innerMidpointSum + postfixSum) / 6.;
}
