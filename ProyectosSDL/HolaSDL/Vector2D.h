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
	double getX() const;
	double getY() const;
	double modulus() const;
	Vector2D normalize();
	Vector2D projectionOn(Vector2D v) const;
	Vector2D reflect(Vector2D) const;
	Vector2D operator+(const Vector2D) const;
	Vector2D operator-(const Vector2D) const;
	Vector2D operator-() const;
	double operator*(const Vector2D) const;
	Vector2D operator*(const double) const;
	Vector2D operator/(const double) const;
	friend Vector2D operator*(const double, const Vector2D);
	friend ostream& operator<<(ostream&, const Vector2D);

};

Vector2D operator*(const double, const Vector2D);
ostream& operator<<(ostream&, const Vector2D);


