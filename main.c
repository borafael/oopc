#include <stdio.h>
#include "FrameBuffer.h"

int main(int argc, char** argv) {
	FrameBuffer* fb = init_frame_buffer();
	
	for(int x = 0; x < get_h_res(fb); x++) {
		for(int y = 0; y < get_v_res(fb); y++) {
			Pixel p;
			p.x = x;
			p.y = y;
			Color c;
			c.r = x * 255 / get_h_res(fb);
			c.g = 0;	
			c.b = 0;
			put_pixel(fb, p, c);
		}
	}
	close_frame_buffer(fb);
	return 0;
}
