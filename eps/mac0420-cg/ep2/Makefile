ep2: main.o island.o ocean.o airplane.o vector3d.o
	g++ main.o island.o ocean.o airplane.o vector3d.o -lfreeglut -lGLU32 -lopenGL32 -lm -o ep2
	
main.o: main.cpp
	g++ -c -o main.o main.cpp

island.o: island.cpp
	g++ -c -o island.o island.cpp
	
ocean.o: ocean.cpp
	g++ -c -o ocean.o ocean.cpp
	
airplane.o: airplane.cpp
	g++ -c -o airplane.o airplane.cpp
	
vector3d.o: vector3d.cpp
	g++ -c -o vector3d.o vector3d.cpp

clean:
	rm main.o island.o ocean.o airplane.o vector3d.o
