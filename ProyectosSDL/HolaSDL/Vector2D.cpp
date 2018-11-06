#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D() : _x(0), _y(0) {};

Vector2D::Vector2D(const double x, const double y) : _x(x), _y(y) {};

/*
 * Get the X component of the Vector
 */
double Vector2D::getX() const
{
	return _x;
}

/*
 * Get the Y component of the Vector
 */
double Vector2D::getY() const
{
	return _y;
}

/*
 * Get the X component of the Vector
 */
double Vector2D::setX(double _x)
{
	return _x = _x;
}

/*
 * Get the Y component of the Vector
 */
double Vector2D::setY(double _y)
{
	return _y = _y;
}

/*
 * Calculate modulus of the Vector
 */
double Vector2D::modulus() const
{
	return sqrt(_x * _x + _y * _y);
}

/*
 * Calculate the unitary vector of the Vector
 */
Vector2D Vector2D::normalize()
{
	return *this / modulus();
}

/*
 * Calculate the vector proyection
 */
Vector2D Vector2D::projectionOn(const Vector2D &v) const
{
	return v * ((*this * v) / (v * v));
}

Vector2D Vector2D::reflect(const Vector2D &normal) const
{
	return (*this) - 2.0 * (*this * normal) * normal;
}

Vector2D Vector2D::operator+(const Vector2D &v) const
{
	return Vector2D(_x + v._x, _y + v._y);
}

Vector2D Vector2D::operator-(const Vector2D &v) const
{
	return Vector2D(_x - v._x, _y - v._y);
}

Vector2D Vector2D::operator-() const
{
	return Vector2D(-_x, -_y);
}

double Vector2D::operator*(const Vector2D &v) const
{
	return _x * v._x + _y * v._y;
}

Vector2D Vector2D::operator*(const double &k) const
{
	return Vector2D(k * _x, k * _y);
}

Vector2D operator*(const double &k, const Vector2D &v)
{
	return Vector2D(k * v._x, k * v._y);
}

bool Vector2D::isIn(const Vector2D &leftInferior, const Vector2D &rightSuperior) const
{
	return (_x >= leftInferior._x) &&
		   (_y >= leftInferior._y) &&
		   (_x <= rightSuperior._x) &&
		   (_y <= rightSuperior._y);
}

bool Vector2D::isIn(const double minX, const double minY, const double maxX, const double maxY) const
{
	return (_x >= minX) &&
		   (_y >= minY) &&
		   (_x <= maxX) &&
		   (_y <= maxY);
}

Vector2D Vector2D::operator/(const double &k) const
{
	return Vector2D(_x / k, _y / k);
}

ostream &operator<<(ostream &os, const Vector2D &v)
{
	return os << "(" << v._x << "," << v._y << ")";
}

Vector2D Vector2D::cutPoint(const Vector2D &p1, const Vector2D &p2, const Vector2D &pp1, const Vector2D &pp2)
{
	double a1 = p2._y - p1._y;
	double b1 = p1._x - p2._x;
	double c1 = a1 * p1._x + b1 * (p1._y);

	double a2 = pp2._y - pp1._y;
	double b2 = pp1._x - pp2._x;
	double c2 = a2 * pp1._x + b2 * (pp1._y);

	double determinat = a1 * b2 - a2 * b1;

	if (determinat == 0)
	{
		return p1;
	}
	else
	{
		double xx = (b2 * c1 - b1 * c2) / determinat;
		double yy = (a1 * c2 - a2 * c1) / determinat;
		return Vector2D(xx, yy);
	}
}

Vector2D Vector2D::unitary(const double angle)
{
	return Vector2D(cos(angle), sin(angle));
}

double Vector2D::angleBetween(const Vector2D v1, const Vector2D v2)
{
	return acos(v1 * v2 / (v1.modulus() + v2.modulus()));
}
