#include "HemGfxWrapper.h"
#include "HemGfx.h"
#include <stdlib.h>

extern "C"{
	struct Hem{
		void *obj;
	};
	
	HemGfx_t* newHemGfx(uint8_t w, uint8_t h, uint16_t *b1, uint16_t *b2){
		HemGfx_t *H;
		HemGfx *object;
		
		H = (HemGfx_t *)malloc(sizeof(*H));
		object = new HemGfx(w, h, b1, b2);
		H->obj = object;
		
		return H;
	}
	
	void destroyHemGfx(HemGfx_t *c){
		if(c == NULL)
			return;
		delete static_cast<HemGfx *>(c->obj);
		free(c);
	}
	
	void HemSetPixel(HemGfx_t* c, uint8_t x, uint8_t y, uint16_t color){
		HemGfx *object;
		
		if(c == NULL)
			return;
		
		object = static_cast<HemGfx *>(c->obj);
		object->setPixel(x, y, color);
	}
	
	void HemdrawImage(HemGfx_t* c, uint16_t *image, uint16_t w, uint16_t h, int16_t x, int16_t y){
		HemGfx *object;
		
		if(c == NULL)
			return;
		
		object = static_cast<HemGfx *>(c->obj);
		object->drawImage(image, w, h, x, y);
	}
	
	void HemClearScreen(HemGfx_t* c){
		HemGfx *object;
		
		if(c == NULL)
			return;
		
		object = static_cast<HemGfx *>(c->obj);
		object->clearScreen();
	}
	
	void HemWave(HemGfx_t* c){
		HemGfx *object;
		
		if(c == NULL)
			return;
		
		object = static_cast<HemGfx *>(c->obj);
		object->Wave();
	}
	
	void HemSwitchBuff(HemGfx_t* c, bool copy){
		HemGfx *object;
		
		if(c == NULL)
			return;
		
		object = static_cast<HemGfx *>(c->obj);
		object->switchBuff(copy);
	}
	
	bool *HemGetReady(HemGfx_t* c){
		HemGfx *object;
		
		if(c == NULL)
			return 0 ;
		
		object = static_cast<HemGfx *>(c->obj);
		return object->getReady();
	}
	
	uint16_t* HemGetBuffer(HemGfx_t* c){
		HemGfx *object;
		
		if(c == NULL)
			return 0;
		
		object = static_cast<HemGfx *>(c->obj);
		return object->getBuffer();
	}
}

