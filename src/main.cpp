#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "LanguageModel.h"

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
    model.printFrequencies();
    model.printTransitions();
    model.printAlphabet();

    cout << "Training completed\n";

    return 0;
}