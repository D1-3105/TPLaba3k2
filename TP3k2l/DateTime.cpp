#include "DateTime.h"
#pragma once

DateTime::DateTimeStamp::DateTimeStamp(std::string& dt_string)
{
	valid = false;
	time = new TimeStamp(dt_string);
	date = new DateStamp(dt_string);
	this->initialized = true;
}

DateTime::DateTimeStamp::DateTimeStamp(const DateTime::DateTimeStamp& on_copy)
{
	this->valid = on_copy.valid;
	this->initialized = on_copy.initialized;
	this->date = on_copy.date;
	this->time = on_copy.time;
}

bool DateTime::DateTimeStamp::is_valid(bool raise_exceptions)
{
	bool date_valid = date->is_valid(raise_exceptions) or date->initialized;
	bool time_valid = time->is_valid(raise_exceptions) or time->initialized;
	valid = time_valid or date_valid;
	return valid;
}

bool DateTime::DateTimeStamp::after(DateTimeStamp& compare_with)
{
	if (not(this->valid and compare_with.valid)) {
		throw "Can't compare with invalid date!";
	}
	long long sec_this = this->to_seconds();
	long long sec_comp = compare_with.to_seconds();
	return sec_this > sec_comp;
}

long long DateTime::DateTimeStamp::to_seconds()
{
	long long secs = 0;
	if (time->valid) {
		secs += time->to_seconds();
	}
	if (date->valid) {
		secs += date->to_seconds();
	}
	return secs;
}

std::string DateTime::DateTimeStamp::to_string()
{
	std::stringstream on_ret;
	if (this->date->valid) {
		on_ret << date->to_string() << ' ';
	}
	if (this->time->valid) {
		on_ret << time->to_string();
	}
	return on_ret.str();
}

DateTime::TimeStamp  DateTime::DateTimeStamp::getTime()
{
	return (*this->time);
}

DateTime::DateStamp DateTime::DateTimeStamp::getDate()
{
	return *date;
}

bool DateTime::DateTimeStamp::only_time()
{
	return time->initialized and time->valid and not date->initialized and not date->valid;
}

bool DateTime::DateTimeStamp::only_date()
{
	return date->initialized and date->valid and not time->initialized and not time->valid;
}

bool DateTime::DateTimeStamp::full_datetime()
{
	return date->valid and time->valid;
}

DateTime::DateStamp::DateStamp(std::string date_string): day(-1), month(-1), year(-1)
{
	std::regex date_regex = std::regex(
		"(\\d{2})\.(\\d{2})\.(\\d{4})"
	);
	std::smatch date_match; // 1 - day, 2 - month, 3 - year
	auto found = std::regex_search(
		date_string, date_match, date_regex
	);
	if (found) {
		this->initialized = true;
		this->day = std::stoi(date_match[1]);
		this->month = std::stoi(date_match[2]);
		this->year = std::stoi(date_match[3]);
	}
}

bool DateTime::DateStamp::is_valid(bool raise_exceptions)
{
	if (not this->initialized)
		return false;
	try {
		short on_valid[3] = { day, month, year };
		short* validated_time = this->validate(on_valid);
		this->day = validated_time[0];
		this->month = validated_time[1];
		this->year = validated_time[2];
		this->valid = true;
	}
	catch (std::exception& e) {
		this->valid = false;
		if (raise_exceptions) {
			throw e;
		}
		else {
			std::cout << e.what();
		}
	}
	return valid;
	return false;
}

short* DateTime::DateStamp::validate(short value[])
{
	short year = value[2];
	short month = value[1];
	short day = value[0];
	short max_days[12] = {
			31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	if (year % 4 == 0) {// leap year
		max_days[2 - 1] = 29; // february
	}
	if (0 < month < 12) {
		if (not (0 < day < max_days[month - 1]))
			throw std::invalid_argument("Invalid day!");
	}
	else {
		throw std::invalid_argument("Invalid month!");
	}
	if (year < 0) {
		throw std::invalid_argument("Invalid year");
	}
	return value;
}

long long DateTime::DateStamp::to_seconds()
{
	return (long long)this->year * 365 * 24 * 60 * 60 + (long long)this->month * 30 * 86400 + (long long)this->day * 86400; // kill me please
}

bool DateTime::DateStamp::after(DateStamp& compare_date)
{
	return this->to_seconds() > compare_date.to_seconds();
}

std::string DateTime::DateStamp::to_string()
{
	std::stringstream on_ret;
	on_ret << day << '.' << month << '.' << year;
	return on_ret.str();
}

DateTime::TimeStamp::TimeStamp(std::string& time_string): hour(0), minute(0), second(0), Validator()
{
	std::regex time_regex = std::regex(
		"(\\d{2}):(\\d{2}):(\\d{2})"
	);
	std::smatch time_match; // 1 - day, 2 - month, 3 - year
	auto found = std::regex_search(
		time_string, time_match, time_regex
	);
	if (found) {
		this->initialized = true;
		this->hour = std::stoi(time_match[1]);
		this->minute = std::stoi(time_match[2]);
		this->second = std::stoi(time_match[3]);
	}
}

bool DateTime::TimeStamp::is_valid(bool raise_exceptions)
{
	if (not this->initialized)
		return false;
	try {
		short on_valid[3] = { hour, minute, second };
		short* validated_time = this->validate(on_valid);
		this->hour = validated_time[0];
		this->minute = validated_time[1];
		this->second = validated_time[2];
		this->valid = false;
	}
	catch (std::exception& e) {
		this->valid = false;
		std::cout << e.what()<<std::endl;
		if (raise_exceptions) {
			throw e;
		}
	}
	return valid;
}

short* DateTime::TimeStamp::validate(short value[])
{
	short hour = value[0];
	short minute = value[1];
	short second = value[2];
	bool assertion = 0 <= hour < 24;
	if (not (0<=hour<24)){
		throw std::invalid_argument("Invalid hour!");
	}
	if (not (0 <= minute < 60)) {
		throw std::invalid_argument("Invalid minute!");
	}
	if (not (0 <= second < 60)) {
		throw std::invalid_argument("Invalid second!");
	}
	return value;
}

int16_t DateTime::TimeStamp::to_seconds()
{
	return this->hour*60*60+this->minute*60+this->second;
}

std::string DateTime::TimeStamp::to_string()
{
	std::stringstream on_ret;
	on_ret << this->hour << ':' << this->minute << ':' << this->second;
	return on_ret.str();
}

