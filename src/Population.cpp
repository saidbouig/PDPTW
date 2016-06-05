#include "Population.h"
#include <string>
#include <vector>
#include "Point.h"
#include <math.h>
#include <time.h>
#include <iostream>
#include<stdlib.h>
#include"Vehicule.h"
#include"Course.h"

using namespace std;

using namespace std;
Population::Population()
{
    //ctor
}

Population::~Population()
{
    //dtor
}

void Population::printChromosome(std::vector<std::vector<Course> > a) {

cout << "Print Chromosome: " << endl;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j <a.at(i).size(); j++)
		{
			cout<<a.at(i).at(j).getId()<<" ";
		}
		cout << endl;

	}
}

std::vector<std::vector<Course> > Population::crossOverChromosome(std::vector<std::vector<Course> >  dad, std::vector<std::vector<Course> > mum) {

	int min_ = (dad.size() > mum.size()) ? mum.size() : dad.size();
	int max_ = (dad.size() <= mum.size()) ? mum.size() : dad.size();
	//Resulted Chromosome
	std::vector<std::vector<Course> > child;

	//Randome parapport à la taille du chromosome a
	//srand(time(NULL));

	//randomint has value between 0 and min-1
	int randomint = (rand() % min_-1) + 1;

	//copying the 1st half of a into c

	//std::cout << "Before\nn";
    std::vector<Course> tmp;

	for (int i = 0; i <= randomint; i++) {
            //cout<<"boocle 1 "<<i<< " "<<endl;
		if(dad.size()==min_)
            child.push_back(dad.at(i));
            //std::vector<Course> tmp(dad.at(i));
        else
            child.push_back(mum.at(i));


            //std::vector<Course> tmp(mum.at(i));

	}
	//std::cout << "After the first\n";
	for (int i = randomint + 1; i < max_; i++) {
	    //cout<<"boocle2 "<<i<< "min: "<<min_<<", max: "<<max_ <<endl;
	    if(dad.size()==min_)
            child.push_back(mum.at(i));
        else
            child.push_back(dad.at(i));

	}
	//cout << "CrossOver chromosome :" << endl;
	//cout << "mid ind : " <<randomint << endl;
	return child;


}


std::vector<std::vector<Course> > Population::mutateChromosome(std::vector<std::vector<Course> > chromosome) {
	//srand(time(NULL));
	std::vector<std::vector<Course> > mutatedChromosome = chromosome;

	//Choosing two random vehicules, from the chromosome

	int tournee1 ;
	//do{
        tournee1= (rand() % chromosome.size()) ;
        //cout<<"tournée 1 "<< tournee1<<endl;
	//}while(chromosome.at(tournee1).size()==1);

	int tournee2;
	//do{
        tournee2= (rand() % chromosome.size()) ;
        //cout<<"tournée 2 "<< tournee2<<endl;

	//}while(chromosome.at(tournee2).size()==1);

	int course1, course2;

	//Choosing a random node -might be a pickup or a delivery one-, other than the depot
	do {
		course1 = (rand() % chromosome.at(tournee1).size()-1) + 1;

	} while ( (!course1) || course1%2 ==0);
	//Same thing, choosing a random node
	do {

		course2 = (rand() % chromosome.at(tournee2).size()-1) + 1;
	} while ((!course2) ||  course2%2 ==0);

	//cout << "Mutate chromosome :" << endl;
	//cout << "Tournée : " << tournee1 << " Course : " << course1 << " With Tournée : " << tournee2 << " Course :" << course2 << endl;
	Course tmp = mutatedChromosome.at(tournee1).at(course1);
	Course tmp2= mutatedChromosome.at(tournee1).at(course1+1);
	mutatedChromosome.at(tournee1).at(course1) = mutatedChromosome.at(tournee2).at(course2);
    mutatedChromosome.at(tournee1).at(course1+1) = mutatedChromosome.at(tournee2).at(course2+1);

	mutatedChromosome.at(tournee2).at(course2) = tmp;
    mutatedChromosome.at(tournee2).at(course2+1) = tmp2;

	//cout << "end mutate\n";

	return mutatedChromosome;
}



