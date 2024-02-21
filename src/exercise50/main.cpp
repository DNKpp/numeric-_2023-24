#include <numbers>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include <fmt/chrono.h>
#include <fmt/ostream.h>
#include <matplot/matplot.h>
#include <range/v3/all.hpp>

#include "Definitions.hpp"
#include "Quadratur.hpp"

namespace
{
	struct Case
	{
		std::function<double(int)> fun{};
		std::string labelText{};
		std::vector<double> results{};
	};

	void plot_results(const std::span<const Case> cases, const std::vector<int>& ms, const double exactResult)
	{
		matplot::ylabel("error |I[f] - Q[f]|");
		matplot::xlabel("m");
		matplot::legend()->location(matplot::legend::general_alignment::topright);
		matplot::hold(true);

		const auto error = [=](const double approx)
		{
			const auto err = blaze::abs(exactResult - approx);
			// prevent the error from being treated as 0
			return std::max(1e-16, err);
		};

		for (const auto& c : cases)
		{
			matplot::loglog(ms, matplot::transform(c.results, error), "-*")
				->display_name(c.labelText);
		}

		const auto plot_gradient = [&](
			const std::string_view displayName,
			const double factor,
			const double exp,
			const std::string_view style
		)
		{
			matplot::loglog(
					ms,
					ms
					| std::views::transform([=](const int m) { return factor * blaze::pow(m, exp); })
					| ranges::to<std::vector>(),
					style)
				->display_name(displayName);
		};

		plot_gradient("Gradient 1", 0.5, -1., "k-");
		plot_gradient("Gradient 2", 0.03, -2., "k:");
		plot_gradient("Gradient 4", 1e-3, -4., "k-");
		

		matplot::hold(false);
		matplot::show();
	}
}

TEST_CASE("50 b) plot quadratur for e^x")
{
	constexpr auto f = [](const double x) { return blaze::exp(x); };
	constexpr double exactResult = std::numbers::e - 1.;
	constexpr double lower{0.};
	constexpr double upper{1.};

	std::array cases{
		Case{[](const int m) { return leftRectangleSum(f, lower, upper, m); }, "leftRectangleSum"},
		Case{[](const int m) { return midpointSum(f, lower, upper, m); }, "midpointSum"},
		Case{[](const int m) { return trapezoidSum(f, lower, upper, m); }, "trapezoidSum"},
		Case{[](const int m) { return simpsonSum(f, lower, upper, m); }, "simpsonSum"}
	};

	const std::vector ms = std::views::iota(0, 24)
							| std::views::transform([](const int exp) { return static_cast<int>(blaze::exp2(exp)); })
							| ranges::to<std::vector>();
	for (auto& c : cases)
	{
		c.results = ms
					| std::views::transform(std::ref(c.fun))
					| ranges::to<std::vector>();
	}

	plot_results(cases, ms, exactResult);
}

TEST_CASE("50 b) plot quadratur for 2 / (x^2 + 1)")
{
	constexpr auto f = [](const double x) { return 2. / (blaze::pow2(x) + 1.); };
	constexpr double exactResult = std::numbers::pi;
	constexpr double lower{-1.};
	constexpr double upper{1.};

	std::array cases{
		Case{[](const int m) { return leftRectangleSum(f, lower, upper, m); }, "leftRectangleSum"},
		Case{[](const int m) { return midpointSum(f, lower, upper, m); }, "midpointSum"},
		Case{[](const int m) { return trapezoidSum(f, lower, upper, m); }, "trapezoidSum"},
		Case{[](const int m) { return simpsonSum(f, lower, upper, m); }, "simpsonSum"}
	};

	const std::vector ms = std::views::iota(0, 24)
							| std::views::transform([](const int exp) { return static_cast<int>(blaze::exp2(exp)); })
							| ranges::to<std::vector>();
	for (auto& c : cases)
	{
		c.results = ms
					| std::views::transform(std::ref(c.fun))
					| ranges::to<std::vector>();
	}

	plot_results(cases, ms, exactResult);
}
