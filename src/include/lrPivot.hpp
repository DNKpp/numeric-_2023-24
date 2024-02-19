#pragma once

#include "Definitions.hpp"

#include <ranges>
#include <range/v3/all.hpp>

constexpr void fix_pivot_index(std::vector<int>& p, const auto& matrix, const int begin)
{
	const int n = static_cast<int>(p.size());
	const int length = n - begin;
	const auto index = blaze::argmax(blaze::abs(subvector(elements(column(matrix, begin), p), begin, length)));
	std::ranges::swap(p[begin], p[begin + index]);
}

inline std::tuple<Matrix, std::vector<int>> lrPivotZP(Matrix A)
{
	if (!isSquare(A))
	{
		throw std::invalid_argument{"Square matrix required."};
	}

	const int n = static_cast<int>(A.rows());
	std::vector<int> p = std::views::iota(0, n) | ranges::to<std::vector>();

	for (const int i : std::views::iota(0, n - 1))
	{
		fix_pivot_index(p, A, i);
		for (const int k : std::views::iota(i + 1, n))
		{
			const int columns = n - i - 1;
			const int pi = p[i];
			const int pk = p[k];
			A(pk, i) /= A(pi, i);
			submatrix(A, pk, i + 1, 1, columns)
				-= A(pk, i) * submatrix(A, pi, i + 1, 1, columns);
		}
	}

	return {std::move(A), std::move(p)};
}
