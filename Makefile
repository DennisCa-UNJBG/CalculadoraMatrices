ROOT:= $(PWD);
FLAGS = -Wall -Wpedantic -Werror -Wextra -g -std=c++11 -O3
HEADERS := -Iheader

build : compilar
	@echo "Building project..."
	@echo "Building complete!"

clean :
	rm ./build/*.o
	rm ./build/*.exe

compilar: main.o matriz.o opermatrices.o
	g++ -o ./build/main ./build/*.o $(FLAGS) $(HEADERS)

main.o : ./src/main.cpp
	g++ ./src/main.cpp -c -o ./build/main.o $(FLAGS) $(HEADERS)

matriz.o : header/matriz.cpp
	g++ ./header/matriz.cpp -c -o ./build/matriz.o $(FLAGS) $(HEADERS)

opermatrices.o : header/opermatrices.cpp
	g++ ./header/opermatrices.cpp -c -o ./build/opermatrices.o $(FLAGS) $(HEADERS)
