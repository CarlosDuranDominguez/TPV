#include "Award.h"

class NextLevelAward : public Award {
public:
	NextLevelAward(float32 x, float32 y, float32 width, float32 height, float32 framerate, Texture *texture);
	virtual void contact();
};