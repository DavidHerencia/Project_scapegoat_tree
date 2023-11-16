#pragma once

#include <iostream>
using namespace std;


//Standard BST node
template <typename T>
struct Node{
    T data;
    Node<T>*left,*right;
    int size;

    Node(T value){
        data = value;
        left = right = nullptr;
        size = 1;
    }
};

//BST class implementation
template <typename T>
class BST{
    Node<T>* root = nullptr;
    public:
        BST(){}
        ~BST(){
            clear(root);
        }

        void insert(T value){

            cout << "Inserting " << value << endl;
            if (!root){
                root = new Node<T>(value);
                cout << "Inserted " << value << endl;
                return;
            }

            //Find next available spot
            Node<T>* temp = root, *prev = nullptr;
            while (temp){
                prev = temp;
                if (value < temp->data){
                    temp = temp->left;
                } else {
                    temp = temp->right;
                }
            }

            //Insert in next available spot
            if (value < prev->data){
                prev->left = new Node<T>(value);
            } else {
                prev->right = new Node<T>(value);
            }
        }

        Node<T>* find(T value){
            if(!root)
                throw "Tree is empty";

            Node<T>* current = root;
            while (current){
                if (value == current->data){
                    return current;
                } else if (value < current->data){
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return nullptr;
        }

        void remove(T value){
            //Find node
            Node<T>* current = root, *prev = nullptr;
            while (current){
                if (value == current->data){
                    break;
                } else if (value < current->data){
                    prev = current;
                    current = current->left;
                } else {
                    prev = current;
                    current = current->right;
                }
            }

            //Check if node was found
            if (!current){
                cout << "Node not found" << endl;
                return;
            }

            //Case 1: Node is a leaf
            if(!current->left && !current->right){
                if(prev->left == current){
                    prev->left = nullptr;
                } else {
                    prev->right = nullptr;
                }

                delete current;
            }
            //Case 2: Node has only a subtree
            else if ((!current->left && current->right) || (current->left && !current->right)){
                if (prev->left == current) {
                    if (current->left)
                        prev->left = current->left;
                    else
                        prev->left = current->right;
                } else {
                    if (current->left)
                        prev->right = current->left;
                    else
                    prev->right = current->right;
                }
                delete current;
            }
            //Case 3: Node has both subtrees
            else {
                //Get succesor
                Node<T>* succesor = current->right, *prevSuccesor = current;
                while (succesor->left){
                    prevSuccesor = succesor;
                    succesor = succesor->left;
                }
                T sucesorValue = succesor->data;

                //Remove succesor
                remove(sucesorValue);

                //Replace current with succesor
                current->data = sucesorValue;
            }
        }

        void pretty(){
            pretty(root, 0);
        }

    private:
        void clear(Node<T>* node){
            if(!node)
                return;
            clear(node->left);
            clear(node->right);
            node->left = node->right = nullptr;
            delete node;
        }

        void pretty(Node<T>* node, int level){
            if(!node)
                return;
            pretty(node->right, level+1);
            for(int i = 0; i < level; i++){
                cout << "   ";
            }
            cout << node->data << endl;
            pretty(node->left, level+1);
        }
};