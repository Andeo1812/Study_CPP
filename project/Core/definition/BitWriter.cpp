#include <vector>

#include "BitWriter.hpp"

size_t BitWriter::GetFreeBits() const {
    size_t free_bit = 8 - bit_count % 8;
    if (free_bit == 8) {
        return 0;
    } else {
        return free_bit;
    }
}

BitWriter &BitWriter::operator+=(const BitWriter &other) {
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

void BitWriter::Remove(const size_t count) {
    for (size_t i = 0; i < count; ++i) {
        --bit_count;

        buffer[bit_count / 8] = (buffer[bit_count / 8] >> 8 - bit_count % 8) << 8 - bit_count % 8;
    }

}

std::ostream &operator<<(std::ostream &out, const BitWriter &bw) {
    if (!bw.bit_count) {
        return out;
    }

    for (auto &byte: bw.GetBuffer()) {
        out << std::bitset<8>(byte) << "|";
    }

    out << bw.bit_count;

    return out;
}

const size_t BitWriter::GetBitCount() const {
    return bit_count;
}

const std::vector <byte> &BitWriter::GetBuffer() const {
    return buffer;
}

void BitWriter::WriteBit(byte bit) {
    if (bit_count == buffer.size() * 8) {
        buffer.push_back(0);
    }

    if (bit) {
        buffer[bit_count / 8] |= 1 << (7 - bit_count % 8);
    }

    ++bit_count;
}

void BitWriter::WriteByte(byte byte) {
    if (bit_count % 8 == 0) {
        buffer.push_back(byte);
    } else {
        size_t offset = bit_count % 8;

        buffer[bit_count / 8] |= byte >> offset;

        buffer.push_back(byte << (8 - offset));
    }

    bit_count += 8;
}
