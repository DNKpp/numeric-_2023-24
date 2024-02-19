#pragma once

#pragma warning(push)
#pragma warning(disable:4996)	// 'localtime': This function or variable may be unsafe.

#include <blaze/Blaze.h>

#pragma warning(pop)

#include <ranges>

using ColumnVector = blaze::DynamicVector<double, blaze::columnVector>;
using Matrix = blaze::DynamicMatrix<double>;

constexpr auto bounded_int_range = [](const int begin, const int end)
{
	return std::views::iota(begin, std::ranges::max(begin, end));
};
