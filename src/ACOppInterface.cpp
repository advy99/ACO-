#include "ACOppInterface.hpp"
#include <iostream>

void SDL_WindowDeleter :: operator()(SDL_Window * window) {
	SDL_DestroyWindow(window);
}

void SDL_RendererDeleter :: operator()(SDL_Renderer * renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}



bool ACOppInterface :: init ( const std::string & title, 
										const uint32_t X_POS, const uint32_t Y_POS,
										const uint32_t WIDTH, const uint32_t HEIGHT,
										const int32_t FLAGS) {
	bool success = true;

	if ( SDL_Init(SDL_INIT_EVERYTHING ) < 0 ) {
		std::cerr << "SDL could not initialize. SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	} else {
		window_.reset(SDL_CreateWindow(title.c_str(), X_POS, Y_POS, WIDTH, HEIGHT, FLAGS));
		
		if ( window_ == nullptr) {
			std::cerr << "SDL could not create window. SDL_Error: " << SDL_GetError() << std::endl;
			success = false;	
		} else {
			renderer_.reset(SDL_CreateRenderer(window_.get(), -1, 0));

			if (renderer_ == nullptr ) {
				std::cerr << "SDL could not create renderer. SDL_Error: " << SDL_GetError() << std::endl;
				success = false;	
			} else {
				// TODO: Inicializar los objetos que tengamos
				SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
			}
		}

	}

	running_ = success;

	return success;

}

void ACOppInterface :: render () {

	SDL_RenderClear(renderer_.get());

	// TODO: Dibujar objetos

	SDL_RenderPresent(renderer_.get());

}

bool ACOppInterface :: running() const {
	return running_;
}

void ACOppInterface :: handle_events() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if ( event.type == SDL_QUIT || event.type == SDL_KEYDOWN ) {
			running_ = false;
		}
	}

}
