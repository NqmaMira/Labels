#pragma once
#include <string>

class HelpProvider {
public:
    virtual ~HelpProvider() = default;
    virtual std::string getHelp() const = 0;
};