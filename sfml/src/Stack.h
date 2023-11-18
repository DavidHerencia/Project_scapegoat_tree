#include "CircularArray.h"

template <typename T>
class Stack : public CircularArray<T> { 
    private:
        //solo almacenamos el size, ya que el array y el capacity se hereda de la clase padre
        int size{};

    public:

    Stack();


    void push(T value);
    T pop();
    void display();

};

template <class T>
Stack<T>::Stack(){}

template <class T>
void Stack<T>::push(T value){
    // Utilizamos el metodo push_back de la clase CircularArray
    this->push_back(value);
    size++;
}

template <class T>
T Stack<T>::pop(){
    // Utilizamos el metodo pop_back de la clase CircularArray, respetando el principio LIFO
    size--;
    return this->pop_back();
}

/*
template<class T>
void Stack<T>::display(){
    // Imprimimos el stack respetando el principio LIFO
    if (this->size <= 0) {
        return;
    }
    int it1 = this->back;
    while (it1 != this->front) {
        std::cout<<this->array[it1]<<" ";
        it1 = this->prev(it1);
    }
    std::cout<<this->array[it1]<<std::endl;
}
*/