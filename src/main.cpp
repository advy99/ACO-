#include "ACOppInterface.hpp"

int main() {

	ACOppInterface interface;

	const uint32_t FPS = 60;
	const uint32_t DELAY_TIME = 1000.0 / FPS;

	uint32_t frame_start, frame_time;

	interface.init("Prueba SDL", 100, 100, 640, 480, 0);

	while ( interface.running() ) {
		frame_start = SDL_GetTicks();

		interface.handle_events();

		frame_time = SDL_GetTicks() - frame_start;

		if (frame_time < DELAY_TIME ) {
			SDL_Delay(static_cast<int> (DELAY_TIME - frame_time));
		}
	}


	return 0;
}

