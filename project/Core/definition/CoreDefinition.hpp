#include <queue>
#include <vector>
#include <cstddef>
#include <map>
#include <ostream>

#include "Node.hpp"
#include "Core.hpp"

#include "HuffmanTree.hpp"
#include "BitReader.hpp"

template<typename T>
void CheckInput(std::vector <T> &input, std::vector <T> &input_buffer, heap &min_heap) {
    std::map <T, size_t> mapABS;

    for (auto data: input) {
        auto needed_node = mapABS.find(data);

        if (needed_node == mapABS.end()) {
            mapABS.insert({data, 1});
        } else {
            needed_node->second++;
        }

        input_buffer.push_back(data);
    }

    CreateHeap(mapABS, min_heap);
}

template<typename T>
void CreateHeap(std::map <T, size_t> &map, heap &min_heap) {
    for (auto &data: map) {
        NodeABS<T> *node = new NodeABS<T>(data.first, data.second);

        min_heap.push(node);
    }
}

template<typename T>
void CustomEncode(std::vector <T> &original, std::vector <T> &compressed) {
    std::vector <T> input_buffer;

    std::priority_queue < NodeABS<T> * , std::vector < NodeABS<T> * >, decltype(more) > min_heap;

    CheckInput(original, input_buffer, min_heap);

    BinaryTreeHuffman<T> tree_huffman_encode(min_heap);

    auto table = tree_huffman_encode.GetTableCode();

    if (table.empty()) {
        compressed = original;
        return;
    }

    BitWriter begin;

    if (table.size() < 256) {
        begin.WriteByte(table.size());
    } else {
        begin.WriteByte(table.size() - 1);
    }

    begin += tree_huffman_encode.GetSerTree();

    BitWriter code;

    for (auto &data: input_buffer) {
        auto needed_node = table.find(data);
        begin += needed_node->second;

        code += needed_node->second;
    }

    BitWriter result;

    result.WriteByte(begin.GetFreeBits());

    result += begin;

    compressed = result.GetBuffer();

    if (compressed.size() > original.size()) {

        std::vector <T> null_compress;

        null_compress.push_back(255);

        for (auto &data: original) {
            null_compress.push_back(data);
        }

        compressed = null_compress;
    }

//    std::cout << "TREE" << std::endl;
//    tree_huffman_encode.Print();
//    std::cout << "TABLE" << std::endl;
//    for (auto &data: table) {
//        std::cout << data.first << " " << data.second << std::endl;
//    }
//    std::cout << "TABLE SIZE - " << table.size() << std::endl;
//    std::cout << "SER - " << tree_huffman_encode.GetSerTree() << std::endl;
//    std::cout << "CODE - " << code << std::endl;
//    std::cout << "FREE BITS - " << begin.GetFreeBits() << std::endl;
//    std::cout << result << std::endl;
}

template<typename T>
void CustomDecode(std::vector <T> &compressed, std::vector <T> &original) {
    BitReader br(compressed);

    BinaryTreeHuffman<T> tree_huffman_decode(br);


    if (!tree_huffman_decode.GetRoot()) {
        for (size_t i = 1; i < compressed.size(); ++i) {
            original.push_back(compressed[i]);
        }

        compressed.erase(compressed.begin());

        return;
    }

    auto res = tree_huffman_decode.GetDecode();

    original = res;
}
