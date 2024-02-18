#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <sciplot/sciplot.hpp>

#include "Linvb.hpp"

TEST_CASE("6.b) Linvb functions solve the LGS by forward-insertion", "[linvb]")
{
	const auto fun = GENERATE(
		&linvb,
		&linvb_vec,
		&linvb2,
		&linvb2_vec
	);

	const auto [expectation, L, z] = GENERATE(
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
			{{1, 0, 0},{1,2, 0,},{2, 3, 4}},
			{1, 2, 3}
			}
			}));

	REQUIRE(expectation == std::invoke(fun, blaze::LowerMatrix<Matrix>{L}, z));
}

TEST_CASE("6 c) plot benchmarks.")
{
	constexpr int min = 6;
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
		using FunPtr = ColumnVector(*)(const blaze::LowerMatrix<Matrix>&, ColumnVector);
		FunPtr fun{};
		std::string labelText{};
		std::vector<std::chrono::nanoseconds> timings{};
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
			// prevent the optimizer from optimizing away the call, by using volatile
			volatile auto result = profile(std::back_inserter(c.timings), c.fun, L, z);
		}
	}

	sciplot::Plot2D plot{};
	plot.legend()
		.atOutsideTopLeft()
		.displayHorizontal();
	plot.ytics().logscale(10);
	plot.xtics().logscale(2);
	plot.ylabel("duration (in nanoseconds)");
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
