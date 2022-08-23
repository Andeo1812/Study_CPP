#include <vector>
#include <ostream>
#include <cstddef>
#include <bitset>
#include <stack>

#include "Node.hpp"

#include "BitReader.hpp"

void
BitReader::GetDecodeDataZeroFreeBit(const size_t start_pos, NodeABS<byte> *root, std::vector <byte> &decode) const {
    NodeABS<byte> **cur = &root;

    size_t i = start_pos;

    while (true) {
        NodeABS<byte> &node = **cur;

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

void
BitReader::GetDecodeDataNonNullFreeBit(const size_t start_pos, NodeABS<byte> *root, std::vector <byte> &decode) const {
    NodeABS<byte> **cur = &root;

    size_t i = start_pos;

    while (true) {
        NodeABS<byte> &node = **cur;

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


size_t BitReader::GetTree(NodeABS<byte> *&root) const {
    if (free_bit == 255) {
        root = nullptr;
        return 0;
    }

    std::stack < NodeABS<byte> * > s;

    size_t i = 8 * 2;

    size_t count_read_abs = 0;
    while (count_read_abs < count_ABS || s.size() > 1) {
        if ((buffer[i / 8] >> (7 - i % 8)) & 1) {
            ++i;

            NodeABS<byte> *new_node = new NodeABS<byte>({});

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

            NodeABS<byte> *right = s.top();
            s.pop();

            NodeABS<byte> *left = s.top();
            s.pop();

            NodeABS<byte> *new_node = new NodeABS<byte>({});

            new_node->left = left;
            new_node->right = right;

            s.push(new_node);
        }
    }

    root = s.top();

    return i;
}

const std::vector <byte> &BitReader::GetBuffer() const {
    return buffer;
}

size_t BitReader::GetFreeBits() const {
    return free_bit;
}

std::ostream &operator<<(std::ostream &out, const BitReader &br) {
    for (auto &byte: br.GetBuffer()) {
        out << std::bitset<8>(byte) << "|";
    }

    out << "Count bytes " << br.GetBuffer().size();

    return out;
}
