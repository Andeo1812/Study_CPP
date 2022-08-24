#pragma once  //  NOLINT

#include "Node.hpp"

template<typename T = byte>
class BitReader {
    std::vector <T> buffer;

    size_t free_bit;

    size_t count_ABS;
public:
    BitReader(std::vector <T> buffer) : buffer(buffer) {
        free_bit = buffer[0];
        count_ABS = buffer[1];
    }

    BitReader() = default;

    size_t GetFreeBits() const;

    size_t GetTree(NodeABS<T> *&root) const;

    void GetDecodeDataZeroFreeBit(const size_t start_pos, NodeABS<T> *root,
                                  std::vector <T> &decode) const;

    void GetDecodeDataNonNullFreeBit(const size_t start_pos, NodeABS<T> *root,
                                     std::vector <T> &decode) const;

    const std::vector <T> &GetBuffer() const;

    void Print() const;
};

#include "BitReaderDefinition.hpp"
