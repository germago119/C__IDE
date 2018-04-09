//
// Created by Roger Valderrama on 4/6/18.
//

#include "NodePrefix.hpp"

// To detect more easily the operator it will only check the first letter:
// float => f => 0
// double => d => 1
// int => i => 2
// long => l => 3
// char => c => 4
// struct => s => 5


using namespace std;

NodePrefix::NodePrefix() = default;

NodePrefix::NodePrefix(const char *text) {
    m_Text = text;
    m_Index = 0;
    cout << "Constructor" << endl;
    GetNextToken();
    Expression();
}

void NodePrefix::SkipWhiteSpaces() {
    while (isspace(m_Text[m_Index])) {
        cout << "whitespace, index: " << m_Index << endl;
        m_Index++;
    }
}

NodeType *NodePrefix::Expression() {
    cout << "ENTER EXPRESSION" << endl;
    NodeType *tempNode = Term();
    NodeType *firstExpressionNode = ExpressionFirst();
    return CreateNode(OperatorPlus, tempNode, firstExpressionNode);
}

NodeType *NodePrefix::ExpressionFirst() {
    NodeType *tempNode;
    NodeType *firstExpressionNode;
    cout << "Expression First" << endl;
    switch (m_crtToken.Type) {
        case Plus:
            cout << " Plus Operator " << endl;
            GetNextToken();
            tempNode = Term();
            firstExpressionNode = ExpressionFirst();
            return CreateNode(OperatorPlus, firstExpressionNode, tempNode);
        case Reference:
            cout << " Reference Operator " << endl;
            GetNextToken();
            tempNode = Term();
            firstExpressionNode = ExpressionFirst();
            return CreateNode(OperatorRef, firstExpressionNode, tempNode);
        case Minus:
            cout << "Minus Operator" << endl;
            GetNextToken();
            tempNode = Term();
            firstExpressionNode = ExpressionFirst();
            return CreateNode(OperatorMinus, firstExpressionNode, tempNode);
        case Variable:
            cout << "Variable Operator" << endl;
            GetNextToken();
            tempNode = Term();
            firstExpressionNode = ExpressionFirst();
            return CreateNode(VariableValue, firstExpressionNode, tempNode);
        case Equal:
            cout << "Equal Operator" << endl;
            GetNextToken();
            tempNode = Term();
            firstExpressionNode = ExpressionFirst();
            return CreateNode(OperadorEqual, firstExpressionNode, tempNode);
    }

    return CreateNodeNumber(0);
}

NodeType *NodePrefix::Term() {

    NodeType *factorNode = Factor();
    NodeType *termFirstNode = TermFirst();
    return CreateNode(OperatorMul, factorNode, termFirstNode);
}

NodeType *NodePrefix::TermFirst() {
    NodeType *factorNode;
    NodeType *termFirstNode;
    switch (m_crtToken.Type) {
        case Mul:
            GetNextToken();
            factorNode = Factor();
            termFirstNode = TermFirst();
            return CreateNode(OperatorMul, termFirstNode, factorNode);

        case Div:
            GetNextToken();
            factorNode = Factor();
            termFirstNode = TermFirst();
            return CreateNode(OperatorDiv, termFirstNode, factorNode);
    }
    return CreateNodeNumber(1);
}

void NodePrefix::GetNextToken() {
    SkipWhiteSpaces();
    m_crtToken.Value = 0;
    m_crtToken.Symbol = 0;
    cout << "Get next token" << endl;
    if (m_Text[m_Index] == 0) {
        cout << "First if, index = 0" << endl;
        m_crtToken.Type = EndOfText;
        return;
    }
    if (isdigit(m_Text[m_Index])) {
        cout << "found a number" << endl;
        m_crtToken.Type = Number;
        m_crtToken.Value = GetNumber();
        cout << "Number VALUE: " << m_crtToken.Value << endl;
        return;
    }
    if (islower(m_Text[m_Index])) {
        cout << "found a operator" << endl;
        m_crtToken.Type = Reference;
        m_crtToken.Value = GetReference();
        cout << "VALUE: " << m_crtToken.Value << endl;
        return;
    }
    if (isupper(m_Text[m_Index])) {
        cout << "found a variable" << endl;
        m_crtToken.Type = Variable;
        m_crtToken.Value = GetVariable();
        cout << "VALUE: " << m_crtToken.Value << endl;
        return;
    }
    m_crtToken.Type = Error;
    switch (m_Text[m_Index]) {
        case '+':
            m_crtToken.Type = Plus;
            cout << "Plus" << endl;
            break;
        case '-':
            m_crtToken.Type = Minus;
            cout << "Minus" << endl;
            break;
        case '=':
            m_crtToken.Type = Equal;
            cout << "Reference to a copy" << endl;
            break;
        case '*':
            m_crtToken.Type = Mul;
            cout << "Multiply star" << endl;
            break;
        case '/':
            m_crtToken.Type = Div;
            cout << "Divide" << endl;
            break;
        case '(':
            m_crtToken.Type = OpenParenthesis;
            cout << "Open Parenthesis" << endl;
            break;
        case ')':
            m_crtToken.Type = ClosedParenthesis;
            cout << "Closed Parenthesis" << endl;
            break;
    }
    if (m_crtToken.Type != Error) {
        m_crtToken.Symbol = m_Text[m_Index];
        m_Index++;
    } else {

        cout << "Unexpected token: " << m_Text[m_Index] << " at position " << m_Index << "\n" << "previous token: "
             << m_Text[m_Index - 1] << endl;
    }
}