bool Population::isValideGene(std::vector<Course> gene){
    for(int i=2; i<gene.size()-1;i+=2)
        {
            //cout<<i<< " "<< gene.at(i).getId()<<" "<<i<<" "<<gene.at(i).getTwStart()<<endl;
            //cout<<gene.at(i).getId()<<" "<<gene.at(i+1).getId() << ": "<< gene.at(i).isCompatible(gene.at(i+1))<<" \n";
            //cout<<"Test :"<<gene.at(i).isCompatible(gene.at(i+1))<<" ";
            if(gene.at(i+1).isCompatible(gene.at(i))==false)
            return false;
        }

    return true;
}

bool Population::isValideChromosome(std::vector<std::vector<Course> > chromosome){
    for (int i=0;i<chromosome.size();i++)
    {
        if(! isValideGene(chromosome.at(i))) return false;
    }
    return true;
}



int Population::countPenality(std::vector<std::vector<Course> > chromosome){
    int globalSize=0;
    std::vector<Course> chromosomeList;
    //Default penality == 1
    int penality=1;

    //Calculating sum of routes sizes of chromosome
    for(int i=0 ; i < chromosome.size() ; i++)
        globalSize+=chromosome.at(i).size();
    //Transforming routes into a List
    chromosomeList.reserve( globalSize ); // preallocate memory

    for(int i=0 ; i < chromosome.size() ; i++)
        chromosomeList.insert( chromosomeList.end(), chromosome.at(i).begin()+1, chromosome.at(i).end() );

    for(int i=0 ; i<chromosomeList.size();i++){
        for(int j=i+1 ;j<chromosomeList.size();j++){
            if(chromosomeList.at(i).getId()==chromosomeList.at(j).getId())
                //chromosomeList.erase(chromosomeList.begin()+j);
                //if there is a duplicata add to penality
                penality++;
        }
    }
    return penality;
}


double Population::costGene(std::vector<Course> gene){
    double cost=0;
    if(gene.size()==0 || gene.size()==1) return 0;

    #pragma omp parallel for private (i)
    for(int i=0; i<gene.size()-1;i++)
        cost+=gene.at(i).getDistance(gene.at(i+1));

    cost+=gene.at(gene.size()-1).getDistance(gene.at(0));
    return cost;
}

double Population::costChromosome(std::vector<std::vector<Course> > chromosome){
    double cost=0;
    if(chromosome.size()==0) return 0;

    #pragma omp parallel for private (i)
    for(int i=0; i<chromosome.size();i++)
        cost+=costGene(chromosome.at(i));
    return cost;
}

int Population::vehiculeNumber(std::vector<std::vector<Course> > chromosome){
    int _vehiculeNumber;
    for(int i=0 ; i<chromosome.size();i++)
        if(chromosome.at(i).size()>=2) _vehiculeNumber++;

    return _vehiculeNumber;
}
double Population::fitnessChromosome( std::vector<std::vector<Course> > chromosome){
    return (0.3*costChromosome(chromosome) + 0.2*vehiculeNumber(chromosome)+0.5 *isValideChromosome(chromosome))*countPenality(chromosome);
}


