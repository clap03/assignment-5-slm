#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include <string>
#include <map>

class LanguageModel {
private:
    int k;
    std::map<std::string, int> frequencies;

public:
    LanguageModel(int k);
    void train(const std::string & text);
    void printFrequencies() const;
};


#endif