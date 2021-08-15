#ifndef AUX_HPP
#define AUX_HPP 

template <typename T>
concept floating_point = std::is_floating_point_v<T>;

template <floating_point T>
bool are_equals(const T & a, const T & b);

#endif
