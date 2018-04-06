//
// Created by Roger Valderrama on 4/6/18.
//

#ifndef C_IDE_ASCIIPARSER_HPP
#define C_IDE_ASCIIPARSER_HPP

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

class ASCIIParser {
public:
    const char *text;

    ASCIIParser();

    int convert();

    int charlength(char *num);

    double charToint(char *num);

    ASCIIParser(const char *text);

    double auxcharlength(int num2);
};


#endif //C_IDE_ASCIIPARSER_HPP
