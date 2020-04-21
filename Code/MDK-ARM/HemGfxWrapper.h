#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif
	
	struct Hem;
	typedef struct Hem HemGfx_t;
	
	HemGfx_t* newHemGfx(uint8_t w, uint8_t h, uint16_t *b1, uint16_t *b2);
	void destroyHemGfx(HemGfx_t *c);
	
	void HemSetPixel(HemGfx_t* c, uint8_t x, uint8_t y, uint16_t color);
	void HemdrawImage(HemGfx_t* c, uint16_t *image, uint16_t w, uint16_t h, int16_t x, int16_t y);
	void HemClearScreen(HemGfx_t* c);
	
	void HemWave(HemGfx_t* c);
	void HemSwitchBuff(HemGfx_t* c, bool copy);
	bool *HemGetReady(HemGfx_t* c);
	
	uint16_t* HemGetBuffer(HemGfx_t* c);

#ifdef __cplusplus
}
#endif

