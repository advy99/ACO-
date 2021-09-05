#ifndef ACOPPINTERFACE_HPP
#define ACOPPINTERFACE_HPP

#include "aux.hpp"

#include "Figures/Figure.hpp"


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

		std::vector<std::unique_ptr<Figure> > cities_;
		std::vector<std::unique_ptr<Figure> > lines_;

		std::unique_ptr<Figure> background_;
	
	public:

		ACOppInterface(const std::string & title, const uint32_t X_POS, const uint32_t Y_POS,
							const uint32_t WIDTH, const uint32_t HEIGHT, const int32_t FLAGS);

		ACOppInterface(const ACOppInterface & other) = delete;

		~ACOppInterface() = default;

		void render();

		void draw();

		void update();

		void handle_events();

		void clear_cities();

		void clear_lines();

		bool running() const;

		void quit();

		uint32_t width();
		uint32_t height();

		std::shared_ptr<SDL_Renderer> renderer() const;
	
		void add_city(std::unique_ptr<Figure> && object);

		void add_line(std::unique_ptr<Figure> && object);

		void change_lines(std::vector<std::unique_ptr<Figure> > && new_lines);

		ACOppInterface & operator = (const ACOppInterface & other) = delete;
		
};


#endif
