#include <iostream>
#include "Scgtree.h"
using namespace std;

void test_insert_bst_scpt(){
    //Test program for BST
    ScgTree<int> bst;
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

    while (input != 101){
        cout << "DELETING" << endl;
        cout << "Enter a number to DELETE: ";
        cin >> input;
        cout << endl;
        bst.remove(input);

        bst.pretty();
        cout <<endl;
    }

    cout << "DONE!" << endl;
}

void test_insert_bst_fig_1(){
    //Test program for BST
    ScgTree<int> bst;
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

    while (input != 101){
        cout << "DELETING" << endl;
        cout << "Enter a number to DELETE: ";
        cin >> input;
        cout << endl;
        bst.remove(input);

        bst.pretty();
        cout <<endl;
    }

    while (input != 102){
        cout << "FIND" << endl;
        cout << "Enter a number to find: ";
        cin >> input;
        cout << endl;
        ScgNode<int>* temp = bst.find(input);
        bst.pretty();
        if (temp == nullptr){
            cout << " nodo no encontrado: "<< input <<endl;
        }
    }



    cout << "DONE!" << endl;
}


// test delete 
void test_insert_delete(){
//Test program for BST
    ScgTree<int> bst;
    int input;
    int *arr = new int[10]{64, 24, 543, 523, 122112, 41221, 123212, 32423, 100, 12};
    for (int i = 0; i < 10; i++){
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

    while (input != 101){
        cout << "DELETING" << endl;
        cout << "Enter a number to DELETE: ";
        cin >> input;
        cout << endl;
        bst.remove(input);

        bst.pretty();
        cout <<endl;
    }

    while (input != 102){
        cout << "FIND" << endl;
        cout << "Enter a number to find: ";
        cin >> input;
        cout << endl;
        ScgNode<int>* temp = bst.find(input);
        bst.pretty();
        if (temp == nullptr){
            cout << " nodo no encontrado: "<< input <<endl;
        }
    }
}

int main(){
    //Test program for BST
    ScgTree<int> bst;

    // test_insert_bst_scpt(); 
    
    
    // test_insert_bst_fig_1();

    test_insert_delete();

        return 0;
}
