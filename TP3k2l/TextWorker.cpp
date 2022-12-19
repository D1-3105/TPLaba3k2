#include "TextWorker.h"

TextWorker::TextWorker(std::string filepath): Validator()
{
	this->inp = new std::ifstream(filepath.c_str());
}

TextWorker::TextWorker(const TextWorker& on_copy)
{
	this->valid = on_copy.valid;
	this->initialized = on_copy.initialized;
	this->inp = on_copy.inp;
}

bool TextWorker::is_valid(bool raise_exceptions)
{
	valid = this->inp->is_open();
	if (not valid and raise_exceptions)
		throw "Invalid file";
	return valid;
}

int TextWorker::process()
{
	if (!this->valid) {
		throw "Invalid file";
	}
	std::stringstream ss;
	ss << this->inp->rdbuf();
	std::string text = ss.str();
	ss.clear();
	std::regex four_letters_regex = std::regex("\\b[A-Za-zР-пр-џ]{1,4}\\b");
	std::string::const_iterator searcher(text.begin());
	std::smatch res;
	int matches = 0;
	while (std::regex_search(searcher, text.cend(), res, four_letters_regex)) {
		matches++;
		searcher = res.suffix().first;
	}
	return matches;
}

