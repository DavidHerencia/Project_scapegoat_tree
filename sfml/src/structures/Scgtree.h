#pragma once

#include <iostream>
#include <queue>
#include <cmath>
#include "Stack.h"

#include "../classes/Node.h"
#include "../classes/TreeHandler.h"

using namespace std;

#define ALPHA 0.57

//Scapegoat Tree class implementation
template <typename T>
class ScgTree{
    ScgNode<T>* root = nullptr;
    int treeSize, maxTreeSize;
    TreeHandler<T>& treeHandler;
    float sleepTime = 0;

    public:
        ScgTree(TreeHandler<T> & _treeHandler): treeHandler(_treeHandler){
            treeSize = 0;
            maxTreeSize = 0;
        }
        ~ScgTree(){
            clear(root);
        }

        void insert(T value);

        ScgNode<T>* find(T value);

        void remove(T value);

        void pretty(){
            pretty(root, 0);
        }

        void setSleepTime(float val){
            this->sleepTime = val;
        }

        ScgNode<T>* getRoot(){
            return this->root;
        }

    private:
        bool insert(ScgNode<T>*& node, T& value, bool& rebuilding);

        ScgNode<T> *removeRecursion(ScgNode<T> *temp, T value);

        void rebuild(int n, ScgNode<T>* &scapegoat);

        //Flatten the tree rooted at node (IN PLACE)
        ScgNode<T>* flatten(ScgNode<T>* node, ScgNode<T>* list);
        
        // Build a balanced tree from the list of nodes
        ScgNode<T>* buildTree(int n, ScgNode<T>* head);


        T* inOrdenAuxiliar(ScgNode<T>* node, T* values, int index);

        int size(ScgNode<T>* node);

        double height_a(ScgNode<T>* node);

        int height(ScgNode<T>* node);

        void clear(ScgNode<T>* node);

        void pretty(ScgNode<T>* node, int level);
};


// ================== Search ==================
template <typename T>
ScgNode<T>* ScgTree<T>::find(T value) {
    ScgNode<T>* temp = root, *prev = nullptr; // start at root
    while (temp != nullptr) {
    
        if(prev != nullptr)
            prev->graphic->setBorder(false);

        if (value == temp->data)
            return temp; // found

        temp->graphic->setBorder(true);    
        
        prev = temp;
        if (value < temp->data) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }

        sf::sleep(sf::milliseconds(sleepTime));
    }
    return nullptr; // not found
}

// ================== Insert ================== 
template <typename T>
void ScgTree<T>::insert(T value){
    //std::cout << "INSERT! " << value << std::endl;
    bool rebuilding = false;
    bool inserted = false;  // controllar repetidos
    inserted = insert(this->root,value, rebuilding);
    if (inserted){ 
        treeSize++;
        if(treeSize > maxTreeSize){
            maxTreeSize = treeSize;
        }
    }   
    std::cout << "Done!" << std::endl;
    treeHandler.arrangeNodes(this->root,true);
}

template <typename T>
bool ScgTree<T>::insert(ScgNode<T>*& node, T& value, bool& rebuilding){
            //caso base
            if(node == nullptr){
                //std::cout << "FOUND! \n";
                node = new ScgNode<T>(value);
                treeHandler.addNode(node);
                //std::cout << "Inserted " << node->data << std::endl;
                return true;
            }

            //node->graphic->select(true);
            //std::cout << "l or r! \n";
            // find the insertion point of the new node
            if(value < node->data){
                insert(node->left, value, rebuilding);
            }
            else if (value > node->data){
                insert(node->right, value, rebuilding);
            }
            else{
                // value is already in the tree
                return false;
            }

            // return of the recursion
            // check if node is unbalanced
            if (double(height(node)) > height_a(node)  && !rebuilding){
                int subtreeSize = size(node);
                // rebuild the subtree
                rebuild(subtreeSize, node);
                rebuilding = true; // to avoid rebuilding upwards in the recursion
            }
            return true;
        }

