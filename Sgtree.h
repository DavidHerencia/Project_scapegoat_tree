#pragma once

#include <iostream>
using namespace std;

//Standard BST node, it is also used in the Scapegoat Tree
template <typename T>
struct SgNode{
    T data;
    SgNode<T> *left, *right;
    int size;

    SgNode(T value){
        data = value;
        left = right = nullptr;
        size = 1;
    }
};

//Scapegoat Tree class implementation
template <typename T>
class SgTree{
    SgNode<T>* root = nullptr;

    public:
        BST(){}
        ~BST(){
            clear(root);
        }

        void insert(T value){

            cout << "Inserting " << value << endl;
            if (!root){
                root = new SgNode<T>(value);
                cout << "Inserted " << value << endl;
                return;
            }

            //Find next available spot
            SgNode<T>* temp = root, *prev = nullptr;
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
                prev->left = new SgNode<T>(value);
            } else {
                prev->right = new SgNode<T>(value);
            }
        }

        SgNode<T>* find(T value){
            if(!root)
                throw "Tree is empty";

            SgNode<T>* current = root;
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
            //Find SgNode
            SgNode<T>* current = root, *prev = nullptr;
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

            //Check if SgNode was found
            if (!current){
                cout << "SgNode not found" << endl;
                return;
            }

            //Case 1: SgNode is a leaf
            if(!current->left && !current->right){
                if(prev->left == current){
                    prev->left = nullptr;
                } else {
                    prev->right = nullptr;
                }

                delete current;
            }
            //Case 2: SgNode has only a subtree
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
            //Case 3: SgNode has both subtrees
            else {
                //Get succesor
                SgNode<T>* succesor = current->right, *prevSuccesor = current;
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
        //Exclusive to Scapegoat Tree

        //Returns the numbers of keys stored in this sub-tree rooted at node
        int size(SgNode<T>* node){
            if(!node)
                return 0;
            
            return size(node->left) + size(node->right) + 1;
        }

        //Returns the brother of node
        SgNode<T>* brother(SgNode<T>* node){
            //Find parent
            SgNode<T>* parent = root, *prev = nullptr;
            while (parent){
                if (node->data == parent->data){
                    break;
                } else if (node->data < parent->data){
                    prev = parent;
                    parent = parent->left;
                } else {
                    prev = parent;
                    parent = parent->right;
                }
            }

            //Check if parent was found
            if (!parent){
                cout << "Parent not found" << endl;
                return;
            }

            //Return brother
            if(parent->left == node)
                return parent->right;
            else
                return parent->left;
        }

        //Returns the height of the tree rooted at node
        int height(SgNode<T>* node){
            if(!node)
                return -1;
            
            int leftHeight = height(node->left);
            int rightHeight = height(node->right);

            return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
        }
        //Returns the depth of node
        int depth(SgNode<T>* node){
            if(!node)
                return -1;
            
            int depth = 0;
            SgNode<T>* current = root;
            while (current){
                if (node->data == current->data){
                    break;
                } else if (node->data < current->data){
                    current = current->left;
                } else {
                    current = current->right;
                }
                depth++;
            }
            return depth;            
        }


        void clear(SgNode<T>* node){
            if(!node)
                return;
            clear(node->left);
            clear(node->right);
            node->left = node->right = nullptr;
            delete node;
        }

        void pretty(SgNode<T>* node, int level){
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