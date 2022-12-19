#include "tests.h"

void Tests::TimeTester::_test_constructor_datetimestamp()
{
	std::string date_string1 = "18.12.2022 21:18:00";
	std::string date_string2 = "22.12.2022 21:22:00";
	DateTime::DateTimeStamp dts1(date_string1); // only date
	dts1.is_valid(true);
	DateTime::DateTimeStamp dts2(date_string2);
	dts2.is_valid(true);
	assert(dts2.after(dts1));
}

void Tests::TimeTester::_test_constructor_timestamp()
{
	std::string t_string1 = "21:08:00";
	std::string t_string2 = "21:08:01";
	DateTime::TimeStamp ts1(t_string1);
	DateTime::TimeStamp ts2(t_string2);
	ts1.is_valid(true);
	ts2.is_valid(true);
	assert(ts2.after(ts1));
}

void Tests::TimeTester::_test_constructor_datestamp()
{
	std::string date_string1 = "18.12.2022";
	std::string date_string2 = "22.12.2022";
	DateTime::DateTimeStamp ds1(date_string1); // only date
	ds1.is_valid(true);
	DateTime::DateTimeStamp ds2(date_string2);
	ds2.is_valid(true);
	assert(ds2.after(ds1));
}

Tests::TimeTester::TimeTester()
{
	this->_test_constructor_timestamp();
	this->_test_constructor_datestamp();
	this->_test_constructor_datetimestamp();
}

void Tests::TrainTester::setUp()
{
	this->target = "Kosovo";
	this->train_number = "3322:A";
	std::string dtstring = "19.12.2022 00:55:00";
	dtstamp = DateTime::DateTimeStamp(dtstring);
	dtstamp.is_valid(true);
	
}

void Tests::TrainTester::_test_train_creation()
{
	this->setUp();
	Train train(target, train_number, dtstamp);
	assert(train.getTarget() == target);
}

Tests::TrainTester::TrainTester()
{
	this->_test_train_creation();
}

void Tests::ListTester::setUp(int* on_push_back, size_t size)
{
	list = List<int>();
	
	for (int i = 0; i < size; i++)
		list.push_back(on_push_back[i]);
}

void Tests::ListTester::_test_push_back_list(bool teardown)
{
	int len = 4;
	int on_push_back[] = { 22, 33, 44, 143 };
	this->setUp(on_push_back, len);
	for (int i = 0; i < len; i++) {
		int ret = list[i];
		int cur = on_push_back[i];
		assert(ret == cur);
	}
	if (teardown) {
		for (int i = 0; i < len; i++)
			list.pop();
	}
}

void Tests::ListTester::_test_pop_list()
{
	int len = 4;
	int on_push_back[] = {3,4,56,7};
	this->setUp(on_push_back, len);
	for (int i = 0; i < len; i++) {
		int pb_el = on_push_back[len - i - 1];
		int cur = list.pop();
		assert(cur == pb_el);
	}
}

void Tests::ListTester::_test_to_array_list()
{
	int arr[] = { 3,4,5,6,7 };
	this->setUp(arr, 5);
	int* ret_arr = this->list.to_array();
	for (int i = 0; i < 5; i++) {
		assert(arr[i] == ret_arr[i]);
	}
}

Tests::ListTester::ListTester()
{
	this->_test_push_back_list();
	this->_test_pop_list();
	this->_test_to_array_list();
}

void Tests::TrainStationTest::setUp()
{
	ts = TrainStation();
	this -> targets = new std::string[3];
	targets[0] = "SPB";
	targets[1] = "MSK";
	targets[2] = "Kiev";

	std::string departures[3] = {
		"19.12.2022 02:23:00", "19.12.2022 02:30:00", "20.12.2022 02:23:00"
	};
	
	std::string train_numbers[3] = {
		"123","124", "125"
	};
	for (int i = 0; i < 3; i++) {
		DateTime::DateTimeStamp dt = DateTime::DateTimeStamp(departures[i]);
		dt.is_valid(true);
		Train tr(targets[i], train_numbers[i], dt);
		this->ts += tr;
	}
	
}

void Tests::TrainStationTest::_test_sort_ts()
{
	std::sort(targets, &targets[3]);
	Train* sorted_arr = ts.sort_by_target();
	for (int i = 0; i < 3; i++) {
		assert(targets[i] == sorted_arr[i].getTarget());
	}
}

void Tests::TrainStationTest::_test_after_ts()
{
	std::string dts_string = "19.12.2022 05:30:00";
	DateTime::DateTimeStamp after_dt(dts_string);
	after_dt.is_valid(true);
	List<Train> trains = this->ts.after(after_dt);
}

Tests::TrainStationTest::TrainStationTest()
{
	this->setUp();
	this->_test_sort_ts();
	this->_test_after_ts();
}
