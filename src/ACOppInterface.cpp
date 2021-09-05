#include "ACOppInterface.hpp"
#include "Figures/Rectangle.hpp"
#include "Figures/Circle.hpp"
#include "Figures/Line.hpp"
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

			background_ = std::make_unique<Rectangle>(0, 0, WIDTH, HEIGHT);

		}
	}

	running_ = true;

}

void ACOppInterface :: render () {

	SDL_RenderClear(renderer_.get());

	background_->draw(renderer_.get());

	for(const auto & city : cities_) {
		city->draw(renderer_.get() );
	} 

	for(const auto & line : lines_) {
		line->draw(renderer_.get() );
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

void ACOppInterface :: add_city(std::unique_ptr<Figure> && object)  {
	cities_.push_back(std::move(object));
}

void ACOppInterface :: clear_cities() {
	cities_.clear();
}

void ACOppInterface :: add_line(std::unique_ptr<Figure> && object)  {
	lines_.push_back(std::move(object));
}

void ACOppInterface :: clear_lines() {
	lines_.clear();
}

void ACOppInterface :: change_lines(std::vector<std::unique_ptr<Figure> > && new_lines) {
	lines_ = std::move(new_lines);
}


std::shared_ptr<SDL_Renderer> ACOppInterface :: renderer() const {
	return renderer_;
}
