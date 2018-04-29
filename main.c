#include "vector.h"
#include <stdio.h>

void print(Vector* v) {
	printf("x=(%f, %f)\n", get_x(v), get_y(v));
	printf("|x|=%f\n", norm(v));
}


int main(int argc, char** argv) {
	Vector* v = create_vector(3, 4);
	print(v);
	Vector* v2 = scale(v, 1);
	print(v2);
	destroy_vector(v);
	destroy_vector(v2);
	return 0;
}
