#pragma once
//#include "stdafx.h"
#include<ostream>
using namespace std;
class Point
{
private:
	double x, y;
public:
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
	Point();
	Point(double, double);
	~Point();
	friend ostream& operator<<(ostream& out, Point point);

};

