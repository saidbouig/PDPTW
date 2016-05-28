//#include "stdafx.h"
#include "Vehicule.h"

int Vehicule::number_vehicules=1;
int Vehicule::MAX_Capacity;

Vehicule::Vehicule()
{
	capacity = 0;
	numV = number_vehicules++;
}


Vehicule::~Vehicule()
{
    //number_vehicules--;
}

int Vehicule::getNumV()
{
	return numV;
}

int Vehicule::getNumber_vehicules()
{
	return number_vehicules;
}

void Vehicule::setNumV(int c)
{
	numV = c;
}

void Vehicule::setCapacity(int c)
{
	capacity = c;
}

int Vehicule::getCapacity()
{
	return capacity;
}

void Vehicule::setMAXCapacity(int c)
{
	MAX_Capacity = c;
}

int Vehicule::getMAXCapacity()
{
	return MAX_Capacity;
}

void Vehicule::setNumber_vehicules(int n)
{
	number_vehicules = n;
}

void Vehicule::setClients(vector<Course> courses)
{
	clients = courses;
}

vector<Course> Vehicule::getClients()
{
	return clients;
}
