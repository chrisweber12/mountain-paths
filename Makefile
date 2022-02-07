make : main.cpp functions.cpp functions.hpp
	g++ -std=c++11 -o Mountain-Paths.exe main.cpp functions.cpp
run:
	./Mountain-Paths.exe
clean :
	$(info Removing executable and all .ppm files in directory)
	rm -f Mountain-Paths.exe
	find . -name *.ppm -delete
