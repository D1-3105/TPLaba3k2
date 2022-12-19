#pragma once
class Validator {
public:
	bool valid;
	bool initialized;
	Validator() : valid(false), initialized(false) {};
	virtual bool is_valid(bool raise_exceptions = false) = 0;
};