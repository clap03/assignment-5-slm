#ifndef TEXTGENERATOR_H
#define TEXTGENERATOR_H

#include <random>
#include "LanguageModel.h"

class TextGenerator {
    private:
    const LanguageModel& model;
    std::mt19937 generator;

    public:
    TextGenerator(const LanguageModel& model);

    char generateNext(const std::string& gram, double alpha);

};



#endif
