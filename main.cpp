// PTVCT.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include"Course.h"
#include<iostream>
#include <fstream>
#include <string>
#include "Vehicule.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<Population.h>
using namespace std;




/**
*Testing if the gene is valid
*/
//bool isValideGene(std::vector<Course> gene){
//    for(int i=2; i<gene.size()-1;i+=2)
//        {
//            //cout<<i<< " "<< gene.at(i).getId()<<" "<<i<<" "<<gene.at(i).getTwStart()<<endl;
//            //cout<<gene.at(i).getId()<<" "<<gene.at(i+1).getId() << ": "<< gene.at(i).isCompatible(gene.at(i+1))<<" \n";
//            //cout<<"Test :"<<gene.at(i).isCompatible(gene.at(i+1))<<" ";
//            if(gene.at(i).isCompatible(gene.at(i+1))==false)
//            return false;
//        }
//
//    return true;
//}
//
//bool isValideChromosome(std::vector<std::vector<Course> > chromosome){
//    for (int i=0;i<chromosome.size();i++)
//    {
//        if(! isValideGene(chromosome.at(i))) return false;
//    }
//}



//double fitnessChromosome( std::vector<std::vector<Course> > chromosome){
//    return 0.5*costChromosome(chromosome) + 0.4*vehiculeNumber(chromosome);//+0.1*isValideGene(chromosome);
//
//}


void printChromosome(std::vector<std::vector<Course> > a) {
	cout << "Chromosome: " << endl;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j <a.at(i).size(); j++)
		{
			cout<<a.at(i).at(j).getId()<<" ";
		}
		cout << endl;

	}
}




