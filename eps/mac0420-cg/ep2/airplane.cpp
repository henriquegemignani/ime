#include "airplane.h"
#include "vector3d.h"
#include <GL/glut.h>
#include <cmath>
#include <cstdio>

#define TO_RADIAN 0.0174532925f

 // Rotacao de um vetor em 3D usando matriz de euler
static Vector3D rotateTo(Vector3D v, Vector3D angles) {
	float 	alpha = angles.z * TO_RADIAN,
			beta = angles.x * TO_RADIAN,
			gama = angles.y * TO_RADIAN;

	float x, y, z;
	x = v.x * cos(beta) * cos(gama) +
		v.y * (cos(gama) * sin(alpha) * sin(beta) - cos(alpha) * sin(gama)) +
		v.z * (cos(alpha) * cos(gama) * sin(beta) + sin(alpha) * sin(gama));
		
	y = v.x * cos(beta) * sin(gama) +
		v.y * (cos(alpha) * cos(gama) + sin(alpha) * sin(beta) * sin(gama)) +
		v.z * (- cos(gama) * sin(alpha) + cos(alpha) * sin(beta) * sin(gama));
		
	z = v.x * (-sin(beta)) +
		v.y * (cos(beta) * sin(alpha)) +
		v.z * (cos(alpha) * cos(beta));
		
	return Vector3D(x, y, z);
}

// Rotacao de um vetor em 3D usando matriz de euler invertida
static Vector3D rotateFrom(Vector3D v, Vector3D angles) {
	float 	alpha = angles.x * TO_RADIAN,
			beta = angles.y * TO_RADIAN,
			gama = angles.z * TO_RADIAN;

	float x, y, z;
	x = v.x * (cos(beta) * cos(gama)) +
		v.y * (cos(beta) * sin(gama)) +
		v.z * (- sin(beta));
		
	y = v.x * (cos(gama) * sin(alpha) * sin(beta) - cos(alpha) * sin(gama)) +
		v.y * (cos(alpha) * cos(gama) + sin(alpha) * sin(beta) * sin(gama)) +
		v.z * (cos(beta) * sin(alpha));
		
	z = v.x * (cos(alpha) * cos(gama) * sin(beta) + sin(alpha) * sin(gama)) +
		v.y * (cos(alpha) * sin(beta) * sin(gama) - cos(gama) * sin(alpha)) +
		v.z * (cos(alpha) * cos(beta));
		
	return Vector3D(x, y, z);
}

// Inicializa novo objeto do tipo aviao com posicao, velocidade e rotacao iniciais
Airplane::Airplane(Vector3D pos, Vector3D rot, float vel) {
	position = pos;
	rotation = rot;
	velocity = vel;
}

Airplane::~Airplane() {
}

// Atualiza a camera de acordo com a posicao do aviao e seu sistema de coordenadas	
void Airplane::Camera(int viewmode) {
	Vector3D origin = position + rotateFrom(Vector3D(0.0f, 0.5f, 1.0f), rotation) * (viewmode * 10.0f),
			 target = position + rotateFrom(Vector3D(0.0f, 0.0f,-1.0f), rotation),
			 angle  = 			rotateFrom(Vector3D(0.0f, 1.0f, 0.0f), rotation);
	gluLookAt( origin.x, origin.y, origin.z, 
			   target.x, target.y, target.z,
			   angle.x, angle.y, angle.z );
}

#define HEIGHT 3.1415f // por que pi é legal
#define WIDTH 3.6274f

// Desenha um aviao de acordo com seu proprio frame de coordenadas
void Airplane::Render() {
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(-rotation.x, 1.0, 0.0f, 0.0f);
	glRotatef(-rotation.y, 0.0, 1.0f, 0.0f);
	glRotatef(-rotation.z, 0.0, 0.0f, 1.0f);

	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(  0.0f,          0.0f,-HEIGHT); // frente
		glVertex3f(-WIDTH,          0.0f, HEIGHT * 1.5f); // baixo esquerda
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(  0.0f, HEIGHT * 0.75f, HEIGHT * 0.5f); // topo
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f( WIDTH,          0.0f, HEIGHT * 1.5f); // baixo direita
		glVertex3f(  0.0f,          0.0f,-HEIGHT); // frente
		glVertex3f(-WIDTH,          0.0f, HEIGHT * 1.5f); // baixo esquerda
	glEnd();
	glPopMatrix();
}

// Atualiza rotacao e posicao do aviao
void Airplane::Update() {
	rotation = rotation + rotvel;
	Vector3D result = rotateFrom(Vector3D(0, 0, -1), rotation);
	position = position + result * velocity;
}

// Atualiza a rotacao do aviao
void Airplane::UpdateRot(Vector3D add) {
	rotation = rotation + add;
}

// Atualiza velocidade de yaw, pitch e roll
void Airplane::UpdateRotVelocity(Vector3D add) {
	rotvel = rotvel + add;
}

void Airplane::StopRotVelocity() {
	rotvel = Vector3D();
}

void Airplane::UpdateVelocity(float vel) {
	velocity += vel;
}

// Funcao para debug
void Airplane::Dump() {
	printf("Pos (%f,%f,%f) - Rot (%f,%f,%f)\n", 
		position.x, position.y, position.z,
		rotation.x, rotation.y, rotation.z);
}
