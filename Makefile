ROOT:= $(PWD);
FLAGS = -Wall -Wpedantic -Werror -std=c++11 -O3

build: compilar
	@echo "Building project..."
	@echo "Building complete!"

compilar: main.o
	g++ -o ./build/main ./build/main.o $(FLAGS)

main.o :
	g++ ./src/main.cpp -c -o ./build/main.o
