#pragma once

inline ColumnVector rinvb(
	const Matrix& R,
	ColumnVector b
)
{
	const int n{static_cast<int>(std::ranges::ssize(b))};

	ColumnVector x(n, 0.);
	for (const auto i : bounded_int_range(0, n) | std::views::reverse)
	{
		const int length = n - i;
		const auto subR = subvector(row(R, i), i, length);
		const auto subX = subvector(x, i, length);
		x[i] = (b[i] - subR * subX) / R(i, i);
	}

	return x;
}
