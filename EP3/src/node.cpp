#include "node.h"

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
