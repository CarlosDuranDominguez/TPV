#include"Vector2D.h"
#include<math.h>
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
	return (*this) - normal*normal*(*this)*2.0;
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
