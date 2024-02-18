#pragma once

#include "Definitions.hpp"

inline Matrix compactLR(Matrix A)
{
	if (!isSquare(A))
	{
		throw std::invalid_argument{"Square matrix required."};
	}

	const int n = static_cast<int>(A.rows());
	for (const auto i : std::views::iota(0, n - 1))
	{
		const int length = n - i;
		auto subA = submatrix(A, i, i, length, length);
		for (const auto k : std::views::iota(1, length))
		{
			const auto factor = subA(k, 0) / subA(0, 0);
			row(subA, k) -= factor * row(subA, 0);
			subA(k, 0) = factor;
		}
	}

	return A;
}

