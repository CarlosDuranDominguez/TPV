#include"Vector2D.h"
#include<math.h>
/*
 * Get the X component of the Vector
*/
double Vector2D::getX() 
{
	return x;
}
/*
 * Get the Y component of the Vector
*/
double Vector2D::getY()
{
	return y;
}
/*
 * Calculate modulus of the Vector
*/
double Vector2D::modulus() 
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
Vector2D Vector2D::projectionOn(Vector2D v)
{
	return v * ((*this*v)/(v*v));
}
Vector2D Vector2D::reflect(Vector2D normal)
{
	return (*this) - normal*normal*(*this)*2.0;
}
Vector2D Vector2D::operator+(const Vector2D v) 
{
	return Vector2D(x + v.x, y + v.y);
}
Vector2D Vector2D::operator-(const Vector2D v) 
{
	return Vector2D(x - v.x, y - v.y);
}
double Vector2D::operator*(const Vector2D v) 
{
	return x * v.x + y * v.y;
}
Vector2D Vector2D::operator*(const double k) 
{
	return Vector2D(k*x, k*y);
}
Vector2D operator*(const double k , const Vector2D v) 
{
	return Vector2D(k*v.x, k*v.y);
}

Vector2D Vector2D::operator/(const double k) 
{
	return Vector2D(x / k, y / k);
}
ostream& operator<<(ostream& os, const Vector2D v) 
{
	return os << "(" << v.x << "," << v.y << ")";
}
