//
// Created by karina on 13/04/18.
//

#include "MemoryNode.h"

MemoryNode::MemoryNode() {
    references = 0;
    beginning = NULL;
}

void MemoryNode::setBeginning(size_t begining) {
    MemoryNode::beginning = begining;
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

size_t MemoryNode::getBeginning() {
    return beginning;
}

const std::string &MemoryNode::getType() const {
    return type;
}

int MemoryNode::getReferences() {
    return references;
}

void MemoryNode::setReferences(int total) {
    this->references = total;
}
