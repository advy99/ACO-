#include "ACOppInterface.hpp"
#include "AntColony.hpp"

#include "Figures/Circle.hpp"

#include "TSPReader.hpp"

#include <iostream>
#include <chrono>

void run_interface(int argc, char ** argv) {

	const uint32_t FPS = 60;
	const uint32_t DELAY_TIME = 1000.0 / FPS;

	ACOppInterface interface("Prueba SDL", 100, 100, 640, 480, 0);


	if ( argc < 4) {
		std::cerr << "ERROR: Incorrect number of parameters.\n"
					 << "\t Use: " << argv[0] << " <num_ants> <num_iterations> <file>\n";

		std::exit(-1);
	}
	
	Random::set_seed(std::time(nullptr));

	int num_ants = std::atoi(argv[1]);
	int iterations = std::atoi(argv[2]);
	std::string file = std::string(argv[3]);

	auto paths = TSPReader::read_from_file(file);

	AntColony my_colony(paths.first, num_ants);

	auto solution = my_colony.run_simulation(iterations);

	for (auto & point: paths.second) {
		std::unique_ptr<Circle> circle = std::make_unique<Circle>(point.x, point.y, 1, Color(0, 0, 200, 255), true);
		interface.add_object(std::move(circle));
	}

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


int main(int argc, char ** argv) {


	if ( SDL_Init(SDL_INIT_EVERYTHING ) < 0 ) {
		throw std::runtime_error("SDL could not initialize. SDL_Error: " + std::string(SDL_GetError()) + "\n");
	}

	run_interface(argc, argv);

	SDL_Quit();

	return 0;
}

