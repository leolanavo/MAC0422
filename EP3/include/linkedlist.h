#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "node.h"

using namespace std;

template <class T> class LinkedList {
    int size;
public:
    Node<T> *head, *tail;
    LinkedList();
    void add(T info);
    T remove(int i);
    bool contain(T info);
    bool isEmpty();
    int get_size();
    void print_list();
    ~LinkedList();
};

using namespace std;

template <class T>
LinkedList<T>::LinkedList() :
    size(0), head(NULL), tail(NULL)
{
}

template <class T>
void LinkedList<T>::add(T info) {
    Node<T> *aux = new Node<T>(info);
    size++;

    if (head == NULL) {
        head = aux;
        tail = head;
        return;
    }

    tail->next = aux;
    aux->prev = tail;
    tail = aux;
    return;
}

template <class T>
T LinkedList<T>::remove(int index) {
    if (head == NULL)
        return 0;

    T result;
    Node<T> *aux = head;

    for (int i = 0; i < index; i++)
        aux = aux->next;

    if (aux == head)
        head = head->next;
    else if (aux == tail)
        tail = tail->prev;

    if (aux->prev != NULL)
        aux->prev->next = aux->next;
    if (aux->next != NULL)
        aux->next->prev = aux->prev;

    result = aux->get_data();
    delete aux;
    size--;
    return result;
}

template <class T>
bool LinkedList<T>::isEmpty() {
    return size == 0;
}

template <class T>
int LinkedList<T>::get_size() {
    return size;
}

template <class T>
void LinkedList<T>::print_list() {
    Node<T> *aux = head;

    for (int i = 0; i < size; i++, aux = aux->next)
        cout << aux->get_data() << " --> ";

    cout << endl;
}

template<class T>
LinkedList<T>::~LinkedList() {
    while (!isEmpty()) remove(0);
    head = NULL;
    tail = NULL;
}

#endif
