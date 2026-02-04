#define TYPES_H
#include <vector>

template<typename T>
using List = std::vector<T>;

template<typename T>
using Matrix = List<List<T>>;