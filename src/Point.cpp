//#include "stdafx.h"
#include "Point.h"



double Point::getX()
{
	return this->x;
}

double Point::getY()
{
	return this->y;
}

void Point::setX(double x)
{
	this->x = x;
}

void Point::setY(double y)
{
	this->y = y;
}

Point::Point()
{

}

Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}


Point::~Point()
{
}

ostream & operator<<(ostream & out, Point point)
{
	out << "(" << point.x << ", " << point.y << ")";
	return out;
}
