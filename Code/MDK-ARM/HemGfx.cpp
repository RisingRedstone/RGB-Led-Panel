#include <stdint.h>
#include <stdlib.h>
#include "HemGfx.h"
#include "../Src/Bitmaps.c"

double f_sine(double x){
	const double pi = 3.1415926535897;
	const double A = 2/pi;
	const double B = 2/(pi * pi);
	
	if(x > pi){
		x -= double(2 * pi * int(x / (2 * pi)));
	}else if(x < -pi){
		x += double(2 * pi * int(x / (2 * pi)));
	}
	
	x -= pi;
	
	return (0.5 + (A * x) - (B * x * ((x < 0) ? -x : x)));
}

HemGfx::HemGfx(uint8_t w, uint8_t h, uint16_t *b1, uint16_t *b2){
	buff_cur = 0;
	t_step = 0;
	ready = true;
	
	buff_w = w;
	buff_h = h;
	buff_ptr[0] = b1;
	buff_ptr[1] = b2;
	
	clearScreen();
	buff_cur = !buff_cur;
	clearScreen();
	buff_cur = !buff_cur;
}

void HemGfx::setPixel(uint8_t x, uint8_t y, uint16_t color){
	buff_ptr[buff_cur][((y * buff_w) + x)] = color;
}

void HemGfx::clearScreen(){
	uint8_t x0 = 0;
	uint8_t y0 = 0;
	
	for(y0 = 0; y0 < buff_h; y0++){
		for(x0 = 0; x0 < buff_w; x0++){
			setPixel(x0, y0, 0x0000);
		}
	}
}

bool *HemGfx::getReady(){
	return &ready;
}

void HemGfx::switchBuff(bool copy){
	
	buff_cur = !buff_cur;
	uint8_t x0 = 0;
	uint8_t y0 = 0;
	if(copy){
		for(y0 = 0; y0 < buff_h; y0++){
			for(x0 = 0; x0 < buff_w; x0++){
				setPixel(x0, y0, buff_ptr[!buff_cur][(x0 + y0 * buff_h)]);
			}
		}
	}
}



void HemGfx::Wave(){
	N_func = 0x0001;
	
	uint16_t *valR = (uint16_t *)malloc(buff_w * sizeof(uint16_t));
	uint16_t *valG = (uint16_t *)malloc(buff_w * sizeof(uint16_t));
	uint16_t *valB = (uint16_t *)malloc(buff_w * sizeof(uint16_t));
	
	uint8_t temp0 = 0;
	for(temp0 = 0; temp0 < buff_w; temp0 ++){
		valR[temp0] = uint16_t(14 * f_sine((double(temp0) / 2) + (0.5 * double(t_step))));
		valG[temp0] = uint16_t(14 * f_sine((double(temp0) / 3) + (0.3 * double(t_step))));
		valB[temp0] = uint16_t(14 * f_sine((double(temp0) / 4) + (0.2 * double(t_step))));
	}
	
	uint8_t x0;
	uint8_t y0;
	for(y0 = 0; y0 < buff_h; y0++){
		for(x0 = 0; x0 < buff_w; x0++){
			setPixel(x0, y0, (((valR[x0] << 8) + (valG[x0] << 4) + valB[x0])) + 0x0001 + 0x0010 + 0x0100);
		}
	}
	
	free(valR);
	free(valG);
	free(valB);
	t_step++;
}

void HemGfx::drawImage(uint16_t *image, uint16_t w, uint16_t h, int16_t x, int16_t y){
	int16_t y0;
	int16_t x0;
	for(y0 = y; y0 < (h + y); y0++){
		if(y0 < buff_h && y0 >= 0){
			for(x0 = x; x0 < (w + x); x0++){
				if(x0 < buff_w && x0 >= 0){
					setPixel(x0, y0, image[((y0 - y) * w + (x0 - x))]);
				}
			}
		}
	}
}

void HemGfx::PerlinNoise(){
	
}

uint16_t* HemGfx::getBuffer(){
	return (uint16_t *)buff_ptr[!buff_cur];
	//return (uint16_t *)mario1;
}

