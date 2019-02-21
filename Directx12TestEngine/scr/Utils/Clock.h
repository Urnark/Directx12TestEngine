#pragma once

#include <chrono>
#include <ctime>

namespace dx12ge
{
	using milliseconds	= std::chrono::milliseconds;
	using microseconds	= std::chrono::microseconds;
	using nanoseconds	= std::chrono::nanoseconds;
	using days			= std::chrono::duration<double, std::ratio<86400>>;
	using hours			= std::chrono::duration<double, std::ratio<3600>>;
	using minutes		= std::chrono::duration<double, std::ratio<60>>;
	using seconds		= std::chrono::duration<double>;

	using daysL			= std::chrono::duration<int, std::ratio<86400>>;
	using hoursL		= std::chrono::hours;
	using minutesL		= std::chrono::minutes;
	using secondsL		= std::chrono::seconds;

	class Clock
	{
	private:
		std::chrono::high_resolution_clock clock;

	public:
		Clock() {};
		~Clock() {};

		template<typename Type>
		Type now()
		{
			auto time_nano = std::chrono::time_point_cast<Type>(clock.now());
			auto epoch = time_nano.time_since_epoch();
			auto value = std::chrono::duration_cast<Type>(epoch);
			return value;
		};

		template<typename To, typename Time>
		To time_Cast(const Time& time)
		{
			return std::chrono::duration_cast<To>(time);
		}

		template<typename To,typename Time1, typename Time2>
		To duration(const Time1& t1, const Time2& t2)
		{
			if (t1.count() > t2.count())
				return std::chrono::duration_cast<To>(t1 - t2);
			else
				return std::chrono::duration_cast<To>(t2 - t1);
		}

		template<typename ToDurFirst, typename ToDurSecond, typename Time1, typename Time2>
		std::chrono::duration<ToDurFirst, ToDurSecond> duration(const Time1& t1, const Time2& t2)
		{
			if (t1.count() > t2.count())
				return std::chrono::duration_cast<std::chrono::duration<ToDurFirst, ToDurSecond>>(t1 - t2);
			else
				return std::chrono::duration_cast<std::chrono::duration<ToDurFirst, ToDurSecond>>(t2 - t1);
		}
	};
};