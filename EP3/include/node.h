#ifndef NODE_H
#define NODE_H

#include <iostream>

template <class T> class Node {
    T data;
public:
    Node<T> *next, *prev;

    Node(T data);
    void set_data(T data);
    T get_data();
};

#endif
