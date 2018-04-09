//
// Created by Roger Valderrama on 4/6/18.
//

#ifndef C_IDE_NODEPREFIX_HPP
#define C_IDE_NODEPREFIX_HPP

#include <cstdio>
#include <cstring>
#include <iostream>
#include "NodeType.hpp"
#include "ASCIIParser.hpp"

enum TokenType {
    Mul,
    Div,
    Plus,
    Error,
    Equal,
    Minus,
    Number,
    Variable,
    EndOfText,
    Reference,
    OpenParenthesis,
    ClosedParenthesis
};

class NodePrefix {

    struct Token {
        TokenType Type;
        double Value;
        char Symbol;

    };
    int m_Index;
    Token m_crtToken;
    const char *m_Text;

private:
    NodeType *Term();

    NodeType *TermFirst();

    int GetVariable();

    double GetNumber();

    NodeType *Factor();

    int GetReference();

    void GetNextToken();

    NodeType *Expression();

    void SkipWhiteSpaces();

    NodeType *ExpressionFirst();

    void Match(char expected);

    bool Check(int type, char *text);

    NodeType *CreateNodeNumber(double value);

    NodeType *CreateUnaryNode(NodeType *left);

    NodeType *CreateNode(NType type, NodeType *left, NodeType *right);

public:
    explicit NodePrefix(const char *text);

    NodePrefix();
};


#endif //C_IDE_NODEPREFIX_HPP
