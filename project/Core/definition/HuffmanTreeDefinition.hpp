#pragma once  //  NOLINT

#include <iostream>
#include <stack>

#include "Node.hpp"

#include "HuffmanTree.hpp"

template<typename T>
auto BinaryTreeHuffman<T>::GetDecode() {
    if (decode.GetFreeBits() == 0) {
        decode.GetDecodeDataZeroFreeBit(pos_start, root, res);
    } else {
        decode.GetDecodeDataNonNullFreeBit(pos_start, root, res);
    }

    return res;
}

template<typename T>
BinaryTreeHuffman<T>::BinaryTreeHuffman(BitReader &compressed) {
    pos_start = compressed.GetTree(root);

    decode = compressed;
}

template<typename T>
auto BinaryTreeHuffman<T>::GetTableCode() {
    BitWriter bw;
    CreateTable(root, bw);

    return table_code;
}

template<typename T>
void BinaryTreeHuffman<T>::CreateTable(NodeABS<T> *node, BitWriter bw) {
    if (!node->left && !node->left) {
        table_code.insert({node->data, bw});
    } else {
        if (node->left) {
            bw.WriteBit(0);

            CreateTable(node->left, bw);

            bw.Remove(1);
        }

        if (node->right) {
            bw.WriteBit(1);
            CreateTable(node->right, bw);
        }
    }
}

template<typename T>
void BinaryTreeHuffman<T>::TraverseCreateSer(NodeABS<T> *node) {
    if (!node->left && !node->right) {
        ser_tree.WriteBit(1);

        ser_tree.WriteByte(node->data);
    } else {
        TraverseCreateSer(node->left);

        TraverseCreateSer(node->right);

        ser_tree.WriteBit(0);
    }
}

template<typename T>
auto BinaryTreeHuffman<T>::GetSerTree() {
    if (ser_tree.GetBuffer().empty()) {
        TraverseCreateSer(root);
    }

    return ser_tree;
}

template<typename T>
BinaryTreeHuffman<T>::BinaryTreeHuffman(std::priority_queue < NodeABS<T> * , std::vector < NodeABS<T> * > ,
                                        decltype(more) > min_heap) {
    while (min_heap.size() > 1) {
        NodeABS<T> *left = min_heap.top();
        min_heap.pop();

        NodeABS<T> *right = min_heap.top();
        min_heap.pop();

        NodeABS<T> *new_node = new NodeABS<byte>({}, left->freq + right->freq);

        new_node->left = left;
        new_node->right = right;

        min_heap.push(new_node);
    }

    root = min_heap.top();

    min_heap.pop();
}

template<typename T>
BinaryTreeHuffman<T>::~BinaryTreeHuffman() {
    if (!root) {
        return;
    }

    std::stack < NodeABS<T> * > s;

    s.push(root);

    while (!s.empty()) {
        NodeABS<T> *tmp = s.top();
        s.pop();

        delete tmp;

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }
    }
}

template<typename T>
void BinaryTreeHuffman<T>::Print() const {
    std::stack < NodeABS<T> * > s;

    s.push(root);

    while (!s.empty()) {
        NodeABS<T> *tmp = s.top();
        s.pop();

        std::cout << *tmp;

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }
    }
}

#include "HuffmanTree.hpp"
