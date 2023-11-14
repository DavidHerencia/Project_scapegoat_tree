#pragma once

#include <iostream>
#include <cmath>
using namespace std;

#define ALPHA 0.6

//Standard BST node, it is also used in the Scapegoat Tree
template <typename T>
struct SgNode{
    T data;
    SgNode<T> *left, *right;

    SgNode(T value){
        data = value;
        left = right = nullptr;
    }
};

//Scapegoat Tree class implementation
template <typename T>
class SgTree{
    SgNode<T>* root = nullptr;
    int size, maxSize;

    public:
        BST(){
            size = 0;
            maxSize = 0;
        }
        ~BST(){
            clear(root);
        }

        void insert(T value){   
            insert(this->root, value);
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
        //Default insert, return the height of the node. Using alpha-height function
        void insert(SgNode<T>* &node, T value){
            //Base case
            if(node == nullptr){
                node = new SgNode<T>(value);   
            }

            //Go trough the tree
            else if (node->value < value)
                insert(node->right, value);
            else 
                insert(node->left, value);

            //Return of the recursion
            //Check if the node is alpha-weight balanced
            if(height(node) < height_a(node)){
                //If it is, then it is not the scapegoat. Because the tree is alpha-weight balanced
                return;
            }

            //If it is not, then it is the scapegoat. So we rebuild the tree
            int n = size(node);
            SgNode<T>* list = flatten(node, nullptr);
            node = build(list, size(list));
        }
        
        //Flatten the tree rooted at node (IN PLACE)
        SgNode<T>* flatten(SgNode<T>*& node, SgNode<T>* list){
            if (node == nullptr)
                return list;
            node->right = flatten(node->right, list);
            return flatten(node->left, node);
        }

        //Build a balanced tree from a list of nodes
        SgNode<T>* build(SgNode<T>* head, int n){
            if(n == 0){
                head->left = nullptr;
                return head;
            }
            SgNode<T>* r = build(head, ceil((n-1)/2));
            SgNode<T>* s = build(r->right,ceil((n-1)/2));

            r->right = s->left;
            s->left = r;
            return s;
        }


        int size(SgNode<T>* node){
            if(!node)
                return 0;
            
            return size(node->left) + size(node->right) + 1;
        }

        int height_a(Node<T>* node){
            return floor(log(size(node)) / log(1/ALPHA));
        }

        int height(SgNode<T>* node){
            if(!node)
                return -1;
            
            int leftHeight = height(node->left);
            int rightHeight = height(node->right);

            return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
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


        /*

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
        } */