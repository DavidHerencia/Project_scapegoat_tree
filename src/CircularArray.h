#pragma once
//#include <iostream>
//#include <sstream>
#define DEFAULT_CAPACITY 10
#define INCREMENT 5
using namespace std;

template <class T>
class CircularArray {
   protected:
    T* array;
    int capacity;
    int back, front;

   public:
    CircularArray(int _capacity = DEFAULT_CAPACITY);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T &data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T& operator[](int);
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep = " ");

   private:
    void resize();

    protected:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray(int _capacity) {
    this->capacity = _capacity;
    this->array = new T[_capacity];
    // Definimos el -1 como indicador de array vacio
    this->front = -1;
    this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray() {
    delete[] array;
}

template <class T>
void CircularArray<T>::push_front(T data) {
    if (this->is_full()) {
        resize();
    }
    if (this->is_empty()) {
        front = 0;
        back = 0;
    } else {
        front = prev(front);
    }
    array[front] = data;
}

template <class T>
void CircularArray<T>::push_back(T &data) {
    if (this->is_full()) {
        resize();
    }
    if (this->is_empty()) {
        front = 0;
        back = 0;
    } else {
        back = next(back);
    }
    array[back] = data;
}

template <class T>
void CircularArray<T>::insert(T data, int pos) {
    if (pos < 0 || pos > this->size()) {
        throw "Error: Index out of bounds";
    } else if (pos == 0) {
        this->push_front(data);
    } else if (pos == this->size()) {
        this->push_back(data);
    } else {
        if (this->is_full()) {
            resize();
        }
        // Si la posicion es menor a la mitad del array, se mueven los elementos
        // hacia la izquierda
        if (pos <= this->size() / 2) {
            front = prev(front);
            for (int i = 0; i < pos; i++) {
                array[next(i)] = array[i];
            }
        }
        // Si la posicion es mayor a la mitad del array, se mueven los elementos
        // hacia la derecha
        else {
            back = next(back);
            for (int i = this->size() - 1; i >= pos; i--) {
                array[prev(i)] = array[i];
            }
        }
        array[pos] = data;
    }
}

template <class T>
T CircularArray<T>::pop_front() {
    // Verificamos si el array esta vacio
    if (this->is_empty()) {
        throw "Error: Empty array";
    }
    // Verificamos que el front no apunte al ultimo espacio del array
    else if (front < capacity - 1) {
        T temp = this->array[front];
        if (front == back) {
            front = -1;
            back = -1;
        } else {
            front++;
        }
        return temp;
    }
    // Si esta en el ultimo espacio y se suma 1, se reinicia en 0
    else {
        T temp = array[capacity - 1];
        if (front == back) {
            front = -1;
            back = -1;
        } else {
            front = 0;
        }
        return temp;
    }
}

template <class T>
T CircularArray<T>::pop_back() {
    // Verificamos si el array esta vacio
    if (this->is_empty()) {
        throw "Error: Empty array";
    }
    // Verificamos que el back no apunte al primer espacio del array [0]
    else if (back > 0) {
        T temp = this->array[back];
        if (front == back) {
            front = -1;
            back = -1;
        } else {
            back--;
        }
        return temp;
    }
    // Si apunta al espacio 0, entonces vuelve al final [capacity-1]
    else {
        T temp = this->array[0];
        if (front == back) {
            front = -1;
            back = -1;
        } else {
            back = capacity - 1;
        }
        return temp;
    }
}

template <class T>
bool CircularArray<T>::is_full() {
    return (front == 0 && back == capacity - 1) || (front == back + 1);
}

template <class T>
bool CircularArray<T>::is_empty() {
    return (front == -1 && back == -1);
}

template <class T>
int CircularArray<T>::size() {
    if (this->is_empty()) {
        return 0;
    } else if (front == back) {
        return 1;
    } else if (front <= back) {
        return (back - front + 1);
    } else {
        return (capacity - front + back + 1);
    }
}

template <class T>
void CircularArray<T>::clear() {
    // reiniciamos los punteros como si fuera un array vacio
    this->front = -1;
    this->back = -1;
}

template <class T>
T& CircularArray<T>::operator[](int pos) {
    // caso para indice invalido
    if (pos < 0 || pos >= this->size()) {
        throw "Error: Index out of bounds";
    } else {
        return array[(front + pos) % capacity];
    }
}

template <class T>
void CircularArray<T>::resize() {
    T* temp = new T[capacity + INCREMENT];
    // copiamos los elementos del array original al nuevo, con el front en la
    // posicion 0
    int i = 0;
    for (int j = front; i < capacity; j = next(j)) {
        temp[i++] = array[j];
    }
    front = 0;
    back = capacity - 1;  // capacity - 1
    capacity += INCREMENT;
    delete[] array;
    array = temp;
}

template <class T>
int CircularArray<T>::next(int pos) {
    return (pos + 1) % capacity;
}

template <class T>
int CircularArray<T>::prev(int pos) {
    return (pos - 1 + capacity) % capacity;
}

template <class T>
void merge(T* arr, int left, int mid, int right) {
    int lSize = mid - left + 1;
    int rSize = right - mid;

    T* leftArr = new T[lSize];
    T* rightArr = new T[rSize];

    for (int i = 0; i < lSize; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < rSize; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < lSize && j < rSize) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < lSize) {
        arr[k++] = leftArr[i++];
    }
    while (j < rSize) {
        arr[k++] = rightArr[j++];
    }
}

template <class T>
void merge_sort(T* arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

template <class T>
void CircularArray<T>::sort() {
    // Validamos que el array no este vacio o que no sea de tamaño 1
    int sz = this->size();
    if (sz <= 1)
        return;

    T* temp = new T[sz];
    for (int i = 0; i < sz; i++) {  // O(n)
        temp[i] = this->pop_back();
    }
    merge_sort(temp, 0, sz - 1);    // O(nlogn)
    for (int i = 0; i < sz; i++) {  // O(n)
        this->push_back(temp[i]);
    }
}

template <class T>
bool CircularArray<T>::is_sorted() {
    if (this->size() < 2) {
        return true;
    }
    for (int i = front; i != back; i = next(i)) {
        if (array[i] > array[next(i)]) {
            return false;
        }
    }
    return true;
}

template <class T>
void CircularArray<T>::reverse() {
    if (this->size() < 2) {
        return;
    }
    int it1 = front;
    int it2 = back;
    while (it1 != it2) {
        swap(array[it1], array[it2]);
        it1 = next(it1);
        it2 = prev(it2);
    }
}

/*
template <class T>
string CircularArray<T>::to_string(string sep) {
    string result = "";
    stringstream ss;

    if (this->is_empty()) {
        return result;
    }
    for (int i = front; i != back; i = next(i)) {
        ss << array[i] << sep;
    }
    ss << array[back] << sep;
    result = ss.str();
    return result;
}*/