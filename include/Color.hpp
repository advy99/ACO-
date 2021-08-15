#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
	private:
		uint8_t red_;
		uint8_t green_;
		uint8_t blue_;
		uint8_t alpha_;
	
	public:
		Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255);

		uint8_t red() const noexcept;
		uint8_t green() const noexcept;
		uint8_t blue() const noexcept;

		uint8_t alpha() const noexcept;

		uint32_t get_color() const noexcept;

		void set_color(const uint32_t color) const noexcept;

		void set_red(const uint8_t red) const noexcept;
		void set_green(const uint8_t green) const noexcept;
		void set_blue(const uint8_t blue) const noexcept;
		void set_alpha(const uint8_t alpha) const noexcept;

}


#endif 
