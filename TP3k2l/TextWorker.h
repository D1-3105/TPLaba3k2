#pragma once
#include <regex>
#include <fstream>
#include <string>
#include <sstream>
#include "Validator.h"
class TextWorker: public Validator {
private:
	std::ifstream* inp;
public:
	TextWorker(std::string filepath);
	TextWorker() : inp(){};
	void setInput(std::string filepath);
	TextWorker(const TextWorker& on_copy);
	~TextWorker() {
		if (inp!= 0 and inp->is_open()) {
			inp->close();
		}
	}
	bool is_valid(bool raise_exceptions=false) override;
	int process();
};