#include <iostream>
#include "Sgtree.h"
using namespace std;

void test_insert_bst_scpt(){
    //Test program for BST
    SgTree<int> bst;
    int input;
    while (input != 100){
        cout << "INSERTING" << endl;
        cout << "Enter a number to insert: ";
        cin >> input;
        cout << endl;
        bst.insert(input);
        bst.pretty();
        cout <<endl;
    }

    cout << "DONE!" << endl;
}

void test_insert_bst_fig_1(){
    //Test program for BST
    SgTree<int> bst;
    int input;
    int *arr = new int[17]{2,1, 6, 5, 15, 4,3, 12,16, 17, 18,13,14, 9, 7, 11, 10};
    for (int i = 0; i < 17; i++){
        cout << "INSERTING" << endl;
        cout << "Enter a number to insert: ";
        //cin >> input;
        input = arr[i];
        cout << input<< endl;
        bst.insert(input);
        bst.pretty();
        cout <<endl;
    }

    while (input != 100){
        cout << "INSERTING" << endl;
        cout << "Enter a number to insert: ";
        cin >> input;
        cout << endl;
        bst.insert(input);
        bst.pretty();
        cout <<endl;
    }

    cout << "DONE!" << endl;
}

int main(){
    //Test program for BST
    SgTree<int> bst;

    test_insert_bst_scpt(); 
    //test_insert_bst_fig_1();

    return 0;
}
