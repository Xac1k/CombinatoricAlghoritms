#pragma once
#include <vector>

template<typename T>
using List = std::vector<T>;

template<typename T>
using AgileMatrix = List<List<T>>;

template<typename T, size_t N>
using Array = std::array<T, N>;

template<typename T, size_t N>
using StrictedMatrix = Array<Array<T, N>, N>;