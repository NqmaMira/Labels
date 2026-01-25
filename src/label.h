#pragma once
#include <string>

class label {
public:
	virtual ~label() = default;
	virtual std::string getText() const = 0;
};