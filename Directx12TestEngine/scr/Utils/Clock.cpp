#include "Clock.h"

namespace dx12ge
{
	std::chrono::high_resolution_clock dx12ge::Clock::clock;
	std::chrono::time_point<std::chrono::steady_clock> dx12ge::Clock::startTime;
}