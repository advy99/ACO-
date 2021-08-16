#include "Rectangle.hpp"

Rectangle :: Rectangle (const int16_t x, const int16_t y,
								const int16_t width, const int16_t height,
								const Color & color, const bool filled)
	: Figure(x, y, color, filled), width_(width), height_(height)
{
}

void Rectangle :: draw(std::shared_ptr<SDL_Renderer> renderer) {
	if ( filled_ ) {
		boxColor(renderer.get(), x_position_, y_position_, x_position_ + width_, y_position_ + height_, color_.get_color());
	} else {
		rectangleColor(renderer.get(), x_position_, y_position_, x_position_ + width_, y_position_ + height_, color_.get_color());
	}
}

int16_t Rectangle :: width() const noexcept {
	return width_;
}

int16_t Rectangle :: height() const noexcept {
	return height_;
}

