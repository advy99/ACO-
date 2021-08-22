#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <memory>
#include "sdl_headers.hpp"
#include "Color.hpp"

class Figure {
	protected:

		int16_t x_position_;
		int16_t y_position_;

		Color color_;

		bool filled_;

		Figure(const int16_t x, const int16_t y, const Color & color, const bool filled);
	
	public:

		virtual ~Figure() = default;

		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const noexcept = 0;

		int16_t x() const noexcept;
		int16_t y() const noexcept;

		Color color() const noexcept;

		bool filled() const noexcept;

		void set_x(const int16_t x) noexcept;
		void set_y(const int16_t y) noexcept;

		void set_color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha = 255) noexcept;
		void set_color(const Color & color) noexcept;

		void set_filled(const bool filled) noexcept;

};


#endif 
