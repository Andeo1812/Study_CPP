#pragma once  //  NOLINT

#include <vector>
#include <iostream>

#include "BitWriter.hpp"

template<typename T>
size_t BitWriter<T>::GetFreeBits() const {
    size_t free_bit = 8 - bit_count % 8;
    if (free_bit == 8) {
        return 0;
    } else {
        return free_bit;
    }
}

template<typename T>
BitWriter<T> &BitWriter<T>::operator+=(const BitWriter<T> &other) {
    size_t free_pos_left = 8 - bit_count % 8;

    size_t free_pos_right = 8 - other.bit_count % 8;

    size_t start_size = buffer.size();

    for (auto &data: other.buffer) {
        buffer.push_back(data);
    }

    if (free_pos_left != 8) {
        for (size_t j = 0; j < other.buffer.size(); ++j) {
            for (size_t i = 0; i < free_pos_left; ++i) {
                if ((buffer[start_size + j] >> (7 - i)) & 1) {
                    buffer[start_size + j - 1] |= 1 << (7 - bit_count % 8 - i);
                }
            }

            buffer[start_size + j] = buffer[start_size + j] << (free_pos_left);
        }

        if (free_pos_left % 8 < 8 && free_pos_right < 8) {
            if (free_pos_left >= other.bit_count % 8) {
                buffer.pop_back();
            }
        }
    }

    bit_count += other.bit_count;

    return *this;
}

template<typename T>
void BitWriter<T>::Remove(const size_t count) {
    for (size_t i = 0; i < count; ++i) {
        --bit_count;

        buffer[bit_count / 8] = (buffer[bit_count / 8] >> 8 - bit_count % 8) << 8 - bit_count % 8;
    }

}

template<typename T>
void BitWriter<T>::Print() const {
    for (auto &byte: GetBuffer()) {
        std::cout << std::bitset<8>(byte) << "|";
    }

    std::cout << bit_count;
}

template<typename T>
const size_t BitWriter<T>::GetBitCount() const {
    return bit_count;
}

template<typename T>
const std::vector <T> &BitWriter<T>::GetBuffer() const {
    return buffer;
}

template<typename T>
void BitWriter<T>::WriteBit(T bit) {
    if (bit_count == buffer.size() * 8) {
        buffer.push_back(0);
    }

    if (bit) {
        buffer[bit_count / 8] |= 1 << (7 - bit_count % 8);
    }

    ++bit_count;
}

template<typename T>
void BitWriter<T>::WriteByte(T byte) {
    if (bit_count % 8 == 0) {
        buffer.push_back(byte);
    } else {
        size_t offset = bit_count % 8;

        buffer[bit_count / 8] |= byte >> offset;

        buffer.push_back(byte << (8 - offset));
    }

    bit_count += 8;
}
