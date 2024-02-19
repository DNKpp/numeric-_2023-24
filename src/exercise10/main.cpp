#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <sciplot/sciplot.hpp>

#include "Cholesky.hpp"
#include "lrPivot.hpp"

namespace
{
	const Matrix A10_1{	// not symmetrical
		{1, 1, 0},
		{-1, 1, -1},
		{0, -1, 2}
	};

	const Matrix A10_2{	// not s.p.d.
		{1, 2, 1},
		{2, 8, 1},
		{1, 1, -8}
	};

	const Matrix A10_3{
		{1, 2, 1},
		{2, 8, 2},
		{1, 2, 2}
	};

	const Matrix expectedCholeskyA10_3{
		{1, 0, 0},
		{2, 2, 0},
		{1, 0, 1}
	};

	const Matrix A12{
		{1, -1, 1, 0},
		{-1, 2, 0, 1},
		{1, 0, 6, -3},
		{0, 1, -3, 30}
	};

	const Matrix expectedCholeskyA12{
		{1, 0, 0, 0},
		{-1, 1, 0, 0},
		{1, 1, 2, 0},
		{0, 1, -2, 5}
	};

	const Matrix B1{
		{4, 2, 4, 4},
		{2, 10, 5, 2},
		{4, 5, 9, 6},
		{4, 2, 6, 9}
	};

	const Matrix expectedCholeskyB1{
		{2, 0, 0, 0},
		{1, 3, 0, 0},
		{2, 1, 2, 0},
		{2, 0, 1, 2}
	};
}

TEST_CASE("Test cholesky with invalid matrices.")
{
	const auto fn = GENERATE(
		&cholesky,
		&choleskyV,
		&choleskyZ);

	const auto& A = GENERATE_REF(A10_1, A10_2);

	REQUIRE_THROWS(std::invoke(fn, A));
}

TEST_CASE("Test cholesky")
{
	const auto fn = GENERATE(
		&cholesky,
		&choleskyV,
		&choleskyZ);

	const auto& [expectation, A] = GENERATE_REF(
		(table<Matrix, Matrix>)({
			{expectedCholeskyA10_3, A10_3},
			{expectedCholeskyA12, A12},
			{expectedCholeskyB1, B1}
			}));

	REQUIRE(expectation == std::invoke(fn, A));
}

TEST_CASE("13 a) plot benchmarks.")
{
	constexpr int min = 3;
	constexpr int max = 13;

	constexpr auto profile = []<typename... Args>(auto out, auto fun, Args&&... inputs)
	{
		constexpr auto clock = std::chrono::steady_clock{};
		const auto begin = clock.now();
		auto result = std::invoke(fun, std::forward<Args>(inputs)...);
		const auto duration = clock.now() - begin;
		*out = duration;
		return result;
	};

	const std::valarray ns = []
	{
		std::valarray<double> exponents(max - min + 1);
		std::iota(begin(exponents), end(exponents), static_cast<double>(min));
		return pow(2., exponents);
	}();

	struct Case
	{
		std::function<Matrix(const Matrix&)> fun{};
		std::string labelText{};
		std::vector<std::chrono::nanoseconds> timings{};
	};

	std::array cases{
		Case{&cholesky, "cholesky"},
		Case{&choleskyV, "choleskyV"},
		Case{&choleskyZ, "choleskyZ"},
		Case{[](const Matrix& A) { return std::get<0>(lrPivotZP(A)); }, "lrPivotZP"}
	};

	for (const auto n : ns)
	{
		const Matrix A = [&]
		{
			Matrix M = 2 * blaze::IdentityMatrix<double>{static_cast<std::size_t>(n)};
			band(M, 1) = ColumnVector(M.rows() - 1, -1.);
			band(M, -1) = ColumnVector(M.rows() - 1, -1.);
			return M;
		}();

		for (auto& c : cases)
		{
			// prevent the optimizer from optimizing away the call, by using volatile
			volatile auto result = profile(std::back_inserter(c.timings), c.fun, A);
		}
	}

	sciplot::Plot2D plot{};
	plot.legend()
		.atOutsideTopLeft()
		.displayHorizontal();
	plot.ytics().logscale(10);
	plot.xtics().logscale(2);
	plot.ylabel("duration (in seconds)");
	plot.xlabel("n");

	for (const auto& c : cases)
	{
		sciplot::Vec timings(std::ranges::size(ns));
		std::ranges::transform(
			c.timings,
			std::ranges::begin(timings),
			[](const auto& duration)
			{
				return static_cast<double>(duration.count()) * 1e-9;
			});
		plot.drawCurve(ns, timings)
			.label(c.labelText);
	}

	sciplot::Figure figure{{plot}};
	figure.palette("dark2");
	sciplot::Canvas canvas{{figure}};
	canvas.size(1200, 600);
	canvas.show();
}
