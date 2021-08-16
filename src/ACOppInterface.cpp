#include "ACOppInterface.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Line.hpp"
#include <iostream>

void SDL_WindowDeleter :: operator()(SDL_Window * window) {
	SDL_DestroyWindow(window);
}

void SDL_RendererDeleter :: operator()(SDL_Renderer * renderer) {
	SDL_DestroyRenderer(renderer);
}



ACOppInterface :: ACOppInterface ( const std::string & title, 
											  const uint32_t X_POS, const uint32_t Y_POS,
											  const uint32_t WIDTH, const uint32_t HEIGHT,
											  const int32_t FLAGS) {

	window_.reset(SDL_CreateWindow(title.c_str(), X_POS, Y_POS, WIDTH, HEIGHT, FLAGS));
	
	if ( window_ == nullptr) {
		throw std::runtime_error("SDL could not create window. SDL_Error: " + std::string(SDL_GetError()) + "\n");
	} else {
		renderer_.reset(SDL_CreateRenderer(window_.get(), -1, 0), SDL_RendererDeleter());

		if (renderer_ == nullptr ) {
			throw std::runtime_error("SDL could not create renderer. SDL_Error: " + std::string(SDL_GetError()) + "\n");
		} else {
			// TODO: Inicializar los objetos que tengamos
			SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);

			
			objects_.push_back(std::make_unique<Rectangle>(0, 0, WIDTH, HEIGHT));
			objects_.push_back(std::make_unique<Rectangle>(50, 55, 100, 100, Color(255, 0, 0, 190), false)); 
			objects_.push_back(std::make_unique<Rectangle>(80, 80, 300, 100, Color(0, 0, 0, 255), true)); 
			objects_.push_back(std::make_unique<Circle>(380, 80, 50, Color(0, 0, 200, 255), true)); 
			objects_.push_back(std::make_unique<Circle>(380, 280, 50, Color(0, 0, 200, 255), false)); 
			objects_.push_back(std::make_unique<Line>(50, 400, 600, 370, 7, Color(50, 100, 200, 255))); 
		}
	}

	running_ = true;

}

void ACOppInterface :: render () {

	SDL_RenderClear(renderer_.get());

	for(const auto & object : objects_) {
		object->draw(renderer_);
	} 

	SDL_RenderPresent(renderer_.get());

}

bool ACOppInterface :: running() const {
	return running_;
}

void ACOppInterface :: handle_events() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if ( event.type == SDL_QUIT) {
			running_ = false;
		}
	}

}

std::shared_ptr<SDL_Renderer> ACOppInterface :: renderer() const {
	return renderer_;
}
