#pragma once  //  NOLINT

#include <queue>
#include <map>

#include "Node.hpp"

template<typename T>
class More {
public:
    bool operator()(const NodeABS<T> *first, const NodeABS<T> *second) const {
        return first->freq > second->freq;
    }
};

const More<unsigned char> more;

using heap = std::priority_queue < NodeABS<byte> * , std::vector < NodeABS<byte> * >, decltype(more) >;

void CheckInput(std::vector <byte> &input, std::vector <byte> &input_buffer, heap &min_heap);

void CreateHeap(std::map <byte, size_t> &map, heap &min_heap);

void CustomEncode(std::vector <byte> &original, std::vector <byte> &compressed);

void CustomDecode(std::vector <byte> &compressed, std::vector <byte> &original);