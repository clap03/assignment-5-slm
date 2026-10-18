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

string TextGenerator::generate(
    const string& start,
    int length,
    double alpha
) {
    string result = start;
    string gram = start;

    while(result.size() < static_cast<size_t>(length)) {

        char next;

        try {
            next = generateNext(gram, alpha);
        }
        catch(const runtime_error&) {
            break;
        }

        result += next;
        gram = gram.substr(1) + next;
    }

    return result;
}

string TextGenerator::generateStart() {

    const auto& frequencies = model.getFrequencies();

    vector<string> grams;
    vector<double> weights;

    for(const auto& entry : frequencies) {
        grams.push_back(entry.first);
        weights.push_back(entry.second);
    }

    if(grams.empty()) {
        throw runtime_error("No k-grams available");
    }

    discrete_distribution<int> distribution(
        weights.begin(), weights.end()
    );

    int index = distribution(generator);

    return grams[index];
}