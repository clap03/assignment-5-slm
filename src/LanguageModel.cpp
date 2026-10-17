#include "LanguageModel.h"
#include <iostream>

using namespace std;

LanguageModel::LanguageModel(int k) : k(k) {
}

void LanguageModel::train(const string& text) {
    frequencies.clear();
    transitions.clear();

    for(size_t i = 0; i + k <= text.size(); ++i) {
        string gram = text.substr(i , k);

        ++frequencies[gram]; 

        if(i + k < text.size()) {
            char next = text[i + k];
            ++transitions[gram][next];

        }
    }
}

void LanguageModel::printFrequencies() const {
    for(const auto& entry : frequencies) {
        cout << entry.first << " : " << entry.second << '\n'; 
    }
}

void LanguageModel::printTransitions() const {
   for(const auto& entry : transitions) { 
    for(const auto& next : entry.second) {
        cout << entry.first << " -> "
             << next.first << " : "
             << next.second << '\n';

    }
  }
}