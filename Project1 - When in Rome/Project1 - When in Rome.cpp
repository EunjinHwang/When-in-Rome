#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>

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
        bool isApostrophus = false;
        bool hasDot = false;
        for (char c : input) {
            if (c == '.') {
                hasDot = true;
            }
            if (!isArabic && isdigit(c)) {
                isArabic = true;
            }
            if (!isRoman && !isdigit(c) && c != '.') {
                isRoman = true;
            }

            if (!isApostrophus && c == ')') {
                isApostrophus = true;
            }
        }

        if (hasDot) {
            if (!isRoman && !isArabic) {
                isRoman = true;
            }

            if (!isRoman && isArabic) {
                if (input[0] == '.') {
                    std::string temp = "0";
                    temp += input;
                    input = temp;
                }
            }


        }

        std::vector<std::pair<int, std::string>> symbols = {
                {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},{100, "C"}, {90, "XC"},
                {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"},{1, "I"}, {0, "S"}, {0, "."}, {0, "-"}, {0, "_"}
        };

        if (isArabic && !isApostrophus) {
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
            if (result == "") {
                std::cout << "invalid Input" << std::endl;
            }
            else {
                std::cout << input << " is " << result << std::endl;
            }
        }
        else if (isRoman) {
            double result = 0;
            int i = 0;
            bool isEndReverseC = false;
            std::string temp = input;
            if (isApostrophus) {
                int c_num=0, i_num=0, rc_num = 0;
                while ((input[i] == 'C' || input[i] == 'I' || input[i] == ')') && !isEndReverseC)
                {
                    if (input[i] == ')') {
                        rc_num++;
                        if (i < input.length() && input[i+1] != ')') {
                            isEndReverseC = true;
                        }
                    }
                    else if (input[i] == 'C') c_num++;
                    else i_num++;
                    i++;
                }

                if (i_num > 1) {
                    std::cout << "Invalid input." << std::endl;
                    continue;
                }

                if (c_num > rc_num) {
                    std::cout << input << " contains unbalanced apostrophus." << std::endl;
                    continue;
                }
                input = input.substr(i - (rc_num - c_num));

                if (c_num > 0) {
                    result = 100;
                    for (int i = c_num; i > 0; i--) {
                        result *= 10;
                    }
                }

                if (rc_num - c_num > 0) {
                    int temp = 50;
                    for (int i = rc_num - c_num; i > 0; i--) {
                        temp *= 10;
                    }
                    result += temp;
                    input = input.substr(rc_num - c_num);
                }
                
                if (input.length() == 0) {
                    if (result == 0) {
                        std::cout << "invalid Input" << std::endl;
                    }
                    else {
                        std::cout << std::fixed << std::setprecision(0) << temp << " is " << result << std::endl;
                    }
                }
            }
            
            if (input.length() > 0) {
                i = 0;
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

                        if (input[i] == '-' || input[i] == '_') {
                            result *= 1000;
                            s = input[++i];
                            symbol = symbols.begin();
                        }
                    }

                    if (i == input.length()) {
                        std::cout << temp << " is " << result << std::endl;
                        break;
                    }

                    s += input[++i];
                    auto nextSymbol = std::next(symbol);
                    if (!(nextSymbol != symbols.end() && s == nextSymbol->second)) {
                        s = s[0];
                        i--;
                    }
                }
            }
        }
        else {
            std::cout << "Invalid input. Please enter either a Roman numeral or an Arabic number." << std::endl;
        }
    }
    return 0;
}


