#include"Vector2D.h"
#include<math.h>

Vector2D::Vector2D() :x(0), y(0) {};

Vector2D::Vector2D(const double x, const double y) :x(x), y(y) {};

/*
 * Get the X component of the Vector
*/
double Vector2D::getX() const
{
	return x;
}

/*
 * Get the Y component of the Vector
*/
double Vector2D::getY() const
{
	return y;
}

/*
 * Get the X component of the Vector
*/
double Vector2D::setX(double _x)
{
	return x = _x;
}

/*
 * Get the Y component of the Vector
*/
double Vector2D::setY(double _y)
{
	return y = _y;
}

/*
 * Calculate modulus of the Vector
*/
double Vector2D::modulus() const
{
	return sqrt(x * x + y * y);
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
Vector2D Vector2D::projectionOn(const Vector2D& v) const
{
	return v * ((*this*v)/(v*v));
}

Vector2D Vector2D::reflect(const Vector2D& normal) const
{
	return (*this) - 2.0*(*this*normal)*normal;
}

Vector2D Vector2D::operator+(const Vector2D& v) const
{
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::operator-() const
{
	return Vector2D(-x, -y);
}

double Vector2D::operator*(const Vector2D& v) const
{
	return x * v.x + y * v.y;
}

Vector2D Vector2D::operator*(const double& k) const
{
	return Vector2D(k*x, k*y);
}

Vector2D operator*(const double& k , const Vector2D& v) 
{
	return Vector2D(k*v.x, k*v.y);
}

bool Vector2D::isIn(const Vector2D& leftInferior, const Vector2D& rightSuperior) const {
	return (x >= leftInferior.x) &&
		   (y >= leftInferior.y) &&
		   (x <= rightSuperior.x) &&
		   (y <= rightSuperior.y);
}

bool Vector2D::isIn(const double minX, const double minY, const double maxX, const double maxY) const {
	return (x >= minX) &&
		   (y >= minY) &&
		   (x <= maxX) &&
		   (y <= maxY);
}

Vector2D Vector2D::operator/(const double& k) const
{
	return Vector2D(x / k, y / k);
}

ostream& operator<<(ostream& os, const Vector2D& v) 
{
	return os << "(" << v.x << "," << v.y << ")";
}

Vector2D Vector2D::cutPoint(const Vector2D& p1, const Vector2D& p2, const Vector2D& pp1, const Vector2D& pp2) 
{
	double a1 = p2.y - p1.y;
	double b1 = p1.x - p2.x;
	double c1 = a1 * p1.x + b1 * (p1.y);

	double a2 = pp2.y - pp1.y;
	double b2 = pp1.x - pp2.x;
	double c2 = a2 * pp1.x + b2 * (pp1.y);

	double determinat = a1 * b2 - a2 * b1;

	if (determinat == 0) {
		return p1;
	}
	else {
		double xx = (b2*c1 - b1 * c2) / determinat;
		double yy = (a1*c2 - a2 * c1) / determinat;
		return Vector2D(xx, yy);
	}
}

Vector2D Vector2D::unitary(const double angle) {
	return Vector2D(cos(angle), sin(angle));
}

double Vector2D::angleBetween(const Vector2D v1, const Vector2D v2) {
	return acos(v1*v2 / (v1.modulus() + v2.modulus()));
}
