#ifndef AUX_HPP
#define AUX_HPP 

#include <cstdint>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

template <typename T>
concept floating_point = std::is_floating_point_v<T>;

template <floating_point T>
bool are_equals(const T & a, const T & b) noexcept;

#endif
