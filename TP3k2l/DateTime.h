#pragma once

#include <regex>
#include <string>
#include <iostream>
#include <sstream>
#include "Validator.h"

namespace DateTime {
	class TimeStamp:public Validator{
	private:
		short hour;
		short minute;
		short second;
	public:
		TimeStamp(std::string& time_string);
		TimeStamp() :hour(0), minute(0), second(0), Validator() {};
		bool is_valid(bool raise_exceptions = false) override;
		short* validate(short value[]);
		int16_t to_seconds();
		bool after(TimeStamp& compare_time) {
			return this->to_seconds() > compare_time.to_seconds();
		}
		std::string to_string();
	};

	class DateStamp: public Validator{
	private:
		short year;
		short month;
		short day;
	public:
		DateStamp(std::string date_string);
		DateStamp() :year(0), month(0), day(0), Validator() {};
		bool is_valid(bool raise_exceptions = false) override;
		short* validate(short value[]);
		long long to_seconds();
		bool after(DateStamp& compare_date);
		std::string to_string();
	};

	class DateTimeStamp:public Validator {
	private:
		TimeStamp* time;
		DateStamp* date;
	public:
		DateTimeStamp(std::string& dt_string);
		DateTimeStamp(): time(0), date(0), Validator() {};
		DateTimeStamp(const DateTime::DateTimeStamp& on_copy);
		bool is_valid(bool raise_exceptions = false) override;
		bool after(DateTimeStamp& another_dts);
		long long to_seconds();
		std::string to_string();
		DateTime::TimeStamp getTime();
		DateTime::DateStamp getDate();
		bool only_time();
		bool only_date();
		bool full_datetime();
	};
}
