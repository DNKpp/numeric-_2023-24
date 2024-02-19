#pragma once

#include <chrono>
#include <type_traits>

using RealSeconds = std::chrono::duration<double>;

template <typename Fun, typename... Args>
	requires std::invocable<Fun, Args...>
constexpr RealSeconds profile(Fun fun, Args&&... inputs)
{
	const auto begin = std::chrono::steady_clock::now();
	volatile auto result = std::invoke(fun, std::forward<Args>(inputs)...);

	return std::chrono::duration_cast<RealSeconds>(std::chrono::steady_clock::now() - begin);
}
