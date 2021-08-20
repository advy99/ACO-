#include "Figures/Figure.hpp"


Figure :: Figure (const int16_t x, const int16_t y,
						const Color & color, const bool filled)
	:x_position_(x), y_position_(y), color_(color), filled_(filled)
{
}


int16_t Figure :: x() const noexcept {
	return x_position_;
}

int16_t Figure :: y() const noexcept {
	return y_position_;
}


Color Figure :: color() const noexcept {
	return color_;
}

bool Figure :: filled() const noexcept {
	return filled_;
}

void Figure :: set_x(const int16_t x) noexcept {
	x_position_ = x;
}

void Figure :: set_y(const int16_t y) noexcept {
	y_position_ = y;
}


void Figure :: set_color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) noexcept {
	color_.set_red(red);
	color_.set_green(green);
	color_.set_blue(blue);
	color_.set_alpha(alpha);
}

void Figure :: set_color(const Color & color) noexcept {
	color_ = color;
}

void Figure :: set_filled(const bool filled) noexcept {
	filled_ = filled;
}
