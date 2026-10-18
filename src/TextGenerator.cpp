#include "TextGenerator.h"

#include <vector>
#include <stdexcept>

using namespace std;

TextGenerator::TextGenerator(const LanguageModel& model)
:model(model), generator(random_device{}()) {
}

char TextGenerator::generateNext(const string& gram, double alpha) {
    map<char, double> weights = model.getWeights(gram, alpha);

    vector<char> characters;
    vector<double> probabilities;

    for(const auto& entry : weights) {
        characters.push_back(entry.first);
        probabilities.push_back(entry.second);
    }

    double total = 0;

    for(double weight : probabilities) {
        total += weight;
    }

    if(total == 0) {
        throw runtime_error("No available transitions");
    }

    discrete_distribution<int> distribution(
        probabilities.begin(), probabilities.end()
    );

    int index = distribution(generator);
    
    return characters[index];
}