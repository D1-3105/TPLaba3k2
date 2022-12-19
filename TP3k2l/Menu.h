#pragma once
#include "tests.h"
#include <string>
#include "DateTime.h"
#include "TrainStation.h"
#include "Train.h"

class Menu {
protected:
	void process_choice_1task(int choice);
	void input_train();
	void output_train(Train tr);
	void output_train_list(List<Train>& train_list);
private:
	TrainStation* train_station_ptr;
	TextWorker* text_worker_ptr;
public:
	Menu() : text_worker_ptr(new TextWorker()), train_station_ptr(new TrainStation()) {};
	~Menu() {
		delete text_worker_ptr;
		delete train_station_ptr;
	}
	void perform_tests();
	void first_task();
	void second_task();
	void loop_menu();
	void make_choice(int choice);
};


