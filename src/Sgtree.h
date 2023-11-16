#pragma once

#include <iostream>
#include <queue>
#include <cmath>
#include "Stack.h"

using namespace std;

#define ALPHA 0.57

//Standard BST node, it is also used in the Scapegoat Tree
template <typename T>
struct SgNode{
    T data;
    SgNode<T> *left{}, *right{};

    SgNode() = default;

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
            insert_nr(this->root,value);
            //insert(this->root,value);
            treeSize++;
            if(treeSize > maxTreeSize){
                maxTreeSize = treeSize;
            }
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
            
            //check if node is unbalanced
            int subtreeSizeLeft = size(node->left);
            int subtreeSizeRight = size(node->right);
            int subtreeSize = subtreeSizeLeft + subtreeSizeRight + 1;
            //if(subtreeSizeLeft <= subtreeSize * ALPHA && subtreeSizeRight <= subtreeSize * ALPHA)
                //return;

            // Rebuild tree at node
            //T* values = new T[subtreeSize];
            //inOrdenAuxiliar(node,values,0);

            //Alternative method to determine if node is the scapegoat
            

            // //testeando las 2 maneras
            // cout <<endl<<endl<< node->data << endl; 
            // cout <<"HEIGHT: " << height(node) << endl;
            // cout << "HEIGHT_A: " << height_a(node) << endl;
            // cout << "SIZE: " << size(node) << endl;
            // cout << "MAX SIZE: " << maxTreeSize << endl;
            // cout << "ALPHA: " << ALPHA << endl;

            // cout << "LEFT: " << subtreeSizeLeft << endl;
            // cout << "RIGHT: " << subtreeSizeRight << endl;
            // cout << "TOTAL: " << subtreeSize << endl;
            // cout << "ALPHA * TOTAL: " << ALPHA * subtreeSize<< endl;

            if (ALPHA * subtreeSize < subtreeSizeLeft || ALPHA * subtreeSize < subtreeSizeRight){
                cout << "SCAPEGOAT FOUND WITH A FIRST MODE" << endl;
                cout << "node:  "<<node->data << endl;
            }
            if (double(height(node)) > height_a(node)){
                cout << "SCAPEGOAT FOUND WITH A SECOND MODE  h>h_a  original del paper" << endl;
                cout << "node:  "<<node->data << endl;
                rebuild(subtreeSize,node);
                cout << "REBUILDING pasando a pretty in insert" << endl;
                pretty();
            }
            if (height(node) < height_a(node)){
                cout << "SCAPEGOAT FOUND WITH A SECOND MODE  h<h_a comprendido " << endl;
                cout << "node:  "<<node->data << endl;
            }
                
            return;
        }

        // insert non recursive
        void insert_nr(SgNode<T>* node, T value){
            //caso inicial
            if(node == nullptr){
                this->root = new SgNode<T>(value);
                return;
            }  
            // find the node to insert
            Stack<SgNode<T>*> pila;
            while (node != nullptr) {
                pila.push(node);  // store the path to the node
                if (value < node->data) {
                    if (node->left == nullptr) {
                        node->left = new SgNode<T>(value);
                        break;
                    } 
                    
                    node = node->left;
                } 
                else if (value > node->data) {
                    if (node->right == nullptr) {
                        node->right = new SgNode<T>(value);
                        break;
                    } 
        
                    node = node->right;
                    
                } 
                else {
                    throw "Error: Value already exists";  // valor duplicado
                    return;  // valor duplicado
                }
            } 

            //check if node is unbalanced in the path 
            while(!pila.is_empty()){
                node = pila.pop();
                if (double(height(node)) > height_a(node)){
                    int subtreeSize = size(node);
                    if (node == root)
                        root = rebuild(subtreeSize, node);
                    else
                        rebuild(subtreeSize, node);
                    cout << node->data << endl;
                    cout << "REBUILDING pasando a pretty in insert_nr" << endl;
                    break;
                } 
            }            
        }

        SgNode<T>* rebuild(int n, SgNode<T>* &scapegoat){
            SgNode<T>* dumi_node = new SgNode<T>();
            SgNode<T>* z;

            //Flatten the tree rooted at scapegoat
            z = flatten(scapegoat, dumi_node);
            cout << "FLATTENING SUCCESS "<< z->data << endl;
            // mostrar el flatten
            SgNode<T>* aux = z;
            while(aux != nullptr){
                cout << aux->data << " ->";
                aux = aux->right;
            }
            cout << endl;
            scapegoat = buildTree(n, z);
            scapegoat = dumi_node->left;
            delete dumi_node;
            return scapegoat;
        }
        
        //Flatten the tree rooted at node (IN PLACE)
        SgNode<T>* flatten(SgNode<T>* node, SgNode<T>* list){
            if (node == nullptr)
                return list;
            node->right = flatten(node->right, list);
            return flatten(node->left, node);
        }

        //Build a balanced tree from a list of nodes
        SgNode<T>* buildTree(int n, SgNode<T>* head){
            cout << "BUILDING TREE WITH N: " << n << endl;
            cout << "HEAD: " << head->data << endl;
            if(n == 0){
                    if(head != nullptr)
                    head->left = nullptr;
                return head;
            }
            float numberx = (float(n)-1)/2;
            // cout << "NUMBERX: " << numberx << endl;
            SgNode<T>* r = buildTree(ceil(numberx), head);
            // SgNode<T>* s = buildTree(floor(numberx), r->right);
            // r->right = s->left;
            // s->left = r;
            // return s;

            if (r->right->right != nullptr){
                SgNode<T>* s = buildTree(floor(numberx), r->right);
                r->right = s->left;
                s->left = r;
                // string step{};
                // pretty(head, 0);
                // cin >> step;
                return s;    
            }
            //cout << "R paso el if: " << r->data << endl;
            SgNode<T>* s = r->right;
            r->right = s->left;
            s->left = r;
            // string step{};
            // pretty(head, 0);
            // cin >> step;
            return s;
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

        /*SgNode<T>* build(int n, T* values){
            if(n == 0)
                return nullptr;
            SgNode<T>* r = build(ceil((n-1)/2), values);
            SgNode<T>* s = build(floor((n-1)/2), values + ceil((n-1)/2) + 1);
            r->right = s->left;
            s->left = r;
            return s;
        }*/

        int size(SgNode<T>* node){
            if(node == nullptr)
                return 0;
            
            return size(node->left) + size(node->right) + 1;
        }

        double height_a(SgNode<T>* node){
            return floor(log(double(size(node))) / log(1.0/ALPHA));
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