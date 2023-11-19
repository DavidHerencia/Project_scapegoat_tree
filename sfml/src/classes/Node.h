#pragma once
#include "GFXNode.h"
//Standard BST node, it is also used in the Scapegoat Tree
template <typename T>
struct ScgNode{
    T data;
    ScgNode<T> *left{}, *right{};
    GFXNode<T>* graphic;

    ScgNode() = default;

    ScgNode(T value){
        data = value;
        left = right = nullptr;
    }

    bool isLeaf(){
        return left == nullptr && right == nullptr;
    }
};