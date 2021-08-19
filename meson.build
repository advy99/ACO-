
project(
	'ACOcpp',
	'cpp',
	default_options : ['cpp_std=c++20', 'warning_level=3',
							 'optimization=2','debug=true'],
	version : '1.0'
)

include_dir = include_directories('include')
src_files = []

src_files += ['src/main.cpp', 'src/ACOppInterface.cpp', 'src/aux.cpp', 
				  'src/Circle.cpp', 'src/Line.cpp', 'src/Figure.cpp', 
				  'src/Rectangle.cpp', 'src/Color.cpp']

sdl2_dep = dependency('SDL2')
sdl2_image_dep = dependency('SDL2_image')
sdl2_gfx_dep = dependency('SDL2_gfx')

executable('main', 
			  sources : src_files,
			  include_directories: include_dir,
			  dependencies : [sdl2_dep, sdl2_image_dep, sdl2_gfx_dep])

