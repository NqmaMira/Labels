#pragma once
#include "HelpProvider.h"

class SimpleHelpProvider : public HelpProvider {
private:
    std::string helpText;
public:
    explicit SimpleHelpProvider(std::string text);
    std::string getHelp() const override;
};