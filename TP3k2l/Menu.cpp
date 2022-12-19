#include "Menu.h"


void Menu::first_task()
{
	int choice = 0;
	while (choice != -1) {

		std::cout << "\t1. Push train to station" << std::endl;
		std::cout << "\t2. Pop last train from station" << std::endl;
		std::cout << "\t3. Filter by date" << std::endl;
		std::cout << "\t4. Sort by target name" << std::endl;
		std::cout << "\t5. Output all trains" << std::endl;
		std::cout << "\t-1. Change task" << std::endl << "->";

		std::cin >> choice;
		this->process_choice_1task(choice);
	}
}

void Menu::process_choice_1task(int choice)
{
	switch (choice) {
	case 1:
		this->input_train();
		break;
	case 2:
		try {
			(*(this->train_station_ptr)).pop();
			std::cout << "Success" << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		break;
		case 3: {
			std::cout << "Enter date of issue as <DD.MM.YYYY HH:MM:SS>:";
			std::string dt_str;
			getchar();
			std::getline(std::cin, dt_str);
			DateTime::DateTimeStamp dts(dt_str);
			try {
				dts.is_valid(true);
				List<Train> filtered = this->train_station_ptr->after(dts);
				this->output_train_list(filtered);
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			break;
		}
		case 4: {
			Train* sorted = this->train_station_ptr->sort_by_target();
			for (int i = 0; i < train_station_ptr->getList().getLength(); i++) {
				this->output_train(sorted[i]);
			}
			break;
		}
	case 5:
		List<Train> trains = this->train_station_ptr->getList();
		this->output_train_list(trains);
		break;
	}
	system("pause");
	system("cls");
}

void Menu::input_train()
{
	std::cout << "\tEnter target:";
	std::string target;
	std::cin >> target;
	std::cout << "\tEnter train-number:";
	std::string train_number;
	std::cin >> train_number;
	std::cout << "\tEnter date-time of departure as <DD.MM.YYYY HH:MM:SS>:";
	std::string dt_str;
	getchar();
	std::getline(std::cin, dt_str);
	DateTime::DateTimeStamp dts(dt_str);
	try {
		dts.is_valid(true);
		Train tr(target, train_number, dts);
		this->train_station_ptr->operator+=(tr);
		this->output_train(tr);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void Menu::output_train(Train tr)
{
	std::cout << "====================================" << std::endl;
	tr.WriteTrainInfo(std::cout);
}

void Menu::output_train_list(List<Train>& train_list)
{
	if (train_list.getLength() == 0) {
		std::cout << "List is empty!" << std::endl;
	}
	for (int i = 0; i < train_list.getLength(); i++) {
		std::cout << "===================================" << std::endl;
		this->output_train(train_list[i]);
	}
	std::cout << "===================================" << std::endl;

}

void Menu::perform_tests()
{
	Tests::TimeTester test_dt;
	std::cout << "DATE TIME TEST PERFORMED - OK" << std::endl;
	Tests::TrainTester test_train;
	std::cout << "TRAIN TEST PERFORMED - OK" << std::endl;
	Tests::ListTester test_list;
	std::cout << "FORWARD LIST TEST PERFORMED - OK" << std::endl;
	Tests::TrainStationTest test_station;
	std::cout << "TRAIN STATION TEST PERFORMED - OK" << std::endl;
	Tests::TextProcessorTest test_text_proc;
	std::cout << "TEXT PROCESSOR TEST PERFORMED - OK" << std::endl;
	system("pause");
	system("cls");
}

void Menu::second_task()
{
	std::string fp;
	std::cout << "Enter filepath: ";
	std::cin >> fp;
	try {
		this->text_worker_ptr->setInput(fp);
		int answer = this->text_worker_ptr->process();
		std::cout << "Number of words with <5 letters:" << answer << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	system("pause");
	system("cls");
	
}

void Menu::loop_menu()
{
	int choice= 0;
	while (choice!=-1) {
		std::cout << "\t1. Perform tests" << std::endl;
		std::cout << "\t2. First task" << std::endl;
		std::cout << "\t3. Second task" << std::endl;
		std::cout << "\t-1. Exit" << std::endl << "->";
		std::cin >> choice;
		system("cls");
		this->make_choice(choice);
	}
}

void Menu::make_choice(int choice)
{
	switch (choice)
	{
	case 1:
		this->perform_tests();
		break;
	case 2:
		this->first_task();
		break;
	case 3:
		this->second_task();
	default:
		break;
	}
}
