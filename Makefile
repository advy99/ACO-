# variables
CXX      := g++
HOME     := .
BIN      = $(HOME)/bin
INC	   = $(HOME)/include
SRC      = $(HOME)/src
OBJ      = $(HOME)/obj

# flags de compilacion por defecto
MENSAJE := "Compilando\ usando\ C++20,\ sin\ optimización\ de\ máximo\ nivel\ y\ con\ todos\ los\ warnings\ activados"
OPTIMIZACION ?= 2

ifeq ($(DEBUG), 1)
# target para debug (cambiamos flags y el mensaje)
OPTIMIZACION = g -g
OPENMP = 0
MENSAJE = "Compilando\ usando\ C++20,\ con\ optimización,\ con\ todos\ los\ warnings\ activados\ y\ con\ símbolos\ de\ depuración"
endif


O_LEVEL := -O$(strip $(OPTIMIZACION))

CXXFLAGS = -std=c++20 $(O_LEVEL) $(F_OPENMP) $(F_GPROF) -Wall -Wextra -Wfloat-equal -Wpedantic

SDL_LINK = -lSDL2 -lSDL2_image -lSDL2_gfx

# objetivo principal
OBJETIVO = $(BIN)/main
OBJETOS = $(OBJ)/main.o $(OBJ)/ACOppInterface.o $(OBJ)/Color.o $(OBJ)/Rectangle.o \
			 $(OBJ)/Figure.o $(OBJ)/Circle.o $(OBJ)/Line.o


# variables para el contador de reglas
N := $(shell echo $(OBJETIVO) $(OBJETOS) | wc -w )
X := 0
SUMA = $(eval X=$(shell echo $$(($(X)+1))))


# targets
.PHONY: all crear-carpetas debug INICIO FIN mrproper help

# target por defecto
all: crear-carpetas INICIO $(OBJETIVO) FIN


# funcion para compilar un objeto
define compilar_objeto
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el objeto $(2) a partir de $(1)\n"
	@$(CXX) -c $(CXXFLAGS) $(3) $(1) -I$(INC) -I. -o $(2)
endef


# mensaje de inicio y compilacion del objetivo y objeros

INICIO:
	@printf "\n\e[36mComenzando compilación de $(OBJETIVO)\n\n"
	@printf "\e[94mCompilador: $(CXX)\n"
	@printf "\e[94mFlags del compilador: $(CXXFLAGS)\n\n"
	@printf "\e[94m$(MENSAJE)\n\n"

$(OBJETIVO): $(OBJETOS) 
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el binario $(OBJETIVO) a partir de $(OBJETOS)\n"
	@$(CXX) $(OBJETOS) $(CXXFLAGS) $(SDL_LINK) -o $@ -I$(INC) 
	@printf "\n\e[36mCompilación de $(OBJETIVO) finalizada con exito.\n\n"


$(OBJ)/ACOppInterface.o: $(SRC)/ACOppInterface.cpp $(INC)/ACOppInterface.hpp
	$(call compilar_objeto,$<,$@, $(SDL_LINK))

$(OBJ)/Color.o: $(SRC)/Color.cpp $(INC)/Color.hpp
	$(call compilar_objeto,$<,$@, $(SDL_LINK))

$(OBJ)/Rectangle.o: $(SRC)/Rectangle.cpp $(INC)/Rectangle.hpp
	$(call compilar_objeto,$<,$@, $(SDL_LINK))

$(OBJ)/Circle.o: $(SRC)/Circle.cpp $(INC)/Circle.hpp
	$(call compilar_objeto,$<,$@, $(SDL_LINK))

$(OBJ)/Figure.o: $(SRC)/Figure.cpp $(INC)/Figure.hpp
	$(call compilar_objeto,$<,$@, $(SDL_LINK))

$(OBJ)/Line.o: $(SRC)/Line.cpp $(INC)/Line.hpp
	$(call compilar_objeto,$<,$@, $(SDL_LINK))

$(OBJ)/main.o: $(SRC)/main.cpp 
	$(call compilar_objeto,$<,$@, $(SDL_LINK))


# mensaje de fin
FIN:
	@printf "\n\e[36mCompilación finalizada con éxito\n"

# targets de limpieza
clean:
	@printf "\e[36mLimpiando el directorio $(OBJ)\n"
	-@rm $(OBJ)/*.o 2> /dev/null || printf "\t\e[33mEl directorio $(OBJ) está vacio, nada que limpiar\n"
	@printf "\e[36mLimpiando el directorio $(BIN)\n"
	-@rm $(BIN)/* 2> /dev/null || printf "\t\e[33mEl directorio $(BIN) está vacio, nada que limpiar\n"
	@printf "\e[36mLimpieza completada\n"

mrproper: clean clean-doc

# target para crear las carpetas necesarias
crear-carpetas:
	@printf "\e[36mCreando carpetas necesarias\e[0m\n"
	-@mkdir $(OBJ) 2> /dev/null || printf "\t\e[33mYa existe la carpeta $(OBJ)\n"
	-@mkdir $(BIN) 2> /dev/null || printf "\t\e[33mYa existe la carpeta $(BIN)\n"

