#pragma once

/*
 *Updatable interface
 */
class Updatable {
public:
	Updatable() {};
	~Updatable() {};
	virtual void update() = 0;
};