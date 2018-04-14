//
// Created by karina on 12/04/18.
//

#ifndef C_IDE_SIMPLELINKEDLIST_H
#define C_IDE_SIMPLELINKEDLIST_H

#include <iostream>
#include "Node.h"

// Template Declaration
template <typename T>
class SimpleLinkedList{
private:
    int size;
    Node<T>* head;
    Node<T>* tail;

public:
    SimpleLinkedList();

    ~SimpleLinkedList();

    void insertFront(T data);

    void insertRear(T value);

    void insertByIndex(T data, int index);

    void deleteFront();

    void deleteRear();

    void deleteByIndex(int index);

    void edit(T data, int index);

    Node<T>* get(int index);

    void print();

    int getSize();

    Node<T>* getHead();

    Node<T>* getTail();

};


// template definition
template<typename T>
SimpleLinkedList<T>::SimpleLinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    size = 0;
}

template<typename T>
SimpleLinkedList<T>::~SimpleLinkedList() {
    delete head;
    delete tail;
}

template<typename T>
void SimpleLinkedList<T>::insertFront(T data) {
    auto *new_node = new Node<T>(data);
    Node<T> *temp = head;

    if(head != nullptr){
        new_node->setNext(head);
        head = new_node;
        size++;
    } else{
        head = new_node;
        tail = new_node;
        size++;
    }
}

template<typename T>
void SimpleLinkedList<T>::insertRear(T value){
    auto *new_node = new Node<T>(value);
    Node<T> *temp = tail;

    if (tail != nullptr) {
        tail->setNext(new_node);
        tail = new_node;
        size++;
    } else {
        head = new_node;
        tail = new_node;
        size++;
    }
}

template<typename T>
void SimpleLinkedList<T>::insertByIndex(T data, int index) {
    if(index > size +1) {
        std::cout << "index out of range" << std::endl;
        return;
    }
    auto *new_node = new Node<T>(data);
    Node<T> *temp = head;
    if(index == 0)
    {
        new_node->setNext(head);
        head = new_node;
    }
    else{
        if (head != nullptr) {
            for(int i = 0; i < (index-1); ++i){
                temp = temp->getNext();
            }
            new_node->setNext(temp->getNext());
            temp->setNext(new_node);
            size++;
        }
        else {
            head = new_node;
            tail = new_node;
            size++;
        }
    }
}

template<typename T>
void SimpleLinkedList<T>::deleteFront() {
    if (head != nullptr) {
        head = head->getNext();
        size--;
    } else {
        return;
    }
}

template<typename T>
int SimpleLinkedList<T>::getSize() {
    return size;
}

template<typename T>
void SimpleLinkedList<T>::deleteRear() {
    Node<T> *temp = head;

    if (head != nullptr) {
        for(int i = 0; i < size - 2; ++i) {
            temp = temp->getNext();
        }
        tail = temp;
        tail->setNext(nullptr);
        size--;
    } else {
        return;
    }
}

template<typename T>
void SimpleLinkedList<T>::deleteByIndex(int index) {
    if(index > size) {
        std::cout << "index out of range" << std::endl;
        return;
    }
    Node<T> *temp = head;
    if(index == 0) {
        head = head->getNext();
        size--;
    }
    else{
        if (head != nullptr) {
            for(int i = 0; i < (index-1); ++i){
                temp = temp->getNext();
            }
            temp->setNext(temp->getNext()->getNext());
            size--;
        } else {
            return;
        }
    }
}

template<typename T>
void SimpleLinkedList<T>::edit(T data, int index) {
    if(index > size)
        return;
    Node<T> *temp = head;
    if (head != nullptr) {
        for(int i = 0; i == index; ++i){
            temp = temp->getNext();
        }
        temp->setData(data);
    } else {
        return;
    }
}

template<typename T>
Node<T>* SimpleLinkedList<T>::get(int index) {
    if(index > size)
        return nullptr;
    Node<T> *temp = head;
    if (head != nullptr) {
        for(int i = 0; i == index; ++i){
            temp = temp->getNext();
        }
        return temp;
    } else {
        return nullptr;
    }
}

template<typename T>
Node<T>* SimpleLinkedList<T>::getHead() {
    return head;
}

template<typename T>
Node<T>* SimpleLinkedList<T>::getTail() {
    return tail;
}

#endif //C_IDE_SIMPLELINKEDLIST_H
