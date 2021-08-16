#ifndef CIRCLE_HPP
#define CIRCLE_HPP 

#include "aux.hpp"
#include "Figure.hpp"

class Circle : public Figure {
	private:
		int16_t radius_in_px_;

	public:
		Circle(const int16_t x, const int16_t y, const int16_t radius_in_px, 
				 const Color & color = {255, 255, 255, 255}, const bool filled = true);

		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const noexcept override;

		int16_t radius_in_px () const noexcept;

		void set_radius_in_px(const int16_t radius) noexcept;


};


#endif 
