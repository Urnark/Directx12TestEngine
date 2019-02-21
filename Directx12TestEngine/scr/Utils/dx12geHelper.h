#pragma once

#include <functional>

namespace dx12ge
{
	template<typename R, typename C, typename... Args>
	std::function<R(Args...)> bindFunciton(R(C::* func)(Args...), const C* instance) {
		return [=](Args... args) { return (instance->*func)(args...); };
	};
	template<typename R, typename C, typename... Args>
	std::function<R(Args...)> bindFunciton(R(C::* func)(Args...) const, const C* instance) {
		return [=](Args... args) { return (instance->*func)(args...); };
	};
	template<typename R, typename C, typename... Args>
	std::function<R(Args...)> bindFunciton(R(C::* func)(Args...), C* instance) {
		return [=](Args... args) { return (instance->*func)(args...); };
	};
	template<typename R, typename C, typename... Args>
	std::function<R(Args...)> bindFunciton(R(C::* func)(Args...) const, C* instance) {
		return [=](Args... args) { return (instance->*func)(args...); };
	};
}