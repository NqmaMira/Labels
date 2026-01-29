#pragma once
#include "LabelDecorator.h"
#include "HelpProvider.h"

class HelpLabel : public LabelDecorator {
private:
    std::shared_ptr<HelpProvider> helpProvider;
public:
    HelpLabel(std::shared_ptr<Label> label, std::shared_ptr<HelpProvider> helpProvider);

    std::string getHelpText() const;
    static std::shared_ptr<Label> create(std::shared_ptr<Label> label, std::shared_ptr<HelpProvider> helpProvider);
};