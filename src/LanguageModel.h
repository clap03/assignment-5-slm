#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include <string>
#include <map>
#include <set>

class LanguageModel {
private:
    int k;
    std::map<std::string, int> frequencies;
    std::map<std::string, std::map<char, int>> transitions;
    std::set<char> alphabet;

public:
    LanguageModel(int k);
    void train(const std::string & text);
    void printFrequencies() const;
    void printTransitions() const;
    void printAlphabet() const;
};


#endif