std::vector<std::vector<Course> > Population::generateChromosome(std::vector<Course> & courses)
{
	std::vector<std::vector<Course> > chromosome, chromosome1;
	unsigned int nbr = 0;
	/*Using this loop invariant, because the max number of itterations is a vehicule per Course.
	:/But we'll have a problem, which is the number of vehicules, and the courses os size 1*/
	while ((nbr++)<= courses.size()) {
		std::vector<Course> tmp;
		Vehicule vehicule;
		int numV = vehicule.getNumV(), maxCapacity = vehicule.getMAXCapacity();
		courses.at(0).setNumVehicule(0);
		courses.at(courses.size() - 1).setNumVehicule(0);
		tmp.push_back(courses.at(0));
		bool b = true;
		std::vector<Course> sorted(courses.begin()+1, courses.begin() + Course::getNumberCourses() + 1);
		sorted = courses.at(0).trierParDistance(sorted);
		/*Insert the first Pickup node, and it's according delivery one*/
		unsigned int cpt = 0;
		unsigned int rInt = (rand() % Course::getNumberCourses() -1)  + 1;
		//std::cout <<"rand :" <<rInt << endl;
		while(b && (cpt<=sorted.size()-1)){
			//std::cout << tmp.at(0).isCompatible(sorted.at(cpt)) << endl;
			if ((tmp.at(0).isCompatible(sorted.at(rInt)))&&(courses.at(sorted.at(rInt).getId()).getNumVehicule()==-1)) {
                //cout<<"First "<< tmp.at(0).getId() << ", " << sorted.at(rInt).getId() <<": "<<sorted.at(rInt).isCompatible(tmp.at(0))<<endl;
				courses.at(sorted.at(rInt).getId()).setNumVehicule(numV);
				courses.at(sorted.at(rInt).getId() + Course::getNumberCourses()).setNumVehicule(numV);
				tmp.push_back(sorted.at(sorted.at(rInt).getId()));
				tmp.push_back(courses.at(sorted.at(rInt).getId() + Course::getNumberCourses()));
				//std::cout << "Setting the course IfOne" << sorted.at(rInt).getId() << " "  << endl;
				b = false;
			}
			cpt++;
		}
		/*In this loop, we sort the elements according to the distance of the last delivery node*/
		for (int k = 1; k < Course::getNumberCourses(); k++) {
			sorted = tmp.at(tmp.size() - 1).trierParDistance(sorted);
			if (sorted.at(k).isCompatible(tmp.at(tmp.size() - 1)) && (courses.at(sorted.at(k).getId()).getNumVehicule() == -1)) {
				//std::cout<< "Loop "<< tmp.at(tmp.size() - 1).getId() << ", " << sorted.at(k).getId() <<": "<<sorted.at(k).isCompatible(tmp.at(tmp.size() - 1))<<endl;
				courses.at(sorted.at(k).getId()).setNumVehicule(numV);
				courses.at(sorted.at(k).getId() + Course::getNumberCourses()).setNumVehicule(numV);
				tmp.push_back(courses.at(sorted.at(k).getId()));
				tmp.push_back(courses.at(sorted.at(k).getId() + Course::getNumberCourses()));
				//std::cout << "Setting the course IfTwo" << sorted.at(k).getId() << " " << endl;
			}

		}
		//std::cout <<"\n\npushing the "<< tmp.size()<<"ReLooping\n\n";
		chromosome.push_back(tmp);
	}

	for (unsigned int i = 0; i < chromosome.size(); i++) {
		if (chromosome.at(i).size() != 1)
			chromosome1.push_back(chromosome.at(i));
	}
    //cout << "#Validité du Chromosome : " <<isValideChromosome(chromosome1)<<endl;
    	courses.at(0).ReSet(courses);
//        for(int i=0 ; i<chromosome1.size();i++){
//                for(int j=0 ; j<chromosome1.at(i).size();j++)
//            std::cout<<chromosome1.at(i).at(j)<<" ";
//
//        }
	return chromosome1;
	//return std::vector<std::vector<Course>>();
}

bool Population::ChromosomeEquals(std::vector<std::vector<Course> > a , std::vector<std::vector<Course> > b){
    if(fitnessChromosome(a)==fitnessChromosome(b)) return true;
    return false;
//    if(a.size()==b.size()) return false;
//        for(int i=0;i<a.size();i++){
//            if(a.at(i).size()!=b.at(i).size()) return false;
//                for(j=0;j<a.at(i).size();j++){
//                    if(a.at(i).at(j)!=b.at(i).at(j)) return false;
//                }
//            }

}


    int Population::stable_fitness_limit_rounds=1;
    double Population::memorized_fitness=0;
    double Population::getMemorized_Fitness(){ return memorized_fitness;}
    int Population::getStable_Fitness_limit_rounds() { return stable_fitness_limit_rounds;}
    void Population::setMemorized_Fitness(double fitness){ memorized_fitness = fitness; }
    void Population::setStable_Fitness_limit_rounds( int fitness){ stable_fitness_limit_rounds= fitness;}


