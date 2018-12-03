#include "Timer.h"
#include <math.h>
#include "State.h"

/**
 * Constructors.
 */
Timer::Timer(float x, float y, int width, int height, SDL_Color color, Font *font)
	:Text(font, x, y, width, height, color, "HOLA"){
	time = State::current->getTime();
};


/**
 * It updates the current time.
 */
void Timer::update()
{
	if (time != State::current->getTime()) {
		time = State::current->getTime();
		setText(to_string(time));
	}
	
}

std::istream& Timer::deserialize(std::istream& out) {
	return out;
}
std::ostream& Timer::serialize(std::ostream& is) const {
	return is;
}
