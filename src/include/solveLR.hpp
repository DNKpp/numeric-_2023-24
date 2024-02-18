#pragma once

#include "Definitions.hpp"
#include "Rinvb.hpp"

inline ColumnVector solveLR(const Matrix& A, const ColumnVector& b)
{
	const int n = static_cast<int>(b.size());

	// specialized version of linvb_vec, which treats the main diagonal consistently as one
	ColumnVector z{b};
	for (const auto i : std::views::iota(1, n))
	{
		const auto subA = subvector(row(A, i), 0, i);
		const auto subZ = subvector(z, 0, i);
		z[i] = b[i] - subA * subZ;
	}
	return rinvb(A, z);
}
