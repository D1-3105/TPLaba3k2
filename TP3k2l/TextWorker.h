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
	TextWorker(const TextWorker& on_copy);
	~TextWorker() {
		inp->close();
	}
	bool is_valid(bool raise_exceptions=false) override;
	int process();
};