#include "TextWorker.h"

TextWorker::TextWorker(std::string filepath)
{
	this->inp = std::ifstream(filepath);
	if (not inp.is_open()) {
		throw "Invalid file";
	}
}

