#pragma once
#include "DateTime.h"
#include "List.h"
#include "Train.h"
#include "TrainStation.h"
#include <assert.h>

namespace Tests {
	class TimeTester {
	public:
		void _test_constructor_datetimestamp();
		void _test_constructor_timestamp();
		void _test_constructor_datestamp();
		TimeTester();
	};
	class TrainTester {
	private:
		DateTime::DateTimeStamp dtstamp;
		std::string target;
		std::string train_number;
	public:
		void setUp();
		void _test_train_creation();
		TrainTester();
	};

	class ListTester {
	private:
		List<int> list;
	public:
		void setUp(int* on_push_back, size_t size);
		void _test_push_back_list(bool teardown=true);
		void _test_pop_list();
		void _test_to_array_list();
		ListTester();
	};
	class TrainStationTest {
	private:
		TrainStation ts;
		std::string *targets;
	public:
		void setUp();
		void _test_sort_ts();
		void _test_after_ts();
		TrainStationTest();
	};
};