int NodePrefix::GetVariable() {
    cout << "GET VAR" << endl;
    SkipWhiteSpaces();
    cout << "get letter" << endl;
    int index = m_Index;
    char buffer[32] = {0};
    int indice = 0;
    while (isupper(m_Text[m_Index])) {
        buffer[indice] = m_Text[m_Index];
        indice++;
        m_Index++;

    }
    if (m_Index - index == 0) {
        cout << "letter expected but not found: " << m_Index << endl;
    }
    cout << "Same problem :( : " << buffer << endl;
    return ASCIIParser(buffer).convert();
}

int NodePrefix::GetReference() {
    SkipWhiteSpaces();
    cout << "get letter" << endl;
    int index = m_Index;
    char buffer[6] = {0};
    int indice = 0;
    while (islower(m_Text[m_Index])) {
        buffer[indice] = m_Text[m_Index];
        indice++;
        m_Index++;
    }
    cout << "buffer value: " << buffer[0] << endl;

    switch (buffer[0]) {
        case 'f': {
            cout << "float" << endl;
            if (Check(0, buffer)) {
                return 0;
            } else {
                break;
            }
        }
        case 'd': {
            cout << "double" << endl;
            if (Check(1, buffer)) {
                return 1;
            } else {
                break;
            }
        }
        case 'i': {
            cout << "int" << endl;
            if (Check(2, buffer)) {
                return 2;
            } else {
                break;
            }
        }

        case 'l': {
            cout << "long" << endl;
            if (Check(3, buffer)) {
                return 3;
            } else {
                break;
            }
        }

        case 'c': {
            cout << "char" << endl;
            if (Check(4, buffer)) {
                return 4;
            } else {
                break;
            }
        }

    }

    if (m_Index - index == 0) {
        cout << "letter expected but not found" << m_Index << endl;
    }
}

double NodePrefix::GetNumber() {
    SkipWhiteSpaces();
    cout << "Get number" << endl;
    int index = m_Index;
    char buffer[32] = {0};
    int indice = 0;
    while (isdigit(m_Text[m_Index])) {
        buffer[indice] = m_Text[m_Index];
        cout << "buffer value: " << buffer[indice] << endl;
        indice++;
        m_Index++;
    }
    if (m_Text[m_Index] == '.') {
        cout << "point if" << endl;
        m_Index++;
    }
    if (m_Index - index == 0) {
        cout << "Number expected but not found" << m_Index << endl;
    }
    double result = ASCIIParser().charToint(buffer);
    cout << "buffer value: " << result << endl;
    return result;
}

NodeType *NodePrefix::Factor() {
    NodeType *node;
    switch (m_crtToken.Type) {
        case OpenParenthesis: {
            GetNextToken();
            node = Expression();
            Match(')');
            return node;
        }
        case Minus: {
            GetNextToken();
            node = Factor();
            return CreateUnaryNode(node);
        }
        case Number: {
            double value = m_crtToken.Value;
            GetNextToken();
            return CreateNodeNumber(value);
        }

        default: {

            cout << "Unexpected Token: " << m_crtToken.Symbol << "at position: " << m_Index << endl;

        }
    }
}

void NodePrefix::Match(char expected) {
    if (m_Text[m_Index - 1] == expected) {
        GetNextToken();
    } else {
        cout << "Expected token: " << expected << " at position: " << m_Index << endl;
    }
}

bool NodePrefix::Check(int type, char *text) {
    cout << "CHECK: " << endl;
    switch (type) {
        case 0: {
            char str1[] = "float";
            for (int i = 0; text[i]; i++) {
                if (text[i] != str1[i]) {
                    cout << "SYNTAX ERROR" << endl;
                    return false;
                }
            }
            cout << "word verified" << endl;
            return true;
        }
        case 1: {
            char str1[] = "double";
            for (int i = 0; text[i]; i++) {
                if (text[i] != str1[i]) {
                    cout << "SYNTAX ERROR" << endl;
                    return false;
                }
            }
            cout << "word verified" << endl;
            return true;
        }
        case 2: {
            char str1[4] = "int";
            for (int i = 0; text[i]; i++) {
                if (text[i] != str1[i]) {
                    cout << "SYNTAX ERROR" << endl;
                    return false;
                }
            }
            cout << "word verified" << endl;
            return true;
        }
        case 3: {
            char str1[] = "long";
            for (int i = 0; text[i]; i++) {
                if (text[i] != str1[i]) {
                    cout << "SYNTAX ERROR" << endl;
                    return false;
                }
            }
            cout << "word verified" << endl;
            return true;
        }
        case 4: {
            char str1[] = "char";
            for (int i = 0; text[i]; i++) {
                if (text[i] != str1[i]) {
                    cout << "SYNTAX ERROR" << endl;
                    return false;
                }
            }
            cout << "word verified" << endl;
            return true;
        }
    }
}

NodeType *NodePrefix::CreateNodeNumber(double value) {
    auto *node = new NodeType;
    node->Value = value;
    node->Type = NumberValue;
    return node;
}

NodeType *NodePrefix::CreateUnaryNode(NodeType *left) {
    auto *node = new NodeType;
    node->Left = left;
    node->Right = nullptr;
    node->Type = UnaryMinus;
    return node;
}

NodeType *NodePrefix::CreateNode(NType type, NodeType *left, NodeType *right) {
    auto *node = new NodeType;
    node->Type = type;
    node->Left = left;
    node->Right = right;
    return node;
}
