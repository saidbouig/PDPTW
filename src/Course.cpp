//#include "stdafx.h"
#include "Course.h"
#include  "Vehicule.h"
#include<stdlib.h>
#include<stdio.h>



using namespace std;


int Course::numberCourses;
Course::Course()
{
	Course::VITESSE;
	numVehicule = -1;
	//depart = NULL;
	//arrivee = null;
}

Course::Course(const Course & course)
{
	position = course.position;
	temps = course.temps;
	twStart = course.twStart;
	twEnd = course.twEnd;
	numVehicule = course.numVehicule;
	demand = course.demand;
	duree = course.duree;
	id = course.id;

}


Course::~Course()
{
	/*delete depart;
	delete arrivee;
	delete temps;*/
}

Course::Course(Point dep)
{
	position = dep;
	/*if (checkTimeFormat(temps))
		this->temps = temps;
	else
		cout << "Exception Error : Course Invalide !!";*/
}



double Course::getDistance(Course c)
{
    return sqrt(pow(position.getX() - c.position.getX(), 2) + pow(position.getY() - c.position.getY(), 2));
}


int Course::getTwEnd()
{
	return twEnd;
}


void Course::setTwEnd(int t)
{
	this->twEnd = t;
}

int Course::getTwStart()
{
	return twStart;
}


void Course::setTwStart(int taMin)
{
	this->twStart = taMin;
}

void Course::setDemand(int d)
{
	demand = d;
}

int Course::getDemand()
{
	return demand;
}

void Course::setId(int i)
{
	id = i;
}

int Course::getId()
{
	return id;
}

bool Course::allSet(vector<Course> courses)
{
	bool res = true;
	for (unsigned int i = 1; i < courses.size(); i++) {
		if (courses.at(i).getNumVehicule() == -1) {
			std::cout << "Course not set: " << courses.at(i).getId() << endl;
			return false;
		}

	}
	return res;
}

void Course::ReSet(vector<Course> &courses)
{
	for (unsigned int i = 0; i < courses.size(); i++)
		courses.at(i).setNumVehicule(-1);
}

double Course::getEpsilon(Course c)
{
	double dist = sqrt(pow(position.getX() - c.position.getX(), 2) + pow(position.getY() - c.position.getY(), 2));
	return (int)(dist / VITESSE * 60);
}




bool Course::isCompatible(Course c)
{
	bool twS, twE;
	double epsilon = getEpsilon(c);
	twS = ((c.getTwStart() <= this->getTwStart() + epsilon)&& (this->getTwStart() + epsilon <= c.getTwEnd()));
	twE = ((c.getTwStart() <= this->getTwEnd() + epsilon )&&(this->getTwEnd() + epsilon <= c.getTwEnd()));
	return (twS || twE);
}

std::vector<Course> Course::trierParTemps(std::vector<Course> courses)
{
	int n = (int)courses.size();
	if (n == 0)
		return courses;
	int ind = 0;
	Course temp;

	for (int i = 0; i < n; i++) {
		ind = i;
		for (int j = i + 1; j < n; j++)
			if ((courses.at(j).getTwStart()) < (courses[ind].getTwStart()))
				ind = j;
		if (ind != i) {
			temp = courses[i];
			courses[i] = courses[ind];
			courses[ind] = temp;
		}
	}
	return courses;
}

std::vector<Course> Course::trierParDistance(std::vector<Course> courses)
{
	int n = (int)courses.size();
	if (n == 0)
		return courses;
	int ind = 0;
	Course temp;

	for (int i = 0; i < n; i++) {
		ind = i;
		for (int j = i + 1; j < n; j++)
			if ((this->getEpsilon(courses.at(j))) < (this->getEpsilon(courses[ind])))
				ind = j;
		if (ind != i) {
			temp = courses[i];
			courses[i] = courses[ind];
			courses[ind] = temp;
		}
	}
	return courses;
}

std::vector<Course> Course::ptvct(std::vector<Course> courses)
{
	return vector<Course>();
}







Point Course::getPosition()
{
	return this->position;
}

void Course::setPosition(Point depart)
{
	this->position = depart;
}

void Course::setNumberCourses(int n)
{
	numberCourses = n;
}

int Course::getNumberCourses()
{
	return numberCourses;
}

string Course::getTemps()
{
	return this->temps;
}

void Course::setTemps(string temps)
{
	this->temps = temps;
}

int Course::getNumVehicule()
{
	return this->numVehicule;
}

void Course::setNumVehicule(int numVehicule)
{
	this->numVehicule = numVehicule;
}

void Course::afficher()
{
	Point depart, arrivee;
	string temps;
	int tempsDepart = -1, tempsArrivee = -1;
	//int numVehicule;
	int duree = -1;
	static const int VITESSE = 20;
	cout << "Vehicule " << this->temps;
}

ostream & Course::operator<<(ostream & flux)
{
	flux << "Depart: (" << position.getX() << ", " << position.getY() << ")";
	flux << "TW [" << twStart << ", " << twEnd << "] Vehicule: " << numVehicule << "\n";
	return flux;
	// TODO: insert return statement here
}

ostream & operator<<(ostream & out, Course & course)
{
	out << "id :" << course.id << ", Depart: " << course.position << ", Demand: " <<
		course.demand << ", num vehicule " << course.numVehicule;
	out << ", Tw [" << course.twStart << ", " << course.twEnd << "], Vehicule: " << course.numVehicule << "\n";
	return out;
}