std::vector<std::vector<std::vector<Course> > > Population::generatePopulation(std::vector<Course> &courses)
{


    Course c ;
    std::vector<std::vector<std::vector<Course> > > pop;
    std::vector<double> fitness;

    std::cout << "Generation :"<<endl;
    std::vector<std::vector<Course> > generatedChromosome;

	for (unsigned int j = 0; j < MAX_SIZE_POP; j++) {
          /*test*/  //cout<<"here" << j<< endl;
        ///we can calculate fitness of each Chromosome  +  avg fitness of the population here too !
        generatedChromosome= Population::generateChromosome(courses);

        pop.push_back(generatedChromosome);
        //cout << "Fitness # "<<fitnessChromosome(generatedChromosome) <<" # ";
        fitness.push_back(fitnessChromosome(generatedChromosome));
        Vehicule::setNumber_vehicules(0);
        //cout<<"end chromosome generation"<<endl;
        generatedChromosome.clear();
	}

    //cout<<"Avant Pop ! :"<<endl;

    /*View Fitness of First Generation*/

	for(int i=0 ; i<fitness.size();i++)
        cout<< fitness.at(i) <<" ";

    Population::triPopulationASC(pop ,fitness);
    //cout<<"Best Fitness : " <<fitness.at(0)<<endl;


    /*cout<<"Apres Pop ! :"<<endl;
	for(int i=0 ; i<fitness.size();i++)
        cout<< fitness.at(i) <<" ";
        */


	std::vector<std::vector<std::vector<Course> > > newGeneration;
	std::vector<double> newGenerationFitness ;

    std::vector<std::vector<Course> > bestChromosome = pop.at(0);
    double BestFitness= fitness.at(0);
    Population::setMemorized_Fitness(fitness.at(0));

	for(int p=0 ; p<ITERATIONS ; p++){
            cout<<"Itération : "<<p<<" "<<endl;
            //cout<<"Crossover "<<endl;
            ///CrossOver
            for(int i=0 ; i < pop.size(); i++){
                for(int j=0 ; j<pop.size();j++){
                    //cout<<"test "<<i << "* "<<j<<endl;
                    if(i!=j){

                        //cout<<"E";
                        generatedChromosome = Population::crossOverChromosome(pop.at(j),pop.at(i));
                        ///TEST
                        //printChromosome(generatedChromosome);
                        //cout<<"F";
                        newGeneration.push_back(generatedChromosome);
                        //cout<<"G";
                        newGenerationFitness.push_back(fitnessChromosome(generatedChromosome));
                        //cout<<"H";
                    }
                }
            }
            cout<<"Mutation "<<endl;
            ///Mutation
            //cout<<" # "<<pop.size()<<" Population Size "<<endl;
            for(int i=0 ; i<pop.size()-1;i++){
                    //cout<<"what + "<<i<<":"<<endl;
                newGeneration.push_back(pop.at(i));
                //cout<<"a";
                newGenerationFitness.push_back(fitness.at(i));
                //cout<<"b";
                generatedChromosome = Population::mutateChromosome(pop.at(i));
                //cout<<"c";

                newGeneration.push_back(generatedChromosome);
                //cout<<"d";
                newGenerationFitness.push_back(fitnessChromosome(generatedChromosome));

            }

            //Selection
            cout<<"Selection "<<endl;
            //Trie :
            Population::triPopulationASC(newGeneration ,newGenerationFitness);
            //cout<<"New Generaton :: Best Fitness : " <<newGenerationFitness.at(0)<<endl;

            pop.clear();
            fitness.clear();
            double fitt;

            for(int i=0;i<newGeneration.size() && (pop.size()<MAX_SIZE_POP);i++){
                pop.push_back(newGeneration.at(i));
                fitness.push_back(newGenerationFitness.at(i));
                //cout<< fitt<<endl;//+0.1*isValideGene(chromosome);
            }

            Population::triPopulationASC(pop ,fitness);
            //cout<<"Best Fitness : " <<fitness.at(0)<<endl;

            if(fitness.at(0)==BestFitness){
                pop.clear();
                fitness.clear();
                pop.push_back(bestChromosome);
                std::vector<std::vector<Course> > generatedChromosome ;
                double fitt;

                for(int i=0 ; i<MAX_SIZE_POP -1 ; i++){
                     generatedChromosome =Population::generateChromosome(courses);
                     pop.push_back(generatedChromosome);
                     fitt= fitnessChromosome(generatedChromosome);
                     fitness.push_back(fitt);
                }
            }

            bestChromosome = pop.at(0);
            cout<<"### Fitness :"<< fitness.at(0)<<endl;//+0.1*isValideGene(chromosome);
            printChromosome(bestChromosome);
            cout<<"isValide Chromosome : " << isValideChromosome(bestChromosome)<<endl;

            //if (getStable_Fitness_limit_rounds()==9 ) break;
            if (getStable_Fitness_limit_rounds()>3 && isValideChromosome(bestChromosome)) break;

            if(fitness.at(0)==getMemorized_Fitness()) Population::setStable_Fitness_limit_rounds(getStable_Fitness_limit_rounds()+1);
                else
            {
                setMemorized_Fitness(fitness.at(0)); setStable_Fitness_limit_rounds(1);
            }



	}

	return pop;

}





