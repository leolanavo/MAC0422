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

using namespace std;

template <class T>
Node<T>::Node(T data) :
    data(data), next(NULL), prev(NULL)
{
}

template <class T>
void Node<T>::set_data(T data) {
    this->data = data;
}

template <class T>
T Node<T>::get_data() {
    return data;
}

#endif
