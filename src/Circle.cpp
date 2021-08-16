#include "Circle.hpp"

Circle :: Circle (const int16_t x, const int16_t y, const int16_t radius_in_px,
						const Color & color, const bool filled)
	: Figure(x, y, color, filled), radius_in_px_(radius_in_px)
{
}

void Circle :: draw(std::shared_ptr<SDL_Renderer> renderer) {
	if ( filled_ ) {
		filledCircleColor(renderer.get(), x_position_, y_position_, radius_in_px_, color_.get_color());
	} else {
		circleColor(renderer.get(), x_position_, y_position_, radius_in_px_, color_.get_color());
	}
}

int16_t Circle :: radius_in_px() const noexcept {
	return radius_in_px_;
}

void Circle :: set_radius_in_px(const int16_t radius) noexcept {
	radius_in_px_ = radius;
}

