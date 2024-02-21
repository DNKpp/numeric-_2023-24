#pragma once

#include <chrono>
#include <type_traits>

using RealSeconds = std::chrono::duration<double>;

void do_not_optimize(auto& value)
{
	volatile auto* var = std::addressof(value);
}

template <typename Fun, typename... Args>
	requires std::invocable<Fun, Args...>
constexpr RealSeconds profile(Fun fun, Args&&... inputs)
{
	const auto begin = std::chrono::steady_clock::now();
	auto result = std::invoke(fun, std::forward<Args>(inputs)...);
	const auto duration = std::chrono::steady_clock::now() - begin;
	do_not_optimize(result);

	return std::chrono::duration_cast<RealSeconds>(duration);
}

