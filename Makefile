ROOT:= $(PWD);
FLAGS = -Wall -Wpedantic -Werror -Wextra -g -std=c++11 -O3
HEADERS := -Iheader

#está variable contiene todos los archivos pre-compilados que necesitamos para enlazar las funciones y crear un ejecutable
OBJS := build/main.o build/matriz.o build/opermatrices.o

# agregando librerias
LIB := -Llibrary

# agregando flags adicionales para raylib
#FLAGSRAYLIB := -lraylib -lgdi32 -luser32 -lkernel32 -lopengl32 -lwinmm
FLAGSRAYLIB := -lraylib -lopengl32 -lgdi32 -lwinmm
# https://stackoverflow.com/questions/73600045/problem-compiling-raylib-program-in-code-blocks
# https://github.com/raysan5/raylib/discussions/2492

build : compilar
	@echo "Building project..."
	@echo "Building complete!"

clean :
	rm ./build/*.o
	rm ./build/*.exe

compilar: $(OBJS)
	g++ -o ./build/main build/*.o $(FLAGS) $(HEADERS) $(LIB) $(FLAGSRAYLIB)

build/main.o : src/main.cpp
	g++ src/main.cpp -c -o build/main.o $(FLAGS) $(HEADERS)

build/matriz.o : src/matriz.cpp header/matriz.hpp
	g++ src/matriz.cpp -c -o build/matriz.o $(FLAGS) $(HEADERS)

build/opermatrices.o : src/opermatrices.cpp header/opermatrices.hpp
	g++ src/opermatrices.cpp -c -o build/opermatrices.o $(FLAGS) $(HEADERS)
