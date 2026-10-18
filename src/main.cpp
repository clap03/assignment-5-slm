#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "LanguageModel.h"
#include "TextGenerator.h"

using namespace std;

int main() {
    ifstream file("input.txt");

    if(!file) {
        cerr << "slm : Cannot open file\n";
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();

    string text = buffer.str();

    LanguageModel model(2);

    model.train(text);
    map<char, double> weights = model.getWeights("ba", 1.0);

    cout << "Weights for ba:\n";
    for(const auto& entry : weights) {
        cout << entry.first << " : " << entry.second << '\n';
    }

    TextGenerator textGenerator(model);

    cout << "Generated characters:";

    for(int i = 0; i < 10; ++i) {
        cout << textGenerator.generateNext("ba", 1.0);
    }

    cout << '\n';

    model.printFrequencies();
    model.printTransitions();
    model.printAlphabet();

    cout << "Training completed\n";

    return 0;
}