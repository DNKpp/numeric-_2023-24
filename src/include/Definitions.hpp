#pragma once

#include <blaze/Blaze.h>

#include <ranges>

using ColumnVector = blaze::DynamicVector<double, blaze::columnVector>;
using Matrix = blaze::DynamicMatrix<double>;

constexpr auto bounded_int_range = [](const int begin, const int end)
{
	return std::views::iota(begin, std::ranges::max(begin, end));
};
