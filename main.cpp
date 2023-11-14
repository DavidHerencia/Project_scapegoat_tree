#include <iostream>
#include "Bst.h"
#include "Sgtree.h"
using namespace std;

int main(){
    //Test program for BST
    SgTree<int> bst;

    cout << "Inserting 10, 5, 20, 15, 30, 25, 40, 35, 50, 45, 60, 55, 70, 65, 80, 75, 90, 85, 100" << endl;
    bst.insert(25);
    bst.insert(20);
    bst.insert(10);
    bst.insert(22);
    bst.insert(5);
    bst.insert(12);
    cout << "Inserted left" << endl;
    bst.insert(36);
    bst.insert(30);
    bst.insert(40);
    bst.insert(28);
    bst.insert(38);
    bst.insert(48);
    cout << "Inserted right" << endl;
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
