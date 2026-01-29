#include "HelpLabel.h"
#include "RichHelpLabel.h"

HelpLabel::HelpLabel(std::shared_ptr<Label> label, std::shared_ptr<HelpProvider> helpProvider)
    : LabelDecorator(std::move(label), nullptr), helpProvider(std::move(helpProvider)) { }

std::string HelpLabel::getHelpText() const {
    return helpProvider ? helpProvider->getHelp() : "No help available.";
}

std::shared_ptr<Label> HelpLabel::create(std::shared_ptr<Label> label, std::shared_ptr<HelpProvider> helpProvider) {
    if (LabelDecorator::isRichLabel(label)) {
        return std::make_shared<RichHelpLabel>(label, helpProvider);
    }
    return std::make_shared<HelpLabel>(label, helpProvider);
}