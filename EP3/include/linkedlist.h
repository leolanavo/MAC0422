#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "node.h"

using namespace std;

template <class T> class LinkedList {
    int size;
    Node<T> *head, *tail;
public:
    LinkedList();
    void add(T info);
    T remove(int i);
    int get_size();
};

#endif
