#include <stdio.h>
#include "FrameBuffer.h"

int main(int argc, char** argv) {
	FrameBuffer* fb = init_frame_buffer();
	
	for(int x = 0; x < 400; x++) {
		for(int y = 0; y < 400; y++) {
			Pixel p;
			p.x = x;
			p.y = y;
			Color c;
			c.r = x * y;
			c.g = 0;	
			c.b = 0;
			put_pixel(fb, p, c);
		}
	}
	close_frame_buffer(fb);
	return 0;
}
