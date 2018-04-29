#include "vector.h"
#include <stdio.h>

int main(int argc, char** argv) {
	Vector* v = create_vector(0.3, 0.9);
	printf("(%f, %f)\n", get_x(v), get_y(v));
	destroy_vector(v);
	return 0;
}
