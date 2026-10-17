#include "LanguageModel.h"
#include <iostream>

using namespace std;

LanguageModel::LanguageModel(int k) : k(k) {
}

void LanguageModel::train(const string& text) {
    frequencies.clear();

    for(size_t i = 0; i + k <= text.size(); ++i) {
        string gram = text.substr(i , k);

        ++frequencies[gram]; 
    }
}

void LanguageModel::printFrequencies() const {
    for(const auto& entry : frequencies) {
        cout << entry.first << " : " << entry.second << '\n'; 
    }
}