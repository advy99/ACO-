#ifndef ACOPPINTERFACE_HPP
#define ACOPPINTERFACE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

#include "Rectangle.hpp"


struct SDL_WindowDeleter {
	void operator()(SDL_Window * window);
};

struct SDL_RendererDeleter {
	void operator()(SDL_Renderer * renderer);
};

class ACOppInterface {
	private:
		bool running_ = false;

		std::unique_ptr<SDL_Window, SDL_WindowDeleter> window_ = nullptr;
		std::shared_ptr<SDL_Renderer> renderer_ = nullptr;

		int32_t current_frame_ = 0;

		// TODO: Create a base class for all objects we will show 
		// std::vector<> objects_;
	
		std::unique_ptr<Rectangle> background;
		std::unique_ptr<Rectangle> rect1;
		std::unique_ptr<Rectangle> rect2;
	
	public:

		ACOppInterface() = default;
		~ACOppInterface() = default;


		bool init(const std::string & title, const uint32_t X_POS, const uint32_t Y_POS,
					 const uint32_t WIDTH, const uint32_t HEIGHT, const int32_t FLAGS);

		void render();

		void draw();

		void update();

		void handle_events();

		void clean();

		bool running() const;

		void quit();

		uint32_t width();
		uint32_t height();

		std::shared_ptr<SDL_Renderer> renderer() const;
		
};


#endif
