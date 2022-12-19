#include "Train.h"

Train::Train(const Train& on_copy)
{
	target = on_copy.target;
	train_number = on_copy.train_number;
	dt_departure = on_copy.dt_departure;
}

Train::Train(std::string& target, std::string& train_number, DateTime::DateTimeStamp& dt_departure)
{
	this->target = target;
	this->train_number = train_number;
	if (dt_departure.valid)
		this->dt_departure = dt_departure;
	else
		throw "Invalid departure";
}

std::string Train::getTarget()
{
	return target;
}

DateTime::DateTimeStamp Train::getDeparture()
{
	return dt_departure;
}

//void Train::WriteTrainInfo(std::ostream& out_stream)
//{
//	if (std::addressof(out_stream) == std::addressof(std::cout)) {
//		out_stream << "\tTARGET:\t" << target << std::endl;
//		out_stream << "\tNUMBER:\t" << train_number << std::endl;
//		out_stream << "\tDEPARTURE:\t" << dt_departure.to_string() << std::endl;
//	}
//	else {
//		out_stream << target << '\n' << train_number << '\n' << dt_departure.to_string() << '\n';
//	}
//}
//
//void Train::ReadTrainInfo(std::istream& inp_stream)
//{
//	if (std::addressof(inp_stream) == std::addressof(std::cin)) {
//		std::cout << "Target: " << std::endl;
//		std::cin >> target;
//		std::cout << "Train number: " << std::endl;
//		std::cin >> train_number;
//		std::cout << "Departure: " << std::endl;
//		getchar();
//		std::string dt_string;
//		std::getline(std::cin, dt_string);
//		dt_departure = DateTime::DateTimeStamp(dt_departure);
//	}
//}
