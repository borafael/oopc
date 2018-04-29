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

float norm(Vector* v) {
	return sqrt(v->x * v->x + v->y * v->y);
}

Vector* scale(Vector* v, float s) {
	float n = norm(v);

	if(n == 0) {
		return NULL;
	}

	return create_vector(s * (v->x / n), s * (v->y / n));
}

void destroy_vector(Vector* v) {
	free(v);
}
