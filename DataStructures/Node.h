//
// Created by karina on 12/04/18.
//

#ifndef C_IDE_NODE_H
#define C_IDE_NODE_H
// Template Declaration
template <typename T>
class Node{
private:
    T data;
    Node* next;

public:
    Node();

    Node(T data);

    ~Node();

    T getData();

    Node<T>* getNext();

    void setData(T data);

    void setNext(Node<T> * next);

    void print();
};


// template definition
template<typename T>
Node<T>::Node() {
    this->next = nullptr;
}

template <typename T>
Node<T>::Node(T data) {
    this->data = data;
    next = nullptr;
}

template <typename T>
Node<T>::~Node() {
    delete next;
}

template <typename T>
T Node<T>::getData() {
    return data;
}

template <typename T>
Node<T>* Node<T>::getNext() {
    return next;
}

template <typename T>
void Node<T>::setData(T data) {
    this->data = data;
}

template <typename T>
void Node<T>::setNext(Node<T> *next) {
    this->next = next;
}
#endif //C_IDE_NODE_H
