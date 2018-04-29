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

Vector* change_x(Vector* v, float x) {
	return create_vector(x, v->y);
}

Vector* change_y(Vector* v, float y) {
	return create_vector(v->x, y);
}

Vector* scale(Vector* v, float s) {
	float n = norm(v);

	if(n == 0) {
		return NULL;
	}

	return create_vector(s * (v->x / n), s * (v->y / n));
}

Vector* add(Vector* v1, Vector* v2) {
	return create_vector(v1->x + v2->x, v1->y + v2->y);
}

Vector* sub(Vector* v1, Vector* v2) {
	return create_vector(v1->x - v2->x, v1->y - v2->y);
}

Vector* mul(Vector* v, float k) {
	return create_vector(v->x * k, v->y * k);
}

void destroy_vector(Vector* v) {
	free(v);
}
