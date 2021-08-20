
project(
	'ACOcpp',
	'cpp',
	default_options : ['cpp_std=c++20', 'warning_level=3',
							 'optimization=2','debug=false',
							 'werror=true'],
	version : '1.0'
)

include_dir = include_directories('include')
src_files = []

src_files += ['src/main.cpp', 'src/ACOppInterface.cpp'] 

figures_src_files = ['src/Figures/Circle.cpp', 'src/Figures/Line.cpp', 'src/Figures/Figure.cpp', 
							'src/Figures/Rectangle.cpp', 'src/Figures/Color.cpp', 'src/Figures/aux.cpp']

sdl2_dep = dependency('SDL2')
sdl2_image_dep = dependency('SDL2_image')
sdl2_gfx_dep = dependency('SDL2_gfx')

figures_lib = library('figures', 
		  sources : figures_src_files, 
		  include_directories : include_dir,
		  dependencies : [sdl2_dep, sdl2_image_dep, sdl2_gfx_dep])

executable('main', 
			  sources : src_files,
			  include_directories: include_dir,
			  dependencies : [sdl2_dep, sdl2_image_dep, sdl2_gfx_dep],
			  link_with: figures_lib)

