#pragma once  //  NOLINT

#include "Node.hpp"

class BitReader {
    std::vector <byte> buffer;

    size_t free_bit;

    size_t count_ABS;
public:
    BitReader(std::vector <byte> buffer) : buffer(buffer) {
        free_bit = buffer[0];
        count_ABS = buffer[1];
    }

    BitReader() = default;

    size_t GetFreeBits() const;

    size_t GetTree(NodeABS<byte> *&root) const;

    void GetDecodeDataZeroFreeBit(const size_t start_pos, NodeABS<byte> *root,
                                  std::vector <byte> &decode) const;

    void GetDecodeDataNonNullFreeBit(const size_t start_pos, NodeABS<byte> *root,
                                     std::vector <byte> &decode) const;

    const std::vector <byte> &GetBuffer() const;

    friend std::ostream &operator<<(std::ostream &out, const BitReader &br);
};
