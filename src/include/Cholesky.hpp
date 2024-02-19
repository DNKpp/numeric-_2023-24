#pragma once

#include "Definitions.hpp"

inline blaze::LowerMatrix<Matrix> cholesky(const Matrix& A)
{
	if (!isSymmetric(A))
	{
		throw std::invalid_argument{"Symmetric matrix required."};
	}

	const int n = static_cast<int>(A.rows());
	blaze::LowerMatrix<Matrix> L{blaze::IdentityMatrix<double>{A.rows()}};

	for (const int i : std::views::iota(0, n))
	{
		if (const auto sum = A(i, i) - sqrLength(subvector(row(L, i), 0, i));
			0. <= sum)
		{
			L(i, i) = blaze::sqrt(sum);
		}
		else
		{
			throw std::invalid_argument{"Input matrix is not s.p.d."};
		}

		for (const int k : std::views::iota(i + 1, n))
		{
			const auto subL = submatrix(L, 0, 0, n, i);
			L(k, i) = (A(k, i) - dot(row(subL, i), row(subL, k))) / L(i, i);
		}
	}

	return L;
}

inline blaze::LowerMatrix<Matrix> choleskyV(const Matrix& A)
{
	if (!isSymmetric(A))
	{
		throw std::invalid_argument{"Symmetric matrix required."};
	}

	const int n = static_cast<int>(A.rows());
	blaze::LowerMatrix<Matrix> L{blaze::IdentityMatrix<double>{A.rows()}};

	for (const int i : std::views::iota(0, n))
	{
		if (const auto sum = A(i, i) - sqrLength(subvector(row(L, i), 0, i));
			0. <= sum)
		{
			L(i, i) = blaze::sqrt(sum);
		}
		else
		{
			throw std::invalid_argument{"Input matrix is not s.p.d."};
		}

		const int height = n - i - 1;
		const auto block = submatrix(L, i + 1, 0, height, i);
		const auto pivotRow = trans(subvector(row(L, i), 0, i));

		subvector(column(L, i), i + 1, height) =
			(subvector(column(A, i), i + 1, height) - block * pivotRow)
			/ L(i, i);
	}

	return L;
}

inline blaze::LowerMatrix<Matrix> choleskyZ(const Matrix& A)
{
	if (!isSymmetric(A))
	{
		throw std::invalid_argument{"Symmetric matrix required."};
	}

	const int n = static_cast<int>(A.rows());
	blaze::LowerMatrix<Matrix> L{blaze::IdentityMatrix<double>{A.rows()}};

	for (const int i : std::views::iota(0, n))
	{
		for (const int k : std::views::iota(0, i))
		{
			const auto subL = submatrix(L, 0, 0, n, k);
			L(i, k) = (A(i, k) - dot(row(subL, k), row(subL, i)))
					/ L(k, k);
		}

		if (const auto sum = A(i, i) - sqrLength(subvector(row(L, i), 0, i));
			0. <= sum)
		{
			L(i, i) = blaze::sqrt(sum);
		}
		else
		{
			throw std::invalid_argument{"Input matrix is not s.p.d."};
		}
	}

	return L;
}
