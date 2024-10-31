#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "expression_handler.hpp"

int main(int argc, char** argv) {
    std::ifstream inputFile;
    if (argc == 2) {
        inputFile.open(argv[1]);
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open file: " << argv[1] << '\n';
            return 1;
        }
    }
    std::istream& input = (argc == 2 ? inputFile : std::cin);

    try {
        poleleyko::Stack<long long> results;
        std::string line;

        while (std::getline(input, line)) {
            if (line.empty()) {
                continue;
            }
            poleleyko::ExpressionHandler expression(line);
            results.push(expression.evaluate());
        }

        if (!results.empty()) {
            std::cout << results.top();
            results.pop();
        }
        while (!results.empty()) {
            std::cout << ' ' << results.top();
            results.pop();
        }
        std::cout << '\n';
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
