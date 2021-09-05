#include "ACOppInterface.hpp"
#include "AntColony.hpp"

#include "Figures/Circle.hpp"
#include "Figures/Line.hpp"

#include "TSPReader.hpp"

#include <iostream>
#include <chrono>




const uint32_t FPS = 60;
const uint32_t DELAY_TIME = 1000.0 / FPS;

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

const uint32_t CIRCLE_RADIUS = 5;
const uint32_t LINE_WIDTH = 2;


std::vector<Point> adjust_points(const std::vector<Point> & points, const uint32_t WIDTH, const uint32_t HEIGHT) {
	const uint32_t max_x = std::max_element(points.begin(), points.end(), 
														[](const Point & p1, const Point & p2){
															return p1.x < p2.x;
														})->x;

	const uint32_t max_y = std::max_element(points.begin(), points.end(), 
														[](const Point & p1, const Point & p2){
															return p1.y < p2.y;
														})->y;
	
	double ratio_x = WIDTH / (max_x * 1.0);
	double ratio_y = HEIGHT / (max_y * 1.0);

	std::vector<Point> solution;
	solution.resize(points.size());

	for(uint32_t i = 0; i < points.size(); i++) {
		solution[i].x = points[i].x * ratio_x;
		solution[i].y = points[i].y * ratio_y;
	}
	

	return solution;

}

std::vector<std::unique_ptr<Figure> > generate_lines(const std::vector<Point> & points, const std::vector<uint32_t> & best_path) {
	std::vector<std::unique_ptr<Figure> > solution;

	for (uint32_t i = 0; i < best_path.size() - 1; i++) {
		solution.push_back(std::make_unique<Line>(points[best_path[i]].x, points[best_path[i]].y,
															 points[best_path[i + 1]].x, points[best_path[i + 1]].y, LINE_WIDTH, Color(0, 0, 200, 255)));
	}
	solution.push_back(std::make_unique<Line>(points[best_path.front()].x, points[best_path.front()].y,
															  points[best_path.back()].x, points[best_path.back()].y, LINE_WIDTH, Color(0, 0, 200, 255)));

	return solution;
}


void run_interface(int argc, char ** argv) {

	ACOppInterface interface("Prueba SDL", 900, 700, WIDTH, HEIGHT, 0);


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

	// std::pair<std::vector<uint32_t>, double> solution = my_colony.run_simulation(iterations);

	std::vector<Point> points = adjust_points(paths.second, WIDTH - 20, HEIGHT - 20);

	for (const Point & point: points) {
		std::unique_ptr<Circle> circle = std::make_unique<Circle>(point.x, point.y, CIRCLE_RADIUS, Color(0, 0, 200, 255), true);
		interface.add_city(std::move(circle));
	}

	// auto best_path = solution.first;

	int num_iterations = 0;

	std::chrono::time_point<std::chrono::system_clock> last_update = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> now;


	std::coroutine_handle<ReturnObject::promise_type> generator =  my_colony.run_step_simulation();
	ReturnObject::promise_type & promise = generator.promise();

	while ( interface.running() ) {
		uint32_t frame_start, frame_time;
		frame_start = SDL_GetTicks();

		interface.handle_events();
		interface.render();
			
		now = std::chrono::system_clock::now();

		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update);

		if ( iterations > num_iterations && milliseconds.count() > 50) {
			last_update = now;
			
			auto iteration_solution = promise.val_;

			interface.change_lines(generate_lines(points, iteration_solution.first));

			generator();

			num_iterations++;
		}


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

