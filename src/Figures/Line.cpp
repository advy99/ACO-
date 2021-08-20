#include "Figures/Line.hpp"

Line :: Line(const int16_t x1, const int16_t y1,
				 const int16_t x2, const int16_t y2, 
				 const uint8_t line_width, const Color & color)
				: Figure(x1, y1, color, true), x_end_(x2), y_end_(y2), line_width_(line_width)
{}

void Line :: draw(std::shared_ptr<SDL_Renderer> renderer) const noexcept {
	// SDL2_gfx does not have aaThickLineColor, so lines with small widths are uglys
	// if we dont apply anti aliasing
	if (line_width_ > WIDTH_THICK_EPSILON) {
		thickLineColor(renderer.get(), x_position_, y_position_, x_end_, y_end_, line_width_, color_.get_color());
	} else {
		aalineColor(renderer.get(), x_position_, y_position_, x_end_, y_end_, color_.get_color());
	}
}

int16_t Line :: x_end() const noexcept {
	return x_end_;
}

int16_t Line :: y_end() const noexcept {
	return y_end_;
}

uint8_t Line :: line_width() const noexcept {
	return line_width_;
}

void Line :: set_x_end (const int16_t x_end) noexcept {
	x_end_ = x_end;
}

void Line :: set_y_end (const int16_t y_end) noexcept {
	y_end_ = y_end;
}

void Line :: set_line_width (const uint8_t line_width) noexcept {
	line_width_ = line_width;
}
