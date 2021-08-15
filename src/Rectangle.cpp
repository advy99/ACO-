#include "Rectangle.hpp"

Rectangle :: Rectangle (const int16_t x, const int16_t y,
								const int16_t width, const int16_t height,
								const Color & color, const bool filled)
	:x_position_(x), y_position_(y), width_(width), height_(height),
	 color_(color), filled_(filled)
{
}

void Rectangle :: draw(std::shared_ptr<SDL_Renderer> renderer) {
	if ( filled_ ) {
		boxColor(renderer.get(), x_position_, y_position_, x_position_ + width_, y_position_ + height_, color_.get_color());
	} else {
		rectangleColor(renderer.get(), x_position_, y_position_, x_position_ + width_, y_position_ + height_, color_.get_color());
	}
}

int16_t Rectangle :: x() const noexcept {
	return x_position_;
}

int16_t Rectangle :: y() const noexcept {
	return y_position_;
}

int16_t Rectangle :: width() const noexcept {
	return width_;
}

int16_t Rectangle :: height() const noexcept {
	return height_;
}

Color Rectangle :: color() const noexcept {
	return color_;
}

bool Rectangle :: filled() const noexcept {
	return filled_;
}

void Rectangle :: set_x(const int16_t x) noexcept {
	x_position_ = x;
}

void Rectangle :: set_y(const int16_t y) noexcept {
	y_position_ = y;
}

void Rectangle :: set_width(const int16_t width) noexcept {
	width_ = width;
}

void Rectangle :: set_height(const int16_t height) noexcept {
	height_ = height;
}


void Rectangle :: set_color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) noexcept {
	color_.set_red(red);
	color_.set_green(green);
	color_.set_blue(blue);
	color_.set_alpha(alpha);
}

void Rectangle :: set_color(const Color & color) noexcept {
	color_ = color;
}

void Rectangle :: set_filled(const bool filled) noexcept {
	filled_ = filled;
}
