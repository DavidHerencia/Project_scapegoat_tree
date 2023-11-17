#pragma once

#include <iostream>
#include <queue>
#include <cmath>
#include "Stack.h"

using namespace std;

#define ALPHA 0.57

//Standard BST node, it is also used in the Scapegoat Tree
template <typename T>
struct ScgNode{
    T data;
    ScgNode<T> *left{}, *right{};

    ScgNode() = default;

    ScgNode(T value){
        data = value;
        left = right = nullptr;
    }

};

//Scapegoat Tree class implementation
template <typename T>
class ScgTree{
    ScgNode<T>* root = nullptr;
    int treeSize, maxTreeSize;

    public:
        ScgTree(){
            treeSize = 0;
            maxTreeSize = 0;
        }
        ~ScgTree(){
            clear(root);
        }

        void insert(T value){
            //insert_nr(this->root,value);
            bool rebuilding = false;
            insert(this->root,value, rebuilding);
            treeSize++;
            if(treeSize > maxTreeSize){
                maxTreeSize = treeSize;
            }
        }

        ScgNode<T>* find(T value){
            //Todo
        }

        void remove(T value){
            //Todo
        }

        void pretty(){
            pretty(root, 0);
        }

    private:
        void insert(ScgNode<T>*& node, T& value, bool& rebuilding){
            //caso base
            if(node == nullptr){
                node = new ScgNode<T>(value);
                return;
            }

            // find the insertion point of the new node
            if(value < node->data){
                insert(node->left, value, rebuilding);
            }
            else if (value > node->data){
                insert(node->right, value, rebuilding);
            }
            else{
                // value is already in the tree
                return;
            }


            // return of the recursion
            // check if node is unbalanced
            if (double(height(node)) > height_a(node)  && !rebuilding){
                int subtreeSize = size(node);

                // rebuild the subtree
                rebuild(subtreeSize, node);
                rebuilding = true; // to avoid rebuilding upwards in the recursion
            }
        }

        void rebuild(int n, ScgNode<T>* &scapegoat){
            ScgNode<T>* dumi_node = new ScgNode<T>();  // w en el paper
            ScgNode<T>* list; // z en el paper 

            // Flatten the tree rooted at scapegoat
            list = flatten(scapegoat, dumi_node);
            
            // Build a balanced tree from the list of nodes
            scapegoat = buildTree(n, list);

            // actualizar el nodo padre del subTree
            scapegoat = dumi_node->left;
            delete dumi_node;
        }
        
        //Flatten the tree rooted at node (IN PLACE)
        ScgNode<T>* flatten(ScgNode<T>* node, ScgNode<T>* list){
            if (node == nullptr)
                return list;
            node->right = flatten(node->right, list);
            return flatten(node->left, node);
        }


        // Build a balanced tree from the list of nodes
        ScgNode<T>* buildTree(int n, ScgNode<T>* head){
            // caso base
            if(n == 0){
                //if(head != nullptr) (ojo) 
                    head->left = nullptr;
                return head;
            }

            float numberx = (float(n)-1)/2;

            ScgNode<T>* r = buildTree(ceil(numberx), head);
            // mientras no sea el ultimo nodo del arbol en la lista
            if (r->right->right != nullptr){
                ScgNode<T>* s = buildTree(floor(numberx), r->right);
                r->right = s->left;
                s->left = r;
                return s;    
            }

            // caso de fin:
            // caso donde head es el ultimo nodo del arbol en la lista
            // es decir el nodo mayor del subarbol
            ScgNode<T>* s = r->right;
            r->right = s->left;
            s->left = r;
            return s;
        }


        T* inOrdenAuxiliar(ScgNode<T>* node, T* values, int index){
            if(node == nullptr)
                return values;
            
            values = inOrdenAuxiliar(node->left, values, index);
            values[index++] = node->data;
            cout << node->data << " ";
            values = inOrdenAuxiliar(node->right, values, index);
            return values;
        }


        int size(ScgNode<T>* node){
            if(node == nullptr)
                return 0;
            
            return size(node->left) + size(node->right) + 1;
        }

        double height_a(ScgNode<T>* node){
            return floor(log(double(size(node))) / log(1.0/ALPHA));
        }

        int height(ScgNode<T>* node){
            if(node == nullptr)
                return -1;

            int leftHeight = height(node->left);
            int rightHeight = height(node->right);

            return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
        }

        void clear(ScgNode<T>* node){
            if(!node)
                return;
            clear(node->left);
            clear(node->right);
            node->left = node->right = nullptr;
            delete node;
        }

        void pretty(ScgNode<T>* node, int level){
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