//
// Created by dcamachog1501 on 01/06/19.
//

#include "Huffman_Tree.h"

Huffman_Tree::Huffman_Tree()
{
    this->Top= nullptr;
}

Huffman_Node* Huffman_Tree::getTop()
{
    return this->Top;
}

void Huffman_Tree::setTop(Huffman_Node*h)
{
    this->Top=h;
}
