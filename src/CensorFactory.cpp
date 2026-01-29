#include "CensorFactory.h"

//std::map<std::string, std::shared_ptr<CensorTransformation>> CensorFactory::cache;

std::shared_ptr<CensorTransformation> CensorFactory::getCensor(const std::string& word) {
    if (word.length() > 4) {
        return std::make_shared<CensorTransformation>(word);
    }

    auto it = cache.find(word);
    if (it != cache.end()) {
        return it->second;
    }

    auto newCensor = std::make_shared<CensorTransformation>(word);
    cache[word] = newCensor;
    return newCensor;
}