OBJECTS=main.o vector3d.o light.o triangle.o sphere.o matrix.o pigment.o ray.o screen.o
CC=g++

ep3: $(OBJECTS)
	g++ -lm -o ep3 $(OBJECTS)
	
main.o: main.cpp
vector3d.o: vector3d.cpp
light.o: light.cpp
triangle.o: triangle.cpp
sphere.o: sphere.cpp
matrix.o: matrix.cpp
pigment.o: pigment.cpp
ray.o: ray.cpp

clean:
	rm $(OBJECTS)
