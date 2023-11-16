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
    int treeSize, maxTreeSize;

    public:
        SgTree(){
            treeSize = 0;
            maxTreeSize = 0;
        }
        ~SgTree(){
            clear(root);
        }

        void insert(T value){
            insert(this->root,value);
            treeSize++;
            if(treeSize > maxTreeSize)
                maxTreeSize = treeSize;
        }

        SgNode<T>* find(T value){
            //Todo
        }

        void remove(T value){
            //Todo
        }

        void pretty(){
            pretty(root, 0);
        }

    private:
        void insert(SgNode<T>*& node, T value){
            if(node == nullptr){
                node = new SgNode<T>(value);
                return;
            }

            if(value < node->data)
                insert(node->left, value);
            else
                insert(node->right, value);
            
            cout << "PASSED TROUGH" << &node << " WITH VALUE:" << node->data << endl;

            //check if node is unbalanced
            int subtreeSizeLeft = size(node->left);
            int subtreeSizeRight = size(node->right);
            int subtreeSize = subtreeSizeLeft + subtreeSizeRight + 1;
            if(subtreeSizeLeft <= subtreeSize * ALPHA && subtreeSizeRight <= subtreeSize * ALPHA)
                return;

            // Rebuild tree at node
            T* values = new T[subtreeSize];
            inOrdenAuxiliar(node,values,0);
            return;
        }

        T* inOrdenAuxiliar(SgNode<T>* node, T* values, int index){
            if(node == nullptr)
                return values;
            
            values = inOrdenAuxiliar(node->left, values, index);
            values[index++] = node->data;
            cout << node->data << " ";
            values = inOrdenAuxiliar(node->right, values, index);
            return values;
        }

        SgNode<T>* buildTree(int n, T* values){
            SgNode<T>* list = nullptr;
            SgNode<T>* node = root;

            //Flatten the tree rooted at scapegoat
            list = flatten(node, list);
            build(n, list);
            return list->left;
        }

        SgNode<T>* buildTree(int n, SgNode<T>* scapegoat){
            SgNode<T>* list = nullptr;
            SgNode<T>* node = scapegoat;

            //Flatten the tree rooted at scapegoat
            list = flatten(node, list);
            build(n, list);
            return list->left;
        }
        
        //Flatten the tree rooted at node (IN PLACE)
        SgNode<T>* flatten(SgNode<T>* node, SgNode<T>* list){
            if (node == nullptr)
                return list;
            node->right = flatten(node->right, list);
            return flatten(node->left, node);
        }

        //Build a balanced tree from a list of nodes
        SgNode<T>* build(int n, SgNode<T>* head){
            if(n == 0){
                if(head != nullptr)
                    head->left = nullptr;
                return head;
            }
            SgNode<T>* r = build(ceil((n-1)/2), head);
            SgNode<T>* s = build(floor((n-1)/2), r->right);
            r->right = s->left;
            s->left = r;
            return s;
        }

        SgNode<T>* build(int n, T* values){
            if(n == 0)
                return nullptr;
            SgNode<T>* r = build(ceil((n-1)/2), values);
            SgNode<T>* s = build(floor((n-1)/2), values + ceil((n-1)/2) + 1);
            r->right = s->left;
            s->left = r;
            return s;
        }

        int size(SgNode<T>* node){
            if(node == nullptr)
                return 0;
            
            return size(node->left) + size(node->right) + 1;
        }

        int height_a(SgNode<T>* node){
            return floor(log(size(node)) / log(1/ALPHA));
        }

        int height(SgNode<T>* node){
            if(node == nullptr)
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