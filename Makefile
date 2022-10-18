ROOT:= $(PWD);
FLAGS = -Wall -Wpedantic -Werror -Wextra -g -std=c++11 -O3
HEADERS := -Iheader

#está variable contiene todos los archivos pre-compilados que necesitamos para enlazar las funciones y crear un ejecutable
OBJS := build/main.o build/matriz.o build/opermatrices.o

build : compilar
	@echo "Building project..."
	@echo "Building complete!"

clean :
	rm ./build/*.o
	rm ./build/*.exe

compilar: $(OBJS)
	g++ -o ./build/main build/*.o $(FLAGS) $(HEADERS)

build/main.o : src/main.cpp
	g++ src/main.cpp -c -o build/main.o $(FLAGS) $(HEADERS)

build/matriz.o : src/matrices/matriz.cpp header/matriz.hpp
	g++ src/matrices/matriz.cpp -c -o build/matriz.o $(FLAGS) $(HEADERS)

build/opermatrices.o : src/matrices/opermatrices.cpp header/opermatrices.hpp
	g++ src/matrices/opermatrices.cpp -c -o build/opermatrices.o $(FLAGS) $(HEADERS)
