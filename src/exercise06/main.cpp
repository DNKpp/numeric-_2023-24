#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <matplot/matplot.h>
#include <range/v3/all.hpp>

#include "../ProfilingUtility.hpp"

#include "Linvb.hpp"

namespace
{
	const Matrix A1{
		{1, 0, 0},
		{1, 2, 0,},
		{2, 3, 4}
	};

	const Matrix A2{
		{1, 0, 0},
		{1, 1, 0,},
		{2, 3, 1}
	};
}

TEST_CASE("6.b) Linvb functions solve the LGS by forward-insertion", "[linvb]")
{
	const auto fun = GENERATE(
		&linvb,
		&linvb_vec,
		&linvb2,
		&linvb2_vec
	);

	const auto [expectation, L, z] = GENERATE_REF(
		(table<ColumnVector, Matrix, ColumnVector>)({
			{
			{42., 1337.},
			blaze::IdentityMatrix<double>{2},
			{42., 1337.}
			},
			{
			{21., 668.5},
			2 * blaze::IdentityMatrix<double>{2},
			{42., 1337.}
			},
			{
			{1, 0.5, -.125},
			A1,
			{1, 2, 3}
			},
			{
			{1, 1, -2},
			A2,
			{1, 2, 3}
			}
			}));

	REQUIRE(expectation == std::invoke(fun, L, z));
}

TEST_CASE("6 c) plot benchmarks.")
{
	constexpr int min = 6;
	constexpr int max = 15;

	const std::vector ns = std::views::iota(min, max + 1)
							| std::views::transform([](const int exp) { return pow(2., exp); })
							| ranges::to<std::vector>();

	struct Case
	{
		using FunPtr = ColumnVector(*)(const Matrix&, ColumnVector);
		FunPtr fun{};
		std::string labelText{};
		std::vector<RealSeconds> timings{};
	};

	std::array cases{
		Case{&linvb, "linvb"},
		Case{&linvb2, "linvb2"},
		Case{&linvb_vec, "linvb_{vec}"},
		Case{&linvb2_vec, "linvb2_{vec}"}
	};

	for (const auto n : ns)
	{
		const blaze::LowerMatrix<Matrix> L{blaze::IdentityMatrix<double>{static_cast<std::size_t>(n)}};
		const ColumnVector z(L.rows(), 1.);

		for (auto& c : cases)
		{
			c.timings.emplace_back(profile(c.fun, L, z));
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
