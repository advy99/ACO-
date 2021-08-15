#include "aux.hpp"


template <floating_point T>
bool are_equals(const T & a, const T & b) {
	return std::abs(a - b) < std::numeric_limits<T>::epsilon();
}

