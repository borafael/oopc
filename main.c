#include <stdio.h>
#include <unistd.h>
#include "FrameBuffer.h"
#include "GameLoop.h"
#include "KbInputHandler.h"

#define KB_INPUT 0
#define FB 1

KbInput kb_input;
Color c;

void handle_input(ServiceLocator* sl) {
	KbInputHandler* kb_input_handler = get_service(sl, KB_INPUT);
	kb_input = get_kb_input(kb_input_handler);
	printf("%d %s %s\n", kb_input.key_code, kb_input.key_name, kb_input.is_release ? "released" : "pressed");
}

void update(ServiceLocator* sl) {
	c.r = c.r + 50;
}

void render(ServiceLocator* sl) {
	FrameBuffer *fb = get_service(sl, FB);
	Pixel p;
	Color c;
	for(int x=0;x<get_h_res(fb);x++){
		for(int y=0;y<get_v_res(fb);y++){
			p.x = x;
			p.y = y;
			put_pixel(fb, p, c);
		}
	}
	sleep(0.5);
}

int should_continue(ServiceLocator* sl) {
	return kb_input.key_code != 1;
}

int main(int argc, char** argv) {
	KbInputHandler* kb_input_handler = create_kb_input_handler();
	FrameBuffer *fb = init_frame_buffer();
	capture_kb(kb_input_handler);
	ServiceLocator* sl = create_service_locator(10);
	store_service(sl, KB_INPUT, kb_input_handler);
	store_service(sl, FB, fb);
	GameLoop* gl = create_game_loop(&handle_input, &update, &render, &should_continue);
	c.r = 0;
	c.g = 0;
	c.b = 0;
	start_game_loop(gl, sl);
	destroy_game_loop(gl);
	release_kb(kb_input_handler);
	close_frame_buffer(fb);
	destroy_kb_input_handler(kb_input_handler);
	destroy_service_locator(sl);
	return 0;
}
