#include "FrameBuffer.h" 

FrameBuffer* init_frame_buffer() {
	FrameBuffer* fb = (FrameBuffer*)malloc(sizeof(FrameBuffer));

	// Open the file for reading and writing
	fb->fbfd = open("/dev/fb0", O_RDWR);

	if (fb->fbfd == -1) {
		perror("Error: cannot open framebuffer device");
		exit(1);
	}

	printf("The framebuffer device was opened successfully.\n");

	// Get fixed screen information
	if (ioctl(fb->fbfd, FBIOGET_FSCREENINFO, &fb->finfo) == -1) {
		perror("Error reading fixed information");
		exit(2);
	}

	// Get variable screen information
	if (ioctl(fb->fbfd, FBIOGET_VSCREENINFO, &fb->vinfo) == -1) {
		perror("Error reading variable information");
		exit(3);
	}

	printf("%dx%d, %dbpp\n", fb->vinfo.xres, fb->vinfo.yres, fb->vinfo.bits_per_pixel);

	// Figure out the size of the screen in bytes
	fb->screensize = fb->vinfo.xres * fb->vinfo.yres * fb->vinfo.bits_per_pixel / 8;

	// Map the device to memory
	fb->fbp = (char *)mmap(0, fb->screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb->fbfd, 0);

	if ((int)fb->fbp == -1) {
		perror("Error: failed to map framebuffer device to memory");
		exit(4);
	}

	printf("The framebuffer device was mapped to memory successfully.\n");
	return fb;
}

void put_pixel(FrameBuffer* fb, Pixel p, Color c) {

	if(p.x > 0 && p.x < fb->vinfo.xres && p.y > 0 && p.y < fb->vinfo.yres) {
		// Figure out where in memory to put the pixel
		long int location = (p.x+fb->vinfo.xoffset) * (fb->vinfo.bits_per_pixel/8) + (p.y+fb->vinfo.yoffset) * fb->finfo.line_length;
		
		if (fb->vinfo.bits_per_pixel == 32) {
			*(fb->fbp + location) = c.b;
			*(fb->fbp + location + 1) = c.g;
			*(fb->fbp + location + 2) = c.r;
			*(fb->fbp + location + 3) = 0;      // No transparency
		} else  { //assume 16bpp
			unsigned short int t = c.r<<11 | c.g << 5 | c.b;
			*((unsigned short int*)(fb->fbp + location)) = t;
		}
	}
}

void close_frame_buffer(FrameBuffer* fb) { 
    munmap(fb->fbp, fb->screensize);
    close(fb->fbfd);
}