void Population::swapChromosome( std::vector<std::vector<std::vector<Course> > > & pop,std::vector<double> & fitness , int i ,int j){
    std::vector<std::vector<Course> > temp_Chromosome = pop.at(i);
    double temp_Fitness = fitness.at(i);

    pop.at(i) = pop.at(j);
    fitness.at(i)=fitness.at(j);

    pop.at(j)=temp_Chromosome;
    fitness.at(j)=temp_Fitness;

}

int Population::getMinFitnessIndice (std::vector<std::vector<std::vector<Course> > > & pop,std::vector<double> & fitness,int i , int j ){
    int min_indice = i;
    for(int k=i+1 ; k<=j ; k++){
        if(fitness.at(k)<fitness.at(min_indice))
            min_indice = k;
    }

    return min_indice;

}


int Population::getMaxFitnessIndice (std::vector<std::vector<std::vector<Course> > > & pop,std::vector<double> & fitness,int i , int j ){
    int max_indice = i;
    for(int k=i+1 ; k<=j ; k++){
        if(fitness.at(k)>fitness.at(max_indice))
            max_indice = k;
    }

    return max_indice;
}



void Population::triPopulationASC(std::vector<std::vector<std::vector<Course> > > & pop,std::vector<double> & fitness){
    int indice_max;
    //cout <<" In TriPopulationASC :"<<endl;
    for(int i=pop.size()-1;i>=0;i--){
        indice_max= getMaxFitnessIndice(pop,fitness ,0,i);
        //cout<<"i= "<<i<<" Min indice est : " << indice_max << ", " << fitness.at(indice_max)<<endl;
        swapChromosome(pop,fitness, i,indice_max);
    }
}

void Population::triPopulationDESC(std::vector<std::vector<std::vector<Course> > > & pop,std::vector<double> & fitness){
    int indice_min;
    //cout <<" In TriPopulationDESC :"<<endl;
    for(int i=pop.size()-1;i>=0;i--){
        indice_min= getMinFitnessIndice(pop , fitness , 0,i);
        //cout<<"i= "<<i<<" Min indice est : " << indice_min << ", " << fitness.at(indice_min)<<endl;
        swapChromosome(pop , fitness , i,indice_min);
    }
}


