#pragma once
#include "CensorTransformation.h"
#include <map>
#include <memory>
#include <string>

class CensorFactory {
private:
    static std::map<std::string, std::shared_ptr<CensorTransformation>> cache;

public:
    static std::shared_ptr<CensorTransformation> getCensor(const std::string& word);
};