#pragma once  //  NOLINT

#include <cstddef>
#include <ostream>
#include <bitset>

#include "Node.hpp"

template<typename T = byte>
class BitWriter {
    std::vector <T> buffer;

    size_t bit_count;
public:
    BitWriter() : bit_count(0) {}

    void WriteBit(T bit);

    void WriteByte(T byte);

    void Remove(const size_t count);

    size_t GetFreeBits() const;

    const std::vector <T> &GetBuffer() const;

    const size_t GetBitCount() const;

    BitWriter<T> &operator+=(const BitWriter<T> &other);

    void Print() const;
};

#include "BitWriterDefinition.hpp"
