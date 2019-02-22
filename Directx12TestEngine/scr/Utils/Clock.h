#pragma once

#include <chrono>
#include <ctime>
#include <string>

namespace dx12ge
{
	typedef std::chrono::milliseconds milliseconds;
	typedef std::chrono::microseconds microseconds;
	typedef std::chrono::nanoseconds nanoseconds;
	typedef std::chrono::duration<int, std::ratio<86400>> days;
	typedef std::chrono::duration<double, std::ratio<3600>> hours;
	typedef std::chrono::duration<double, std::ratio<60>> minutes;
	typedef std::chrono::duration<double> seconds;

	typedef std::chrono::hours hoursL;
	typedef std::chrono::minutes minutesL;
	typedef std::chrono::seconds secondsL;

	struct Date
	{
		int milli;
		int sec;  // seconds after the minute - [0, 60] including leap second
		int min;  // minutes after the hour - [0, 59]
		int hour; // hours since midnight - [0, 23]
		int mday; // day of the month - [1, 31]
		int mon;  // months since January - [1, 12]
		int year; // years
		int wday; // days since Sunday - [0, 6]
		int yday; // days since January 1 - [0, 365]
	};

	class Clock
	{
	private:
		static std::chrono::high_resolution_clock clock;
		static std::chrono::time_point<std::chrono::steady_clock> startTime;

	public:
		Clock() {
			startTime = clock.now();
		};
		~Clock() {};

		static Date date()
		{
			Date date;

			auto now = std::chrono::system_clock::now();
			time_t tt = std::chrono::system_clock::to_time_t(now);
			tm local_tm;
			localtime_s(&local_tm, &tt);

			date.milli = std::chrono::duration_cast<milliseconds>(std::chrono::steady_clock::now() - startTime).count() % 1000;
			date.sec = local_tm.tm_sec;
			date.min = local_tm.tm_min;
			date.hour = local_tm.tm_hour;
			date.mday = local_tm.tm_mday;
			date.mon = local_tm.tm_mon + 1;
			date.year = local_tm.tm_year + 1900;
			date.wday = local_tm.tm_wday;
			date.yday = local_tm.tm_yday;

			return date;
		};

		static std::string date_as_string()
		{
			Date date = dx12ge::Clock::date();
			return std::string(std::to_string(date.year) + "-" + std::to_string(date.mon) + "-" + std::to_string(date.mday));
		}
		static std::string systime_as_string()
		{
			Date date = dx12ge::Clock::date();
			return std::string(std::to_string(date.hour) + ":" + std::to_string(date.min) + ":" + std::to_string(date.sec) + ":" + std::to_string(date.milli));
		}
		static std::string date_and_systime_as_string()
		{
			Date date = dx12ge::Clock::date();
			return std::string(date_as_string() + " " + systime_as_string());
		}

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