#pragma once
#include "Course.h"
class Vehicule
{
private:

	int numV, capacity;
	static int MAX_Capacity;
	std::vector<Course> clients;
public:
	static int number_vehicules;
	Vehicule();
	~Vehicule();
	int getNumV();
	static int getNumber_vehicules();
	void setNumV(int c);
	void setCapacity(int c);
	int getCapacity();
	static void setMAXCapacity(int c);
	static int getMAXCapacity();
	static void setNumber_vehicules(int n);
	void setClients(std::vector<Course> courses);
	std::vector<Course> getClients();
};

