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
	double modulus();
	Vector2D normalize();
	Vector2D projectionOn(Vector2D v);
	Vector2D reflect(Vector2D);
	Vector2D operator+(const Vector2D);
	Vector2D operator-(const Vector2D);
	Vector2D operator-();
	double operator*(const Vector2D);
	Vector2D operator*(const double);
	Vector2D operator/(const double);
	friend Vector2D operator*(const double, const Vector2D);
	friend ostream& operator<<(ostream&, const Vector2D);

};

Vector2D operator*(const double, const Vector2D);
ostream& operator<<(ostream&, const Vector2D);


