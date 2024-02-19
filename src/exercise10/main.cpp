#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <matplot/matplot.h>

#include "../ProfilingUtility.hpp"

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
	constexpr int max = 12;

	const std::vector ns = std::views::iota(min, max + 1)
							| std::views::transform([](const int exp) { return pow(2., exp); })
							| ranges::to<std::vector>();

	struct Case
	{
		std::function<Matrix(const Matrix&)> fun{};
		std::string labelText{};
		std::vector<RealSeconds> timings{};
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
			c.timings.emplace_back(profile(c.fun, A));
		}
	}

	for (const auto& c : cases)
	{
		matplot::loglog(
				ns,
				c.timings
				| std::views::transform(&RealSeconds::count)
				| ranges::to<std::vector>(),
				"-o")
			->display_name(c.labelText);
		matplot::hold(true);
	}

	matplot::hold(false);

	matplot::ylabel("duration (in seconds)");
	matplot::xlabel("n");
	matplot::legend()->location(matplot::legend::general_alignment::topleft);
	matplot::show();
}
