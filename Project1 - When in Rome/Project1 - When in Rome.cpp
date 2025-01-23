#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
    std::cout << "Roman/Arabic converter, (c) 2025 - Eunjin Hwang\ntype 'quit' to exit.\n" << std::endl;

    while (true) {
        std::cout << "Enter a roman or arabic number: ";
        std::string input;
        std::cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) {
            return std::toupper(c);
            });

        if (input == "QUIT") {
            return 0;
        }

        if (input == "0") {
            std::cout << "The input value must be greater than equal to 1. Please try again." << std::endl;
        }

        bool isArabic = false;
        bool isRoman = false;
        for (char c : input) {
            if (!isArabic && isdigit(c)) {
                isArabic = true;
            }
            if (!isRoman && !isdigit(c)) {
                isRoman = true;
            }
        }

        std::vector<std::pair<int, std::string>> symbols = {
                {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},{100, "C"}, {90, "XC"},
                {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"},{1, "I"}, {0, "S"}, {0, "."}
        };

        if (isArabic && !isRoman) {
            std::string result = "";
            int integerPart = std::stoi(input);
            double fractionPart = std::stod(input) - integerPart;

            for (auto& symbol : symbols) {
                while (integerPart >= symbol.first && symbol.second != "S" && symbol.second != ".") {
                        result += symbol.second;
                        integerPart -= symbol.first;        
                }
            }
            if (fractionPart > 0) {
                if (fractionPart >= 0.5) {
                    result += "S";
                    fractionPart -= 0.5;
                }
                int fractionValue = floor(fractionPart * 12);
                for (int i = 0; i < fractionValue; ++i) {
                    result += ".";
                }
            }
            
            std::cout << input << " is " << result << std::endl;
        }
        else if (isRoman && !isArabic) {
            int i = 0;
            double result = 0;
            std::string s = "";
            s += input[i];

            for (auto symbol = symbols.begin(); symbol != symbols.end(); symbol++) {
                while (s == symbol->second) {
                    if (s == "S") {
                        result = (result * 2 + 1) / 2;
                    }

                    if (s == ".") {
                        result += 1 / (double)12;
                    }

                    result += symbol->first;
                    s = input[++i];
                }

                if (i == input.length()) {
                    std::cout << input << " is " << result << std::endl;
                    break;
                }

                s += input[++i];

                auto nextSymbol = std::next(symbol);
                if (!(nextSymbol != symbols.end() && s == nextSymbol->second)) {
                    s = s[0];
                    i--;
                }
            }

            /*if (result == 0) {
                std::cout << "You have entered an invalid character. Please try again." << std::endl;
            }*/
        }
        else {
            std::cout << "Invalid input. Please enter either a Roman numeral or an Arabic number." << std::endl;
        }
    }
    return 0;
}


