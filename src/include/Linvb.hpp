#pragma once

#include "Definitions.hpp"

inline ColumnVector linvb(
	const Matrix& L,
	ColumnVector z
)
{
	const int n{static_cast<int>(std::ranges::ssize(z))};

	ColumnVector x(n, 0.);
	for (const auto i : bounded_int_range(0, n))
	{
		for (const auto k : bounded_int_range(0, i))
		{
			z[i] -= L(i, k) * x[k];
		}

		x[i] = z[i] / L(i, i);
	}

	return x;
}

inline ColumnVector linvb_vec(
	const Matrix& L,
	ColumnVector z
)
{
	const int n{static_cast<int>(std::ranges::ssize(z))};

	ColumnVector x(n, 0.);
	x[0] = z[0] / L(0, 0);
	for (const auto i : bounded_int_range(1, n))
	{
		const auto subL = subvector(row(L, i), 0, i);
		const auto subX = subvector(x, 0, i);
		z[i] -= subL * subX;
		x[i] = z[i] / L(i, i);
	}

	return x;
}

inline ColumnVector linvb2(
	const Matrix& L,
	ColumnVector z
)
{
	const int n{static_cast<int>(std::ranges::ssize(z))};

	ColumnVector x(n, 0.);
	for (const auto i : bounded_int_range(0, n))
	{
		x[i] = z[i] / L(i, i);

		for (const auto k : bounded_int_range(i + 1, n))
		{
			z[k] -= L(k, i) * x[i];
		}
	}

	return x;
}

inline ColumnVector linvb2_vec(
	const Matrix& L,
	ColumnVector z
)
{
	const int n{static_cast<int>(std::ranges::ssize(z))};

	ColumnVector x(n, 0.);
	for (const auto i : bounded_int_range(0, n))
	{
		x[i] = z[i] / L(i, i);

		const std::size_t begin = i + 1;
		const std::size_t length = n - begin;
		const auto subL = subvector(column(L, i), begin, length);
		subvector(z, begin, length) -= subL * x[i];
	}

	return x;
}
