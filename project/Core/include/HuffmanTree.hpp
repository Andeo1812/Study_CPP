#pragma once  //  NOLINT

#include "Core.hpp"
#include "BitWriter.hpp"
#include "BitReader.hpp"

template<typename T>
class BinaryTreeHuffman {
    NodeABS<T> *root;

    std::map <T, BitWriter<T>> table_code;

    BitWriter<T> ser_tree;

    BitReader decode;
    size_t pos_start;

    size_t free_pos_bits;

    std::vector <T> res;

    void TraverseCreateSer(NodeABS<T> *node);

    void CreateTable(NodeABS<T> *node, BitWriter<T> bw);

public:
    auto GetRoot() const { return root; }

    void Print() const;

    auto GetSerTree();

    auto GetTableCode();

    auto GetDecode();

    BinaryTreeHuffman() : root(nullptr) {};

    BinaryTreeHuffman(std::priority_queue<NodeABS<T> *, std::vector < NodeABS<T> * >, decltype(more)> min_heap);

    BinaryTreeHuffman(BitReader &compressed);

    ~BinaryTreeHuffman();
};

#include "HuffmanTreeDefinition.hpp"
