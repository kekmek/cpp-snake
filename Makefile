all:
	g++ main.cpp Source/*.cpp -std=c++17 -IIncludes -o snake
clean:
	rm *.o snake