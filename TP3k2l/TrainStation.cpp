#include "TrainStation.h"

void TrainStation::operator+=(Train tr)
{
	trains.push_back(tr);
}

Train TrainStation::pop()
{
	if (trains.getLength() > 0) {
		return trains.pop();
	}
	else {
		throw std::exception("Station is empty!");
	}
	
}

Train* TrainStation::sort_by_target()
{
	Train* train_arr = trains.to_array();
	for (int i = 0; i < trains.getLength() - 1; i++)
		for (int j = i + 1; j < trains.getLength(); j++) {
			if (strcmp(train_arr[i].getTarget().c_str(), train_arr[j].getTarget().c_str()) > 0)
			{
				Train cur = train_arr[i];
				train_arr[i] = train_arr[j];
				train_arr[j] = cur;
			}
		}
	return train_arr;
}

List<Train> TrainStation::after(DateTime::DateTimeStamp dt)
{
	List<Train> after_list;
	if (dt.only_date()) {
		DateTime::DateStamp ds = dt.getDate();
		for (size_t cursor = 0; cursor < trains.getLength(); cursor++) {
			DateTime::DateTimeStamp cur_dt = trains[cursor].getDeparture();

			bool check = (cur_dt.only_date() or cur_dt.full_datetime()) and cur_dt.getDate().after(ds);
			if (
				check
				) {
				after_list.push_back(trains[cursor]);
			}
		}
	}
	else if (dt.only_time()) {
		DateTime::TimeStamp ds = dt.getTime();
		for (size_t cursor = 0; cursor < trains.getLength(); cursor++) {
			DateTime::DateTimeStamp cur_dt = trains[cursor].getDeparture();
			bool check = (cur_dt.only_time() or cur_dt.full_datetime()) and cur_dt.getTime().after(ds);
			if (
				check
				) {
				after_list.push_back(trains[cursor]);
			}
		}
	}
	else if (dt.full_datetime()) {
		for (size_t cursor = 0; cursor < trains.getLength(); cursor++) {
			DateTime::DateTimeStamp cur_dt = trains[cursor].getDeparture();
			bool check = (cur_dt.full_datetime()) and cur_dt.after(dt);
			if (
				check
				) {
				after_list.push_back(trains[cursor]);
			}
		}
	}
	else {
		for (size_t cursor = 0; cursor < trains.getLength(); cursor++) {
			DateTime::DateTimeStamp cur_dt = trains[cursor].getDeparture();
			bool check = cur_dt.after(dt);
			if (
				check
				) {
				after_list.push_back(trains[cursor]);
			}
		}
	}
	return after_list;
}

List<Train> TrainStation::getList()
{
	return trains;
}
