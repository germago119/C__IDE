//
// Created by Roger Valderrama on 4/6/18.
//

#ifndef C_IDE_NODETYPE_HPP
#define C_IDE_NODETYPE_HPP

enum NType {
    Undefined,
    UnaryMinus,
    NumberValue,
    OperatorRef,
    OperatorMul,
    OperatorDiv,
    OperatorPlus,
    OperadorEqual,
    OperatorMinus,
    VariableValue
};

class NodeType {

public:
    NType Type;
    double Value;
    NodeType *Left;
    NodeType *Right;

    NodeType();

    ~NodeType() {
        delete Right;
        delete Left;
    }
};


#endif //C_IDE_NODETYPE_HPP
