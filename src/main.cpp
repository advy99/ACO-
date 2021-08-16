#include "ACOppInterface.hpp"


void run_interface() {

	const uint32_t FPS = 60;
	const uint32_t DELAY_TIME = 1000.0 / FPS;

	ACOppInterface interface("Prueba SDL", 100, 100, 640, 480, 0);

	while ( interface.running() ) {
		uint32_t frame_start, frame_time;
		frame_start = SDL_GetTicks();

		interface.handle_events();
		interface.render();

		frame_time = SDL_GetTicks() - frame_start;

		if (frame_time < DELAY_TIME ) {
			SDL_Delay(static_cast<int> (DELAY_TIME - frame_time));
		}
	}

}


int main() {

	if ( SDL_Init(SDL_INIT_EVERYTHING ) < 0 ) {
		throw std::runtime_error("SDL could not initialize. SDL_Error: " + std::string(SDL_GetError()) + "\n");
	}

	run_interface();

	SDL_Quit();

	return 0;
}

