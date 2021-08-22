#ifndef AUX_HPP
#define AUX_HPP 

#include <cstdint>
#include <memory>
#include <vector>

#inclue "Random.hpp"
#include "Figures/sdl_headers.hpp"

template <typename T>
concept floating_point = std::is_floating_point_v<T>;

template <floating_point T>
bool are_equals(const T & a, const T & b) noexcept;

#endif
