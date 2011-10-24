/* * * * * * * * * * * * * * * * * * * * * * * * * 
 * EP3 - Ray Tracing                             *
 *                                               *
 * Henrique Geminiani Passos - NUSP: 6879634     * 
 * Luciana dos Santos Kayo - NUSP: 6430992       * 
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */ 

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "common.h"
#include "vector3d.h"
#include "light.h"
#include "object.h"
#include "sphere.h"
#include "triangle.h"
#include "screen.h"
#include "pigment.h"
#include "surface.h"
#include "ray.h"

static Vector3D eye, center, up;
static double fovy;
static std::vector<Light*> lights;
static std::vector<Object*> objects;
static Light* ambient_light;

void readinput(std::ifstream &input) {
	std::vector<Pigment*> pigments;
	std::vector<Surface*> surfaces;

	int num;
	input >> eye >> center >> up >> fovy;
	if(DEBUG) std::cout << "Eye: " << eye << "\nCenter: " << center << "\nUp: " << up << "\nFOVY: " << fovy << std::endl;
	
	if(DEBUG) std::cout << std::endl;
	input >> num;
	for(int i = 0; i < num; i++) {
		Vector3D pos, color, abc;
		input >> pos >> color >> abc;
		if(i == 0)
			ambient_light = new Light(pos, color, abc);
		else
			lights.push_back(new Light(pos, color, abc));
		if(DEBUG) std::cout << "Light " << i << ": " << pos << color << abc << std::endl;
	}
	
	if(DEBUG) std::cout << std::endl;
	input >> num;
	for(int i = 0; i < num; i++) {
		char buffer[64];
		input >> buffer;
		if(strncmp(buffer, "SOLI", 4) == 0) {
			Vector3D color;
			input >> color;
			pigments.push_back(new Pigment(color));
			if(DEBUG) std::cout << "Pigmento " << i << ": SOLID " << color << std::endl;
		} else {
			Vector3D color1, color2;
			double s;
			input >> color1 >> color2 >> s;
			pigments.push_back(new Pigment(color1, color2, s));
			if(DEBUG) std::cout << "Pigmento " << i << ": QUAD " << color1 << color2 << " size "<< s << std::endl;
		}

	}
	
	if(DEBUG) std::cout << std::endl;
	input >> num;
	for(int i = 0; i < num; i++) {
		Surface *s = new Surface;
		input >> *s;
		surfaces.push_back(s);
		if(DEBUG) std::cout << "Acabamento " << i << " = " << *s << std::endl;
	}
	
	if(DEBUG) std::cout << std::endl;
	input >> num;
	for(int i = 0; i < num; i++) {
		int pig, surf;
		char buffer[64];
		input >> pig >> surf >> buffer;
		if(DEBUG) std::cout << "Objeto " << i << " [" << buffer << "] Pig: " << pig << ", ACA: " << surf;
		if(strncmp(buffer, "ESFE", 4) == 0) {
			Vector3D aux;
			double r;
			input >> aux >> r;
			objects.push_back(new Sphere(pigments[pig], surfaces[surf], aux, r));
			if(DEBUG) std::cout << ", Origem: " << aux << ", R: " << r << std::endl;
		} else {
			Vector3D aux[3];
			input >> aux[0] >> aux[1] >> aux[2];
			objects.push_back(new Triangle(pigments[pig], surfaces[surf], aux));
			if(DEBUG) std::cout << ", V: " << aux[0] << aux[1] << aux[2] << std::endl;

		}
	}
}

int main(int argc, char *argv[]) {
	if(argc < 5) {
		fprintf(stderr, "Falta parametros!\n");
		exit(1);
	}
	std::ifstream input(argv[1]);
	if(!input.is_open()) {
		fprintf(stderr, "Erro ao abrir arquivo de entrada %s\n", argv[1]);
		exit(2);
	}
	FILE *output = fopen(argv[2], "wb");
	if(output == NULL) {
		fprintf(stderr, "Erro ao abrir arquivo de saida %s\n", argv[2]);
		exit(2);
	}
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	if(argc >= 6 && strcmp(argv[5], "-d") == 0) {
		std::cout << "MODO DEBUG!" << std::endl;
		Debug::debug(true);
	}
	// Pronto! Leu tudo! Bora pro programa.
	readinput(input);

	if(DEBUG) std::cout << "\n\n";

	Screen *screen = new Screen(width, height, fovy);
	screen->CalculatePosition(eye, center, up);

	Environment env;
	env.ambient_light = ambient_light;
	env.lights = lights;
	env.objects = objects;

	if(DEBUG) std::cout << "\n\n";
	int w = width;
	for(int h = 0; h < height; ++h)
		for(w -= width; w < width; ++w) {
			if(DEBUG) std::cout << "Raio (" << w << ", " << h << "): ";

			Vector3D pixelpos = screen->GetPixelPosition(w, h);
			Vector3D direction = (pixelpos - eye);

			Ray r(eye, direction.Normalize());
			//screen->SetColor(w, h, raytrace(eye, (pixelpos - eye).Normalize(), 0));
			screen->SetColor(w, h, r.Trace(env));
			if(DEBUG) {
				int skip;
				if(std::cin >> skip)
					w += skip;
			}
		}

	screen->WriteToFile(output);
	fclose(output);
	return 0;
}
