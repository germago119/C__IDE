//
// Created by karina on 13/04/18.
//

#ifndef C_IDE_MEMORYNODE_H
#define C_IDE_MEMORYNODE_H


#include <string>

class MemoryNode {
public:
    MemoryNode();

    void setBegining(char *begining);

    void setType(const std::string &type);

    const std::string &getIdentifier() const;

    void setIdentifier(const std::string &identifier);

    char *getBegining() const;

    const std::string &getType() const;

    int getReferences();

    void setReferences(int total);

private:
    char* begining;
    std::string type;
    std::string identifier;
    int references;
};


#endif //C_IDE_MEMORYNODE_H
