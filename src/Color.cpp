#include "Color.hpp"


Color :: Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
					:red_(red), green_(green), blue_(blue), alpha_(alpha)
{
}

uint8_t Color :: red() const noexcept {
	return red_;
}


uint8_t Color :: green() const noexcept {
	return green_;
}


uint8_t Color :: blue() const noexcept {
	return blue_;
}


uint8_t Color :: alpha() const noexcept {
	return alpha_;
}

uint32_t Color :: get_color() const noexcept {
	uint32_t result = red_;
	result |= static_cast<uint32_t>(green_) << 8;
	result |= static_cast<uint32_t>(blue_) << 16;
	result |= static_cast<uint32_t>(alpha_) << 24;
	
	return result;

}

void Color :: set_color(const uint32_t color) const noexcept {
	red_ = static_cast<uint8_t>( (color >> 24) & 0x000000FF);
	green_ = static_cast<uint8_t>( (color >> 16) & 0x000000FF);
	blue_ = static_cast<uint8_t>( (color >> 8) & 0x000000FF);
	alpha_ = static_cast<uint8_t>( color & 0x000000FF);
}

void Color :: set_red(const uint8_t red) const noexcept {
	red_ = red;
}

void Color :: set_green(const uint8_t green) const noexcept {
	green_ = green;
}

void Color :: set_blue(const uint8_t blue) const noexcept {
	blue_ = blue;
}

void Color :: set_alpha(const uint8_t alpha) const noexcept {
	alpha_ = alpha;
}

