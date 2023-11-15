#include <iostream>
#include "Bst.h"
#include "Sgtree.h"
using namespace std;

template <typename T>
void insertTobst(SgTree<T> tree, T value){
    cout << "Inserting " << value << endl;
    tree.insert(value);
}


int main(){
    //Test program for BST
    SgTree<int> bst;

    insertTobst(bst, 25);
    insertTobst(bst, 20);
    insertTobst(bst, 10);
    insertTobst(bst, 22);
    cout << "DISPLAYING" << endl;
    bst.pretty();

    /*
    cout << "Removing 20" << endl;
    bst.remove(20);
    bst.pretty();

    cout << "Removing 25" << endl;
    bst.remove(25);
    bst.pretty();*/

    cout << "DONE!" << endl;
    return 0;
}
