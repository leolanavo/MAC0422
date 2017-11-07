#include "linkedlist.h"

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
        return NULL;

    T result;
    Node<T> *aux = head;

    for (int i = 0; i < index; i++)
        aux = aux->next;

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
int LinkedList<T>::get_size() {
    return size;
}
