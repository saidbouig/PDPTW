#pragma once
//#include "stdafx.h"
#include <string>
#include <vector>
#include "Point.h"
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;
class Course
{
private:
	Point position;
	string temps;
	int twStart = -1, twEnd = -1;
	int numVehicule, demand, id;
	int duree = -1;
	static const int VITESSE = 30;
	static int numberCourses;

public:
	Course();
	Course(const  Course &);
	~Course();
	Course(Point dep);
	bool checkTimeFormat(string s);

	double getDistance(Course c);

	double getEpsilon(Course c);
	//int getDuree();

	bool isCompatible(Course c);
	std::vector<Course> trierParTemps(std::vector<Course> courses);
	std::vector<Course> trierParDistance(std::vector<Course> courses);
	std::vector<Course> ptvct(std::vector<Course> courses);
	std::vector<std::vector<std::vector<Course> > > populationIni(std::vector<Course>);
	std::vector<std::vector<Course> > generateChromosome(std::vector<Course> &);
	std::vector<std::vector<std::vector<Course> > > generatePopulation(std::vector<Course> &courses,double & fitness);
	std::vector<std::vector<Course> > crossOverChromosome(std::vector<std::vector<Course> >  dad, std::vector<std::vector<Course> > mum) ;
    std::vector<std::vector<Course> > mutateChromosome(std::vector<std::vector<Course> > chromosome);


	//ofstream & ofstream<<();

	// GETTERS & SETTERS
	Point getPosition();
	void setPosition(Point depart);
	static void setNumberCourses(int );
	static int getNumberCourses();
	/*Point getArrivee();
	void setArrivee(Point arrivee);*/
	string getTemps();
	void setTemps(string temps);
	int getNumVehicule();
	void setNumVehicule(int numVehicule);
	/*int getTempsDepartMin(Course c);
	int getTempsArriveeMax(Course c);
	int getTempsDepartMax(Course c);
	int getTempsArriveeMin(Course c);
	void setTempsDepartMin(int tdMin);
	void setTempsArriveeMax(int taMax);
	void setTempsDepartMax(int tdMax);
	void setTempsArriveeMin(int taMin);*/
	int getTwStart();
	void setTwStart(int);
	int getTwEnd();
	void setTwEnd(int);
	void setDemand(int d);
	int getDemand();
	void setId(int i);
	int getId();
	bool allSet(vector<Course>);
	void ReSet(vector<Course>& courses);

	/*std::vector<Course> ptvct(std::vector<Course> courses);
	vector<Course> trierParTemps(std::vector<Course> courses);*/
	void afficher();
	friend ostream & operator<<(ostream &out, Course & course);

	ostream& operator<<(ostream &flux);

	//char* toString();


};

