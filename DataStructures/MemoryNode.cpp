//
// Created by karina on 13/04/18.
//

#include "MemoryNode.h"

void MemoryNode::setBegining(char *begining) {
    MemoryNode::begining = begining;
}

void MemoryNode::setType(const std::string &type) {
    MemoryNode::type = type;
}

const std::string &MemoryNode::getIdentifier() const {
    return identifier;
}

void MemoryNode::setIdentifier(const std::string &identifier) {
    MemoryNode::identifier = identifier;
}

char *MemoryNode::getBegining() const {
    return begining;
}

const std::string &MemoryNode::getType() const {
    return type;
}
