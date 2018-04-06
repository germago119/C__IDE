//
// Created by Roger Valderrama on 4/6/18.
//

#ifndef C_IDE_NODETYPE_HPP
#define C_IDE_NODETYPE_HPP

enum NType {
    Undefined,
    UnaryMinus,
    NumberValue,
    OperadorEq,
    OperatorRef,
    OperatorMul,
    OperatorDiv,
    OperatorPlus,
    OperatorMinus,
    VariableValue,
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
