#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

typedef struct {
	int fbfd;
	char* fbp;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize;
} FrameBuffer;

typedef struct {
	int x;
	int y;
} Pixel;

typedef struct {
	int r;
	int g;
	int b;
} Color;

FrameBuffer* init_frame_buffer();

int get_h_res(FrameBuffer* fb);

int get_v_res(FrameBuffer* fb);

void put_pixel(FrameBuffer* fb, Pixel p, Color c);

void close_frame_buffer(FrameBuffer* fb); 

#endif
