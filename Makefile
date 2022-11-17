ROOT:= $(PWD);
FLAGS = -Wall -Wpedantic -Werror -Wextra -g -std=c++11 -O3
HEADERS := -Iheader

#está variable contiene todos los archivos pre-compilados que necesitamos para enlazar las funciones y crear un ejecutable
OBJS := build/main.o build/matriz_base.o build/matrices.o build/opermatrices.o build/lineales.o build/operlineales.o build/nolineales.o build/opernolineales.o

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

build/matriz_base.o : src/matrizBase/matriz_base.cpp header/matriz_base.hpp
	g++ src/matrizBase/matriz_base.cpp -c -o build/matriz_base.o $(FLAGS) $(HEADERS)

build/matrices.o : src/matrices/matrices.cpp header/matrices.hpp
	g++ src/matrices/matrices.cpp -c -o build/matrices.o $(FLAGS) $(HEADERS)

build/opermatrices.o : src/matrices/opermatrices.cpp header/opermatrices.hpp
	g++ src/matrices/opermatrices.cpp -c -o build/opermatrices.o $(FLAGS) $(HEADERS)

build/lineales.o : src/lineales/lineales.cpp header/lineales.hpp
	g++ src/lineales/lineales.cpp -c -o build/lineales.o $(FLAGS) $(HEADERS)

build/operlineales.o : src/lineales/operlineales.cpp header/operlineales.hpp
	g++ src/lineales/operlineales.cpp -c -o build/operlineales.o $(FLAGS) $(HEADERS)

build/nolineales.o : src/noLineales/nolineales.cpp header/nolineales.hpp
	g++ src/noLineales/nolineales.cpp -c -o build/nolineales.o $(FLAGS) $(HEADERS)

build/opernolineales.o : src/noLineales/opernolineales.cpp header/opernolineales.hpp
	g++ src/noLineales/opernolineales.cpp -c -o build/opernolineales.o $(FLAGS) $(HEADERS)
