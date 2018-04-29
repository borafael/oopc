#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} Vector;

Vector* create_vector(float x, float y);

float get_x(Vector* v);

float get_y(Vector* v);

float norm(Vector* v);

Vector* scale(Vector* v, float s);

void destroy_vector(Vector* vector);

#endif
