#pragma once
#include "Label.h"
#include <string>
#include <iostream>

class CustomLabel : public Label {
private:
    mutable std::string cachedText;
    mutable int accessCount;
    int timeout;

    void fetchText() const;
public:
    explicit CustomLabel(int timeout = 5);
    std::string getText() const override;
};