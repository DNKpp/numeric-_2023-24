#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include <fmt/chrono.h>
#include <fmt/ostream.h>
#include <matplot/matplot.h>
#include <range/v3/all.hpp>

#include "Bisektion.hpp"
#include "RegulaFalsi.hpp"
#include "Sekanten.hpp"

TEST_CASE("32 b) f(x) = x^2 - cos(x) in [0, 3]")
{
	constexpr auto f = [](const double x) { return x * x - blaze::cos(x); };
	constexpr double lower{0.};
	constexpr double upper{3.};
	constexpr double tol{1e-8};
	constexpr int maxIt{100};

	const auto fun = GENERATE_COPY(
		+[] { return bisektion(f, lower, upper, tol); },
		+[] { return regulaFalsi(f, lower, upper, tol, maxIt); },
		+[] { return sekanten(f, lower, upper, tol, maxIt); }
	);

	const std::vector xk = fun();

	REQUIRE(lower == xk.front());
	REQUIRE(upper == xk[1]);
	REQUIRE(Catch::Approx{0.82413231230252242296}.epsilon(1e-8) == xk.back());
}

namespace
{
	void plot_bisection_interval_lengths(const std::vector<double>& bisectionResults)
	{
		const std::vector lengths = matplot::transform(
			bisectionResults | ranges::views::drop_last(1) | ranges::to<std::vector>(),
			bisectionResults | ranges::views::drop(1) | ranges::to<std::vector>(),
			[](const double lhs, const double rhs) { return blaze::abs(lhs - rhs); });
		matplot::semilogy(
				matplot::linspace(1., static_cast<double>(std::ranges::ssize(lengths)), std::ranges::ssize(lengths)),
				lengths)
			->display_name("Bisektion Intervall Länge");
	}
}

TEST_CASE("32 b) plot f(x) = x^2 - cos(x) in [0, 3]")
{
	constexpr auto f = [](const double x) { return x * x - blaze::cos(x); };
	constexpr double lower{0.};
	constexpr double upper{3.};
	constexpr double tol{1e-8};
	constexpr int maxIt{100};
	constexpr double x = 0.82413231230252242296;

	struct Case
	{
		std::string labelText{};
		std::vector<double> xk{};
	};

	constexpr auto error = [](const double approx) { return blaze::abs(x - approx); };

	std::array cases{
		Case{"bisektion", bisektion(f, lower, upper, tol)},
		Case{"regulaFalsi", regulaFalsi(f, lower, upper, tol, maxIt)},
		Case{"sekanten", sekanten(f, lower, upper, tol, maxIt)}
	};

	matplot::ylabel("error |x_k - x^*|");
	matplot::xlabel("i");
	matplot::legend()->location(matplot::legend::general_alignment::bottomleft);
	matplot::hold(true);

	for (const auto& c : cases)
	{
		const auto xkLength = std::ranges::ssize(c.xk);
		matplot::semilogy(
				matplot::linspace(0., static_cast<double>(xkLength - 1), xkLength),
				matplot::transform(c.xk, error))
			->display_name(c.labelText);
	}

	plot_bisection_interval_lengths(cases.front().xk);

	matplot::hold(false);

	matplot::show();
}
