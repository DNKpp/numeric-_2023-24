#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include <fmt/chrono.h>
#include <fmt/ostream.h>
#include <matplot/matplot.h>

#include "Newton.hpp"
#include "Bisektion.hpp"
#include "Sekanten.hpp"
#include "RegulaFalsi.hpp"

TEST_CASE("newtonSkalar with f = x^2 - 5 and x0 = 1")
{
	constexpr auto f = [](const double x) { return x*x - 5.; };
	constexpr auto df= [](const double x) { return 2*x; };

	const std::vector xk = newtonSkalar(f, df, 1., 1e-16, 3);

	REQUIRE_THAT(xk, Catch::Matchers::RangeEquals(std::array{1., 3., 7./3, 47./21}));
}

TEST_CASE("newtonSkalar with f(x) = x^2 - cos(x) and x0 = 3")
{
	constexpr auto f = [](const double x) { return x * x - blaze::cos(x); };
	constexpr auto df = [](const double x) { return 2 * x + blaze::sin(x); };

	const std::vector xk = newtonSkalar(f, df, 3., 1e-8, 100);

	REQUIRE(3. == xk.front());
	REQUIRE(Catch::Approx{0.82413231230252242296}.epsilon(1e-8) == xk.back());
}

TEST_CASE("newtonSkalar with f(x) = (x-1)^2 and x0 = 3")
{
	constexpr auto f = [](const double x) { return blaze::pow(x - 1., 2.); };
	constexpr auto df = [](const double x) { return 2 * (x - 1); };

	const std::vector xk = newtonSkalar(f, df, 3., 1e-8, 100);

	REQUIRE(3. == xk.front());
	REQUIRE(Catch::Approx{1.}.epsilon(1e-8) == xk.back());
}
