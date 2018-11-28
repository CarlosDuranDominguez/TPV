#include "GameObject.h"

std::istream& operator>>(std::istream& out, GameObject& object) {
	return object.deserialize(out);
}

std::ostream& operator<<(std::ostream& in, const GameObject& object) {
	return object.serialize(in);
}

std::istream& operator>>(std::istream& out, GAME_OBJECTS& object) {
	string str;
	out >> str;
	int i = 0;
	while (i < GAME_OBJECT_COUNT) {
		if (GAME_OBJECT_NAMES[i].compare(str)) {
			object = (GAME_OBJECTS)i;
			break;
		}
		i++;
	}
	if (i == GAME_OBJECT_COUNT)
		throw "Unrecognized object";
	return out;
}