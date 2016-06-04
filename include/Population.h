#ifndef POPULATION_H
#define POPULATION_H
#include<stdio.h>
#include<vector>
#include"Course.h"
#define MAX_SIZE_POP 10
#define ITERATIONS 1000

class Population
{
static double memorized_fitness;
    static int stable_fitness_limit_rounds ;
    public:

        static double getMemorized_Fitness();//{ return memorized_fitness;}
        static int getStable_Fitness_limit_rounds() ;//{ return stable_fitness_limit_rounds;}
        static void setMemorized_Fitness(double fitness);//{ memorized_fitness = fitness; }
        static void setStable_Fitness_limit_rounds( int fitness);//{ stable_fitness_limit_rounds= fitness;}

        int countPenality(std::vector<std::vector<Course> > chromosome);
        std::vector<std::vector<std::vector<Course> > > pop;
        std::vector<double> fitness;
        double fitnessTot;
        std::vector<std::vector<std::vector<Course> > > generatePopulation(std::vector<Course> &courses);
        std::vector<std::vector<Course> > crossOverChromosome(std::vector<std::vector<Course> >  dad, std::vector<std::vector<Course> > mum);
        std::vector<std::vector<Course> > mutateChromosome(std::vector<std::vector<Course> > chromosome) ;
        bool isValideGene(std::vector<Course> gene);
        bool isValideChromosome(std::vector<std::vector<Course> > chromosome);
        std::vector<std::vector<Course> > generateChromosome(std::vector<Course> & courses);
        bool ChromosomeEquals(std::vector<std::vector<Course> > a , std::vector<std::vector<Course> > b);

        double fitnessChromosome( std::vector<std::vector<Course> > chromosome);
        double costChromosome(std::vector<std::vector<Course> > chromosome);
        int vehiculeNumber(std::vector<std::vector<Course> > chromosome);
        double costGene(std::vector<Course> gene);
        void swapChromosome(int i ,int j);
        void swapChromosome( std::vector<std::vector<std::vector<Course> > > & pop,std::vector<double> & fitness , int i ,int j);
        void printChromosome(std::vector<std::vector<Course> > a) ;

        void triPopulation();
        void triPopulationDESC(std::vector<std::vector<std::vector<Course> > > & pop,std::vector<double> & fitness);
        void triPopulationASC(std::vector<std::vector<std::vector<Course> > > & pop,std::vector<double> & fitness);

        int getMinFitnessIndice (int i , int j , double & min_fitness);
        int getMinFitnessIndice (std::vector<std::vector<std::vector<Course> > > & pop,std::vector<double> & fitness,int i , int j );

        int getMaxFitnessIndice (int i , int j , double & max_fitness);
        int getMaxFitnessIndice (std::vector<std::vector<std::vector<Course> > > & pop,std::vector<double> & fitness,int i , int j );


        Population();
        virtual ~Population();
    protected:
    private:
};



#endif // POPULATION_H
