#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cmath>

#include "LanguageModel.h"
#include "TextGenerator.h"

using namespace std;

int parseInt(const string& value) {
    if(value.empty()) {
        throw invalid_argument("Invalid integer: " + value);
    }

    for(char c : value) {
        if (c < '0' || c > '9') {
            throw invalid_argument("Invalid integer: " + value);
        }
    }
    
    size_t pos = 0;
    int number = stoi(value, &pos);

    if (pos != value.size()) {
        throw invalid_argument("Invalid integer: " + value);
    }

    return number;
}

double parseDouble(const string& value) {
    size_t pos = 0;

    double number = stod(value, &pos);

    if(pos != value.size()) {
        throw invalid_argument("Invalid alpha: " + value);
    }

    if(!isfinite(number)) {
        throw invalid_argument("Alpha must be finite");
    }

    return number;
}

int main(int argc, char* argv[]) {

    try {
        double alpha = 0.0;
        int k;
        int length;
        string filename;

        if(argc == 4) {
            k = parseInt(argv[1]);
            filename = argv[2];
            length = parseInt(argv[3]);
        }

        else if(argc == 6 && string(argv[1]) == "-a") {
            alpha = parseDouble(argv[2]);
            k = parseInt(argv[3]);
            filename = argv[4];
            length = parseInt(argv[5]);
        }

        else {
            throw invalid_argument("Invalid arguments");
        }

        if(k <= 0) {
            throw invalid_argument("k must be positive");
        }

        if(length <= 0) {
            throw invalid_argument("length must be positive");
        }

        if(length < k) {
            throw invalid_argument("length must be at least k");
        }

        if(alpha < 0.0) {
            throw invalid_argument("alpha must be non-negative");
        }

        ifstream file(filename);

        if(!file) {
            throw runtime_error("Cannot open file");
        } 

        stringstream buffer;
        buffer << file.rdbuf();

        string text = buffer.str();

        if(text.size() <= static_cast<size_t>(k)) {
            throw invalid_argument("Training text  must be longer than k");
        }

        LanguageModel model(k);
        model.train(text);

        TextGenerator textGenerator(model);

        string start = textGenerator.generateStart();

        cout << textGenerator.generate(start, length, alpha) << '\n';
    }

    catch(const exception& e) {
        cerr << "slm: " << e.what() << '\n';
        return 1;
    }

    return 0;


}