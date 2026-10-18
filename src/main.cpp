#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "LanguageModel.h"
#include "TextGenerator.h"

using namespace std;

int main(int argc, char* argv[]) {

    try {
        double alpha = 0.0;
        int k;
        int length;
        string filename;

        if(argc == 4) {
            k = stoi(argv[1]);
            filename = argv[2];
            length = stoi(argv[3]);
        }

        else if(argc == 6 && string(argv[1]) == "-a") {
            alpha = stod(argv[2]);
            k = stoi(argv[3]);
            filename = argv[4];
            length = stoi(argv[5]);
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