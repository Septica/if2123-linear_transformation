#ifndef MAIN_H
#define MAIN_H

#include "include/glew.h"

enum VAO_IDs
{
	Polygon,
	Axes,
	NumVAOs
};
enum Buffer_IDs
{
	PolygonVertices,
	AxesVertices,
	NumBuffers
};
enum Attrib_IDs
{
	vPosition = 0
};

struct Vertex {
	GLint x, y, z;
};

int main(int argc, char *argv[]);
void initialize();
void display();
void finalize();

#endif