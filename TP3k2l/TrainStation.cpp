#include "TrainStation.h"

void TrainStation::operator+=(Train tr)
{
	trains.push_back(tr);
}

void TrainStation::operator--()
{
	trains.pop();
}

Train* TrainStation::sort_by_target()
{
	Train* train_arr = trains.to_array();
	auto comparator = [](Train& tr1, Train& tr2) {
		return tr1.getTarget() < tr2.getTarget();
	};
	std::sort(train_arr, &train_arr[trains.getLength()], comparator);
	return train_arr;
}

List<Train> TrainStation::after(DateTime::DateTimeStamp dt)
{
	List<Train> after_list;
	for (size_t cursor = 0; cursor < trains.getLength(); cursor++) {
		DateTime::DateTimeStamp cur_dt = trains[cursor].getDeparture();
		DateTime::TimeStamp ts = dt.getTime();
		bool only_date_check = (dt.only_date() or dt.full_datetime()) and (cur_dt.only_date() or cur_dt.full_datetime()) and cur_dt.after(dt);
		bool only_time_check = (dt.only_time() or cur_dt.full_datetime()) and (cur_dt.only_date() or cur_dt.full_datetime()) and cur_dt.after(dt);
		bool full_datetime_check = cur_dt.after(dt);
		if (
			only_date_check or only_time_check or full_datetime_check
		) {
			after_list.push_back(trains[cursor]);
		}
	}
	return after_list;
}
