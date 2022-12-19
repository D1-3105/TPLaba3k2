#ifndef __TRAIN__
#define __TRAIN__
#include <string>
#include <iostream>
#include <fstream>
#include "DateTime.h"


class Train {
private:
	std::string target;
	std::string train_number;
	DateTime::DateTimeStamp dt_departure;
public:
	explicit Train(): target(""), train_number(""), dt_departure() {};
	Train(const Train& on_copy);
	Train(std::string& target, std::string& train_number, DateTime::DateTimeStamp& dt_departure);
	std::string getTarget();
	DateTime::DateTimeStamp getDeparture();
	void WriteTrainInfo(std::ostream& out_stream);

};



#endif