#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP 

#include "Figure.hpp"

class Rectangle : public Figure {
	private:
		int16_t width_;
		int16_t height_;

	public:

		Rectangle(const int16_t x, const int16_t y, 
					 const int16_t width, const int16_t height,
					 const Color & color = {255, 255, 255, 255}, const bool filled = true);

		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const noexcept override;
		
		int16_t width() const noexcept;
		int16_t height() const noexcept;

		void set_width(const int16_t width) noexcept;
		void set_height(const int16_t height) noexcept;

};


#endif
