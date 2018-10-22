#pragma once
#include<iostream>
using namespace std;

class Vector2D {
private:
	double x, y;
public:
	Vector2D() :x(0), y(0) {};
	Vector2D(double x, double y) :x(x), y(y) {};
	~Vector2D() {};
	double getX();
	double getY();
	Vector2D normalize();
	Vector2D operator+(const Vector2D);
	Vector2D operator-(const Vector2D);
	double operator*(const Vector2D);
	Vector2D operator*(const double);

};

ostream& operator<<(ostream&, const Vector2D);