int main()
{
    double wtime;
    /*OpenMP Intro */
    cout << "  Number of processors available = " << omp_get_num_procs ( ) << "\n";
    cout << "  Number of threads =              " << omp_get_max_threads ( ) << "\n";
	//Calculate start time
    wtime = omp_get_wtime ( );

	srand(time(NULL));
	fstream instream("C:\\dataset\\AA45");
	vector<Course> myCourses;
	string line;
	int id = 0, n, tmp, capacite, cpt = 0, TwStart = 0, TwEnd = 0, demand = 0;
	double  x = 0, y = 0, serTime = 0;
	std::cout << "Here in the main classe :D :D \n";

	if (instream.is_open()) {
		instream >> n >> n;
		Course::setNumberCourses(n);
		const int nbr = n;
		instream >> tmp >> capacite >> tmp;
		Vehicule::setMAXCapacity(capacite);
		//std::cout << n << " " << capacite << endl;
		//std::cout << 2 * n + 1 << endl;
		for (int i = 0; i < 2 * n + 2; i++) {

			instream >> id >> x >> y >> serTime >> demand >> TwStart >> TwEnd;
			Point point(x, y);
			Course course;
			course.setId(id);
			course.setPosition(point);
			course.setTwStart(TwStart);
			course.setTwEnd(TwEnd);
			course.setDemand(demand);
			myCourses.push_back(course);

		}

	}

    Population population ;
    //std::vector<std::vector<Course> > chromosome1;

    population.generatePopulation(myCourses);
    //chromosome1 = population.generateChromosome(myCourses);
    //printChromosome(chromosome1);
    //cout<<"ISValide : "<<population.isValideChromosome(chromosome1);
	//End OMP Parallel





	//vector<Course>().swap(myCourses);
	/**/

//	cout<<"Theinput data \n";
//	for (int i = 0; i < myCourses.size(); i++) {
//            cout<<myCourses.at(i)<<endl;
//	}
//
//	std::vector<std::vector<Course> > chromosome1;
//	std::vector<std::vector<Course> > chromosome2;
//	std::vector<std::vector<Course> > chromosome3;
//	std::vector<std::vector<Course> > chromosome4;
//
//	/*The methode generate chromosome uses a reference argument, so the change affects the initial vector*/
//	chromosome1 = myCourses.at(0).generateChromosome(myCourses);
//	std::cout << "Generation 1\n";
//	printChromosome(chromosome1);
//	myCourses.at(0).ReSet(myCourses);
//	std::cout << "Generating the second chromosome\n";
//	chromosome3 = myCourses.at(1).generateChromosome(myCourses);
//	printChromosome(chromosome3);
//	std::cout << "finishing the generation\n";
//	chromosome2 = mutateChromosome(chromosome1);
//	chromosome2 = mutateChromosome(chromosome2);
//	std::cout << "After the mutation \n";
//	printChromosome(chromosome2);
	//chromosome4 = crossOverChromosome(chromosome1, chromosome2);
	//printChromosome(chromosome4);

//	std::cout << "Cost du gene"<<costGene(chromosome2.at(0))<<endl;;
//	for(int i=0 ;i<chromosome1.size();i++)
//        std::cout << "Validité du gene "<<isValideGene(chromosome1.at(i))<<endl;;
////    for(int i=0 ;i<chromosome2.size();i++)
//        std::cout << "Validité du gene "<<isValideGene(chromosome2.at(i))<<endl;;

    //std::cout << "Cost du Chromosome 1"<<costChromosome(chromosome2)<<endl;;
//
//    std::cout << "fitness du Chromosome 1"<<fitnessChromosome(chromosome1)<<endl;
//    std::cout << "fitness du Chromosome 2"<<fitnessChromosome(chromosome2)<<endl;
//    std::cout << "fitness du Chromosome 3"<<fitnessChromosome(chromosome3)<<endl;

	//do {
		//chromosome2 = mutateChromosome(chromosome1);
		///chromosome3 = crossOverChromosome(chromosome1, chromosome2);

		/*cout << "Chromosome 1: " << endl;
		printChromosome(chromosome1);
		cout << "Chromosome 2: " << endl;
		printChromosome(chromosome2);
		cout << "Chromosome 3: " << endl;*/
		//printChromosome(chromosome3);
	//} while (true);
	/*
	for (int j = 0; j < myCourses.size(); j++)
		std::cout << myCourses.at(j);
	*/


	/*
	cout << "Chromosome 1: " << endl;
	chromosome2 =mutateChromosome(chromosome3);
	cout << "Chromosome 1: " << endl;
	printChromosome(chromosome1);
	cout << "Chromosome 2: " << endl;
	printChromosome(chromosome2);
	cout << "Chromosome 3: " << endl;
	printChromosome(chromosome3);
	*/

	//chromosome2 = myCourses.at(0).generateChromosome(myCourses);
	/*
	for (int j = 0; j < myCourses.size(); j++)
		std::cout << myCourses.at(j);
	*/

	//std::vector<std::vector<std::vector<Course>>> population;


	//population = myCourses.at(0).populationIni(myCourses);
//	for (int j = n; j < 2*n+1; j++)
//		for (int i = 0; i < n; i++) {
//			std::cout << "Course: " << j<< ", Course: " << i << " " << myCourses.at(j).isCompatible(myCourses.at(i)) << endl;
//		}
//		std::cout << endl;
    //std::cout <<  myCourses.at(1).isCompatible(myCourses.at(31)) << endl;
	int a;

    cout << "  Elapsed wall clock time = " << wtime << "\n";

	//std::cin >> a;
// PTVCT.cpp : Defines the entry point for the console application.
//
#include <omp.h>

//#include "stdafx.h"
#include"Course.h"
#include<iostream>
#include <fstream>
#include <string>
#include "Vehicule.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<Population.h>
using namespace std;




/**
*Testing if the gene is valid
*/
//bool isValideGene(std::vector<Course> gene){
//    for(int i=2; i<gene.size()-1;i+=2)
//        {
//            //cout<<i<< " "<< gene.at(i).getId()<<" "<<i<<" "<<gene.at(i).getTwStart()<<endl;
//            //cout<<gene.at(i).getId()<<" "<<gene.at(i+1).getId() << ": "<< gene.at(i).isCompatible(gene.at(i+1))<<" \n";
//            //cout<<"Test :"<<gene.at(i).isCompatible(gene.at(i+1))<<" ";
//            if(gene.at(i).isCompatible(gene.at(i+1))==false)
//            return false;
//        }
//
//    return true;
//}
//
//bool isValideChromosome(std::vector<std::vector<Course> > chromosome){
//    for (int i=0;i<chromosome.size();i++)
//    {
//        if(! isValideGene(chromosome.at(i))) return false;
//    }
//}



//double fitnessChromosome( std::vector<std::vector<Course> > chromosome){
//    return 0.5*costChromosome(chromosome) + 0.4*vehiculeNumber(chromosome);//+0.1*isValideGene(chromosome);
//
//}


void printChromosome(std::vector<std::vector<Course> > a) {
	cout << "Chromosome: " << endl;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j <a.at(i).size(); j++)
		{
			cout<<a.at(i).at(j).getId()<<" ";
		}
		cout << endl;

	}
}




