#include <stdint.h>

class HemGfx
{
	private:
		uint16_t *buff_ptr[2];
		uint8_t buff_w;
		uint8_t buff_h;
		bool buff_cur;
		uint32_t t_step;
		uint16_t N_func;
	
	public:
		bool ready;
		bool *getReady();
	
		HemGfx(uint8_t w, uint8_t h, uint16_t *b1, uint16_t *b2);
		
		void setPixel(uint8_t x, uint8_t y, uint16_t color);
		void drawImage(uint16_t *image, uint16_t w, uint16_t h, int16_t x, int16_t y);
		void clearScreen();
	
		void Wave();
		void PerlinNoise();
		void switchBuff(bool copy);
		void copy();
	
		uint16_t* getBuffer();
};

