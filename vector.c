#include "vector.h"

Vector* create_vector(float x, float y) {
	Vector* v = (Vector*)malloc(sizeof(Vector));
	v->x = x;
	v->y = y;
	return v;
}

float get_x(Vector* v) {
	return v->x;
}

float get_y(Vector* v) {
	return v->y;
}

void destroy_vector(Vector* v) {
	free(v);
}