#pragma omp parallel
int main()
{
    double wtime;
    /*OpenMP Intro */
    cout << "  Number of processors available = " << omp_get_num_procs ( ) << "\n";
    cout << "  Number of threads =              " << omp_get_max_threads ( ) << "\n";
	//Calculate start time
    wtime = omp_get_wtime ( );

	srand(time(NULL));
	fstream instream("C:\\dataset\\AA45");
	vector<Course> myCourses;
	string line;
	int id = 0, n, tmp, capacite, cpt = 0, TwStart = 0, TwEnd = 0, demand = 0;
	double  x = 0, y = 0, serTime = 0;
	std::cout << "Here in the main classe :D :D \n";

	if (instream.is_open()) {
		instream >> n >> n;
		Course::setNumberCourses(n);
		const int nbr = n;
		instream >> tmp >> capacite >> tmp;
		Vehicule::setMAXCapacity(capacite);
		//std::cout << n << " " << capacite << endl;
		//std::cout << 2 * n + 1 << endl;
        #pragma omp parallel for
		for (int i = 0; i < 2 * n + 2; i++) {

			instream >> id >> x >> y >> serTime >> demand >> TwStart >> TwEnd;
			Point point(x, y);
			Course course;
			course.setId(id);
			course.setPosition(point);
			course.setTwStart(TwStart);
			course.setTwEnd(TwEnd);
			course.setDemand(demand);
			myCourses.push_back(course);

		}

	}

    Population population ;
    //std::vector<std::vector<Course> > chromosome1;

    population.generatePopulation(myCourses);
    //chromosome1 = population.generateChromosome(myCourses);
    //printChromosome(chromosome1);
    //cout<<"ISValide : "<<population.isValideChromosome(chromosome1);
	//End OMP Parallel





	//vector<Course>().swap(myCourses);
	/**/

//	cout<<"Theinput data \n";
//	for (int i = 0; i < myCourses.size(); i++) {
//            cout<<myCourses.at(i)<<endl;
//	}
//
//	std::vector<std::vector<Course> > chromosome1;
//	std::vector<std::vector<Course> > chromosome2;
//	std::vector<std::vector<Course> > chromosome3;
//	std::vector<std::vector<Course> > chromosome4;
//
//	/*The methode generate chromosome uses a reference argument, so the change affects the initial vector*/
//	chromosome1 = myCourses.at(0).generateChromosome(myCourses);
//	std::cout << "Generation 1\n";
//	printChromosome(chromosome1);
//	myCourses.at(0).ReSet(myCourses);
//	std::cout << "Generating the second chromosome\n";
//	chromosome3 = myCourses.at(1).generateChromosome(myCourses);
//	printChromosome(chromosome3);
//	std::cout << "finishing the generation\n";
//	chromosome2 = mutateChromosome(chromosome1);
//	chromosome2 = mutateChromosome(chromosome2);
//	std::cout << "After the mutation \n";
//	printChromosome(chromosome2);
	//chromosome4 = crossOverChromosome(chromosome1, chromosome2);
	//printChromosome(chromosome4);

//	std::cout << "Cost du gene"<<costGene(chromosome2.at(0))<<endl;;
//	for(int i=0 ;i<chromosome1.size();i++)
//        std::cout << "Validité du gene "<<isValideGene(chromosome1.at(i))<<endl;;
////    for(int i=0 ;i<chromosome2.size();i++)
//        std::cout << "Validité du gene "<<isValideGene(chromosome2.at(i))<<endl;;

    //std::cout << "Cost du Chromosome 1"<<costChromosome(chromosome2)<<endl;;
//
//    std::cout << "fitness du Chromosome 1"<<fitnessChromosome(chromosome1)<<endl;
//    std::cout << "fitness du Chromosome 2"<<fitnessChromosome(chromosome2)<<endl;
//    std::cout << "fitness du Chromosome 3"<<fitnessChromosome(chromosome3)<<endl;

	//do {
		//chromosome2 = mutateChromosome(chromosome1);
		///chromosome3 = crossOverChromosome(chromosome1, chromosome2);

		/*cout << "Chromosome 1: " << endl;
		printChromosome(chromosome1);
		cout << "Chromosome 2: " << endl;
		printChromosome(chromosome2);
		cout << "Chromosome 3: " << endl;*/
		//printChromosome(chromosome3);
	//} while (true);
	/*
	for (int j = 0; j < myCourses.size(); j++)
		std::cout << myCourses.at(j);
	*/


	/*
	cout << "Chromosome 1: " << endl;
	chromosome2 =mutateChromosome(chromosome3);
	cout << "Chromosome 1: " << endl;
	printChromosome(chromosome1);
	cout << "Chromosome 2: " << endl;
	printChromosome(chromosome2);
	cout << "Chromosome 3: " << endl;
	printChromosome(chromosome3);
	*/

	//chromosome2 = myCourses.at(0).generateChromosome(myCourses);
	/*
	for (int j = 0; j < myCourses.size(); j++)
		std::cout << myCourses.at(j);
	*/

	//std::vector<std::vector<std::vector<Course>>> population;


	//population = myCourses.at(0).populationIni(myCourses);
//	for (int j = n; j < 2*n+1; j++)
//		for (int i = 0; i < n; i++) {
//			std::cout << "Course: " << j<< ", Course: " << i << " " << myCourses.at(j).isCompatible(myCourses.at(i)) << endl;
//		}
//		std::cout << endl;
    //std::cout <<  myCourses.at(1).isCompatible(myCourses.at(31)) << endl;
	int a;
	std::cout << "\n\n\n Guess we finished xD, give me something in return :\n";

    cout << "  Elapsed wall clock time = " << wtime << "\n";

	//std::cin >> a;
	//std::cout << "See ya, you can have it back xD " << a << endl;
}

}

