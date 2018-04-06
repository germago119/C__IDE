//
// Created by Roger Valderrama on 4/6/18.
//

#include "ASCIIParser.hpp"


ASCIIParser::ASCIIParser(const char *text1) {
    text = text1;

}

int ASCIIParser::convert() {
    int result = 0;
    for (int i = 0; text[i]; i++) {
        result += (int) text[i];
    }
    std::cout << "Convert Result: " << result << std::endl;
    return result;

}

double ASCIIParser::charToint(char *num) {
    int exc = charlength(num);
    std::cout << "Length: " << exc << std::endl;
    int a = 0;
    double b = 0;
    double result = 0;
    for (int i = 0; num[i]; i++) {
        b = auxcharlength(num[i]);
        a = static_cast<int>(b * pow(10, exc - 1));
        result = result + a;
        a, b = 0;
        exc--;
    }
    return result;
}

int ASCIIParser::charlength(char *num) {
    int length = 0;
    for (int i = 0; num[i]; i++) {
        length++;
    }
    return length;
}

double ASCIIParser::auxcharlength(int num2) {
    switch (num2) {
        case 48:
            return 0;
        case 49:
            return 1;
        case 50:
            return 2;
        case 51:
            return 3;
        case 52:
            return 4;
        case 53:
            return 5;
        case 54:
            return 6;
        case 55:
            return 7;
        case 56:
            return 8;
        case 57:
            return 9;
        default:
            return 0;
    }

}

ASCIIParser::ASCIIParser() = default;