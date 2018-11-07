#pragma once

#include "checkML.h"
#include <iostream>

using namespace std;

class Vector2D
{
  private:
	double _x, _y;

  public:
	Vector2D();
	Vector2D(const double x, const double y);
	~Vector2D(){};
	double getX() const;
	double getY() const;
	double setX(double);
	double setY(double);
	double modulus() const;
	Vector2D normalize();
	Vector2D projectionOn(const Vector2D &v) const;
	Vector2D reflect(const Vector2D &) const;
	Vector2D operator+(const Vector2D &) const;
	Vector2D operator-(const Vector2D &) const;
	Vector2D operator-() const;
	double operator*(const Vector2D &)const;
	Vector2D operator*(const double &)const;
	Vector2D operator/(const double &) const;
	bool isIn(const Vector2D &, const Vector2D &) const;
	bool isIn(const double, const double, const double, const double) const;
	friend Vector2D operator*(const double &, const Vector2D &);
	friend ostream &operator<<(ostream &, const Vector2D &);
	static Vector2D cutPoint(const Vector2D &p1, const Vector2D &p2, const Vector2D &pp1, const Vector2D &pp2);
	static Vector2D unitary(const double angle);
	static double angleBetween(const Vector2D v1, const Vector2D v2);
};
Vector2D operator*(const double &, const Vector2D &);
ostream &operator<<(ostream &, const Vector2D &);