// ================== Delete ==================
template <typename T>
void ScgTree<T>::remove(T value) {
    std::cout << "REMOVE! " << value << std::endl;
    // deleting the node as we would from an ordinary binary search tree
    this->root = removeRecursion(root, value);
    // decrement the size of the tree in the function removeRecursion if the node is found

    // check if the tree need rebuilding
    if (treeSize == 0){
        cout << "Tree is empty" << endl;
        maxTreeSize = 0;
        return;
    }
    else if (treeSize < ALPHA * maxTreeSize) {
        rebuild(treeSize, this->root);
        maxTreeSize = treeSize;
    }
    std::cout << "Done!" << std::endl;
    treeHandler.arrangeNodes(this->root,true);
}

template <typename T>
ScgNode<T>* ScgTree<T>::removeRecursion(ScgNode<T>* temp, T value) {
    std::cout << "REMOVE RECURSION! " << value << std::endl;
    if (temp == nullptr) {
        return temp;
    }

    if (temp->data > value) {
        temp->left = removeRecursion(temp->left, value);
        return temp;
    } else if (temp->data < value) {
        temp->right = removeRecursion(temp->right, value);
        return temp;
    }

    if (temp->left == nullptr) {
        ScgNode<T>* temporal = temp->right;
        treeHandler.removeNode(temp);
        treeSize--;
        return temporal;
    } else if (temp->right == nullptr) {
        ScgNode<T> *temporal = temp->left;
        treeHandler.removeNode(temp);
        treeSize--;
        return temporal;
    }
    else {
        ScgNode<T>* succParent = temp;
        ScgNode<T>* succ = temp->right;
        while (succ->left != nullptr) {
            succParent = succ;
            succ = succ->left;
        }

        if (succParent != temp)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        temp->data = succ->data;
        temp->graphic->updateLabel();
        treeHandler.removeNode(succ);
        treeSize--;
        return temp;
    }
}

// ================== Rebuild ==================
template <typename T>
void ScgTree<T>::rebuild(int n, ScgNode<T>* &scapegoat){
    ScgNode<T>* dumi_node = new ScgNode<T>();  // w en el paper
    ScgNode<T>* list; // z en el paper 

    // Flatten the tree rooted at scapegoat
    list = flatten(scapegoat, dumi_node);
    // Build a balanced tree from the list of nodes
    scapegoat = buildTree(n, list);
    // actualizar el nodo padr  e del subTree
    scapegoat = dumi_node->left;
    delete dumi_node;
}
        
template <typename T>
ScgNode<T>* ScgTree<T>::flatten(ScgNode<T>* node, ScgNode<T>* list){
    // Flatten the tree rooted at node (IN PLACE)
    if (node == nullptr)
        return list;

    node->right = flatten(node->right, list);
    node->graphic->setBorder(false);
    return flatten(node->left, node);
}


template <typename T>
ScgNode<T>* ScgTree<T>::buildTree(int n, ScgNode<T>* head){
    // Build a balanced tree from the list of nodes
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

// ================ Functions =============
template <typename T>
int ScgTree<T>::size(ScgNode<T>* node){
    if(node == nullptr)
        return 0;

    return size(node->left) + size(node->right) + 1;
}

template <typename T>
double ScgTree<T>::height_a(ScgNode<T>* node){
    return floor(log(double(size(node))) / log(1.0/ALPHA)); // log1/ALPHA(size(node))
}

template <typename T>
int ScgTree<T>::height(ScgNode<T>* node){
    if(node == nullptr)
        return -1;

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

template <typename T>
T* ScgTree<T>::inOrdenAuxiliar(ScgNode<T>* node, T* values, int index){
    if(node == nullptr)
        return values;
    
    values = inOrdenAuxiliar(node->left, values, index);
    values[index++] = node->data;
    cout << node->data << " ";
    values = inOrdenAuxiliar(node->right, values, index);
    return values;
}

template <typename T>
void ScgTree<T>::clear(ScgNode<T>* node){
    if(!node)
        return;
    clear(node->left);
    clear(node->right);
    node->left = node->right = nullptr;
    delete node;
}

template <typename T>
void ScgTree<T>::pretty(ScgNode<T>* node, int level){
    if(!node)
        return;
    pretty(node->right, level+1);
    for(int i = 0; i < level; i++){
        cout << "   ";
    }
    cout << node->data << endl;
    pretty(node->left, level+1);
}