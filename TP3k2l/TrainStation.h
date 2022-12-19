#pragma once
#ifndef __TRAIN_STATION__
#include "Train.h"
#include "List.h"
#include <algorithm>
class TrainStation {
private:
	List<Train> trains;
public:
	TrainStation() : trains() {};
	void operator+=(Train tr);
	void operator--();
	Train* sort_by_target();
	List<Train> after(DateTime::DateTimeStamp dt);
};

#endif // !__TRAIN_STATION__
