#include "Ant.hpp"



void Ant :: update_position (const uint32_t new_position) noexcept {
	position_ = new_position;
}

uint32_t Ant :: position() const noexcept {
	return position_;
}
