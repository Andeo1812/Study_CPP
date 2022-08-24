#include <vector>
#include <ostream>
#include <iostream>
#include <cstddef>
#include <bitset>
#include <stack>

#include "Node.hpp"

#include "BitReader.hpp"

template<typename T>
void BitReader<T>::GetDecodeDataZeroFreeBit(const size_t start_pos, NodeABS<T> *root, std::vector <T> &decode) const {
    NodeABS<T> **cur = &root;

    size_t i = start_pos;

    while (true) {
        NodeABS<T> &node = **cur;

        if (!node.right && !node.left) {
            decode.push_back(node.data);

            cur = &root;

            continue;
        }

        if (i % 8 == free_bit && i / 8 == buffer.size()) {
            break;
        }

        if ((buffer[i / 8] >> (7 - i % 8)) & 1) {
            cur = &node.right;
            ++i;
        } else {
            cur = &node.left;
            ++i;
        }
    }
}

template<typename T>
void BitReader<T>::GetDecodeDataNonNullFreeBit(const size_t start_pos, NodeABS<T> *root, std::vector <T> &decode) const {
    NodeABS<T> **cur = &root;

    size_t i = start_pos;

    while (true) {
        NodeABS<T> &node = **cur;

        if (!node.right && !node.left) {
            decode.push_back(node.data);

            cur = &root;

            continue;
        }

        if (i % 8 == 8 - free_bit && i / 8 == buffer.size() - 1) {
            break;
        }

        if ((buffer[i / 8] >> (7 - i % 8)) & 1) {
            cur = &node.right;
        } else {
            cur = &node.left;
        }

        ++i;
    }
}

template<typename T>
size_t BitReader<T>::GetTree(NodeABS<T> *&root) const {
    if (free_bit == 255) {
        root = nullptr;
        return 0;
    }

    std::stack < NodeABS<T> * > s;

    size_t i = 8 * 2;

    size_t count_read_abs = 0;
    while (count_read_abs < count_ABS || s.size() > 1) {
        if ((buffer[i / 8] >> (7 - i % 8)) & 1) {
            ++i;

            NodeABS<T> *new_node = new NodeABS<T>({});

            for (size_t j = 0; j < 8; ++j) {
                if ((buffer[i / 8] >> (7 - i % 8)) & 1) {
                    new_node->data |= 1 << (7 - j % 8);
                }

                ++i;
            }

            s.push(new_node);

            ++count_read_abs;
        } else {
            ++i;

            NodeABS<T> *right = s.top();
            s.pop();

            NodeABS<T> *left = s.top();
            s.pop();

            NodeABS<T> *new_node = new NodeABS<T>({});

            new_node->left = left;
            new_node->right = right;

            s.push(new_node);
        }
    }

    root = s.top();

    return i;
}

template<typename T>
const std::vector <T> &BitReader<T>::GetBuffer() const {
    return buffer;
}

template<typename T>
size_t BitReader<T>::GetFreeBits() const {
    return free_bit;
}

template<typename T>
void BitReader<T>::Print() const {
    for (auto &value: GetBuffer()) {
        std::cout << std::bitset<8>(value) << "|";
    }

    std::cout  << "Count bytes " << GetBuffer().size();
}
