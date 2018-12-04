#include "Award.h"

class StickyAward : public Award {
public:
    StickyAward();
	StickyAward(float32 x, float32 y, float32 width, float32 height, float32 framerate, Texture *texture);
	virtual void contact();
};