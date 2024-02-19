#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "lrPivot.hpp"
#include "solveLR.hpp"

namespace
{
	const Matrix A1{
		{0, 1},
		{1, 0}
	};

	const Matrix lrPivotExpectationA1{
		{1, 0},
		{0, 1}
	};

	const Matrix A2{
		{1, 0},
		{0, 2}
	};

	const Matrix lrPivotExpectationA2{A2};

	const Matrix A3{
		{1, 2, 2},
		{-2, -2, 4},
		{2, 4, 2}
	};

	const Matrix lrPivotExpectationA3{
		{-2, -2, 4},
		{-1, 2, 6},
		{-1. / 2, 1. / 2, 1}
	};
}

TEST_CASE("Test lrPivotZP")
{
	const auto [expectation, A] = GENERATE_REF(
		(table<Matrix, Matrix>)({
			{lrPivotExpectationA1, A1},
			{lrPivotExpectationA2, A2},
			{lrPivotExpectationA3, A3}
			}));

	const auto [M, p] = lrPivotZP(A);
	const auto permutedM = rows(M, p);

	REQUIRE(expectation == permutedM);
}

TEST_CASE("SolveLR with lrPivotZP.")
{
	const Matrix A{
		{1, 4, 7, 7, 5},
		{0, 8, 3, 3, 7},
		{4, 6, 9, 9, 5},
		{2, 5, 6, 6, 2},
		{8, 3, 5, 6, 1}
	};

	const ColumnVector b{3, 8, 2, 6, 9};
	const ColumnVector expectedX{-49. / 26, 24. / 13, -875. / 52, 225. / 13, -61. / 52};

	const auto [M, p] = lrPivotZP(A);
	const auto x = solveLR(rows(M, p), elements(b, p));

	REQUIRE(expectedX == x);
}
