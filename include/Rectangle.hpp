#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP 

#include "aux.hpp"
#include "Color.hpp"

class Rectangle {
	private:
		int16_t x_position_;
		int16_t y_position_;

		int16_t width_;
		int16_t height_;

		Color color_;

		bool filled_;

	public:

		Rectangle(const int16_t x, const int16_t y, 
					 const int16_t width, const int16_t height,
					 const Color & color = {255, 255, 255, 255}, const bool filled = true);

		void draw(std::shared_ptr<SDL_Renderer> renderer);
		
		int16_t x() const noexcept;
		int16_t y() const noexcept;

		int16_t width() const noexcept;
		int16_t height() const noexcept;

		Color color() const noexcept;

		bool filled() const noexcept;

		void set_x(const int16_t x) noexcept;
		void set_y(const int16_t y) noexcept;

		void set_width(const int16_t width) noexcept;
		void set_height(const int16_t height) noexcept;

		void set_color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha = 255) noexcept;
		void set_color(const Color & color) noexcept;

		void set_filled(const bool filled) noexcept;

};


#endif
