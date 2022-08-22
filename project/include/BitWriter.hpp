#pragma once  //  NOLINT

class BitWriter {
    std::vector <byte> buffer;

    size_t bit_count;
public:
    BitWriter() : bit_count(0) {}

    void WriteBit(byte bit);

    void WriteByte(byte byte);

    void Remove(const size_t count);

    size_t GetFreeBits() const;

    const std::vector <byte> &GetBuffer() const;

    const size_t GetBitCount() const;

    BitWriter &operator+=(const BitWriter &other);

    friend std::ostream &operator<<(std::ostream &out, const BitWriter &bw);
};
