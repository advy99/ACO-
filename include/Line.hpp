#ifndef LINE_HPP
#define LINE_HPP 

#include "Figure.hpp"

class Line : public Figure {
	private:
		int16_t x_end_;
		int16_t y_end_;

		uint8_t line_width_;

	public:

		static const uint8_t WIDTH_THICK_EPSILON = 5;

		Line(const int16_t x1, const int16_t y1, const int16_t x2, const int16_t y2, const uint8_t line_width, const Color & color);

		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const noexcept override;	

		int16_t x_end() const noexcept;
		int16_t y_end() const noexcept;

		uint8_t line_width() const noexcept;

		void set_x_end(const int16_t x_end) noexcept;
		void set_y_end(const int16_t y_end ) noexcept;
		void set_line_width(const uint8_t line_width) noexcept;

};

#endif 
