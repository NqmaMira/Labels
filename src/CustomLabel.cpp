#include "CustomLabel.h"

CustomLabel::CustomLabel(int timeout)
    : cachedText(""), accessCount(0), timeout(timeout) { }

void CustomLabel::fetchText() const {
    std::cout << "Enter label text: ";
    std::getline(std::cin, cachedText);
    accessCount = 0;
}

std::string CustomLabel::getText() const {
    if (cachedText.empty() || accessCount >= timeout) {
        fetchText();
    }
    accessCount++;
    return cachedText;
}