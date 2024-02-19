#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "compactLR.hpp"
#include "Rinvb.hpp"
#include "solveLR.hpp"

namespace
{
	const Matrix A1{
		blaze::IdentityMatrix<double>{3}
	};

	const Matrix A2{
		{1, 0},
		{0, 2}
	};

	const Matrix A3{
		{1, -3, 2},
		{2, -8, 5},
		{3, -11, 11}
	};

	const Matrix expectedLRA3{
		{1, -3, 2},
		{2, -2, 1},
		{3, 1, 4}
	};

	const Matrix A7e{
		{6, -4, 7},
		{-12, 5, -12},
		{18, 0, 22}
	};

	const Matrix expectedLRA7e{
		{6, -4, 7},
		{-2, -3, 2},
		{3, -4, 9}
	};
}

TEST_CASE("Test rinvb")
{
	const Matrix A{
		{4, 3, 2},
		{0, 2, 1},
		{0, 0, 1}
	};
	const ColumnVector b{3, 2, 1};
	const ColumnVector expected{-.125, 0.5, 1};

	REQUIRE(expected == rinvb(A, b));
}

TEST_CASE("Test compactLR")
{
	const auto [expected, A] = GENERATE_REF(
		(table<Matrix, Matrix>)({
			{A1, A1},
			{A2, A2},
			{expectedLRA3, A3},
			{expectedLRA7e, A7e},
			}));

	REQUIRE(expected == compactLR(A));
}

TEST_CASE("Test solveLR")
{
	const auto [expected, A, b] = GENERATE(
		(table<ColumnVector, Matrix, ColumnVector>)({
			{{1, 0, 0}, A3, {1, 2, 3}},
			{{19./2, 3./2, -1}, A3, {3, 2, 1}},
			{{1./2, 1./3, 1./4}, A7e, {41./12, -22./3, 29./2}}
			}));

	const auto LR = compactLR(A);
	REQUIRE(expected == solveLR(LR, b));
}
