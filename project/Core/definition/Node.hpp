#pragma once  //  NOLINT

using byte = u_int8_t;

template<typename T = byte>
struct NodeABS {
    T data;
    size_t freq;

    NodeABS *left;
    NodeABS *right;

    NodeABS(const T &data, size_t freq = 1) : data(data), freq(freq), left(nullptr), right(nullptr) {}

    friend std::ostream &operator<<(std::ostream &os, const NodeABS &it) {
        return os << it.data << " " << it.freq << std::endl;
    }
};

template<typename T>
class More {
public:
    bool operator()(const NodeABS<T> *first, const NodeABS<T> *second) const {
        return first->freq > second->freq;
    }
};

const More<unsigned char> more;
