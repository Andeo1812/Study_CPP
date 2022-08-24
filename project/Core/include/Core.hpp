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

template<typename T = byte>
void CheckInput(std::vector <T> &input, std::vector <T> &input_buffer, heap &min_heap);

template<typename T = byte>
void CreateHeap(std::map <T, size_t> &map, heap &min_heap);

template<typename T = byte>
void CustomEncode(std::vector <T> &original, std::vector <T> &compressed);

template<typename T = byte>
void CustomDecode(std::vector <T> &compressed, std::vector <T> &original);

#include "CoreDefinition.hpp"
