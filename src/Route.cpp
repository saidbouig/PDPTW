#include "Route.h"

Route::Route()
{
    //ctor
}

Route::~Route()
{
    //dtor
}


std::vector<std::vector<Course> > Route::crossOverChromosome(std::vector<std::vector<Course> >  dad, std::vector<std::vector<Course> > mum) {

	int min = (dad.size() >= mum.size()) ? mum.size() : dad.size();
	int max = (dad.size() <= mum.size()) ? mum.size() : dad.size();
	//Resulted Chromosome
	std::vector<std::vector<Course> > child;

	//Randome parapport à la taille du chromosome a
	//srand(time(NULL));

	//randomint has value between 0 and min-1
	int randomint = rand() % min + 1;

	//copying the 1st half of a into c
	std::cout << "Before\nn";

	for (int i = 0; i <= randomint; i++) {
		std::vector<Course> tmp(dad.at(i));
		child.push_back(tmp);
	}
	std::cout << "After the first\n";
	for (int i = randomint + 1; i < max; i++) {
		std::vector<Course> tmp(mum.at(i));
		child.push_back(tmp);
	}
	cout << "CrossOver chromosome :" << endl;
	cout << "mid ind : " <<randomint << endl;
	return child;


}


std::vector<std::vector<Course> > Course::mutateChromosome(std::vector<std::vector<Course> > chromosome) {
	//srand(time(NULL));
	std::vector<std::vector<Course> > mutatedChromosome = chromosome;

	//Choosing two random vehicules, from the chromosome

	int tournee1 = (rand() % chromosome.size()) ;
	int tournee2 = (rand() % chromosome.size()) ;
	int course1, course2;

	//Choosing a random node -might be a pickup or a delivery one-, other than the depot
	do {
		course1 = (rand() % chromosome.at(tournee1).size()-1) + 1;

	} while (!course1 );
	//Same thing, choosing a random node
	do {

		course2 = (rand() % chromosome.at(tournee2).size()-1) + 1;
	} while (!course2);

	cout << "Mutate chromosome :" << endl;
	cout << "Tournée : " << tournee1 << " Course : " << course1 << " With Tournée : " << tournee2 << " Course :" << course2 << endl;
	Course tmp = mutatedChromosome.at(tournee1).at(course1);
	mutatedChromosome.at(tournee1).at(course1) = mutatedChromosome.at(tournee2).at(course2);
	mutatedChromosome.at(tournee2).at(course2) = tmp;
	cout << "end mutate\n";

	return mutatedChromosome;
}



bool isValideGene(std::vector<Course> gene){
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

bool isValideChromosome(std::vector<std::vector<Course> > chromosome){
    for (int i=0;i<chromosome.size();i++)
    {
        if(! isValideGene(chromosome.at(i))) return false;
    }
    return true;
}

double costGene(std::vector<Course> gene){
    double cost=0;
    if(gene.size()==0 || gene.size()==1) return 0;

    for(int i=0; i<gene.size()-1;i++)
        cost+=gene.at(i).getDistance(gene.at(i+1));

    cost+=gene.at(gene.size()-1).getDistance(gene.at(0));
    return cost;
}

double costChromosome(std::vector<std::vector<Course> > chromosome){
    double cost=0;
    if(chromosome.size()==0) return 0;

    for(int i=0; i<chromosome.size();i++)
        cost+=costGene(chromosome.at(i));
    return cost;
}

int vehiculeNumber(std::vector<std::vector<Course> > chromosome){
    int _vehiculeNumber;
    for(int i=0 ; i<chromosome.size();i++)
        if(chromosome.at(i).size()>=2) _vehiculeNumber++;

    return _vehiculeNumber;
}
double fitnessChromosome( std::vector<std::vector<Course> > chromosome){
    return 0.5*costChromosome(chromosome) + 0.4*vehiculeNumber(chromosome);//+0.1*isValideGene(chromosome);

}


std::vector<std::vector<Course> > Course::generateChromosome(std::vector<Course> & courses)
{
	route chromosome, chromosome1;
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
		std::vector<Course> sorted(courses.begin()+1, courses.begin() + numberCourses + 1);
		sorted = courses.at(0).trierParDistance(sorted);
		/*Insert the first Pickup node, and it's according delivery one*/
		unsigned int cpt = 0;
		unsigned int rInt = (rand() % numberCourses -1)  + 1;
		//std::cout <<"rand :" <<rInt << endl;
		while(b && (cpt<=sorted.size()-1)){
			//std::cout << tmp.at(0).isCompatible(sorted.at(cpt)) << endl;
			if ((tmp.at(0).isCompatible(sorted.at(rInt)))&&(courses.at(sorted.at(rInt).getId()).getNumVehicule()==-1)) {
                cout<<"First "<< tmp.at(0).getId() << ", " << sorted.at(rInt).getId() <<": "<<sorted.at(rInt).isCompatible(tmp.at(0))<<endl;
				courses.at(sorted.at(rInt).getId()).setNumVehicule(numV);
				courses.at(sorted.at(rInt).getId() + numberCourses).setNumVehicule(numV);
				tmp.push_back(sorted.at(sorted.at(rInt).getId()));
				tmp.push_back(courses.at(sorted.at(rInt).getId() + numberCourses));
				//std::cout << "Setting the course IfOne" << sorted.at(rInt).getId() << " "  << endl;
				b = false;
			}
			cpt++;
		}
		/*In this loop, we sort the elements according to the distance of the last delivery node*/
		for (int k = 1; k < numberCourses; k++) {
			sorted = tmp.at(tmp.size() - 1).trierParDistance(sorted);
			if (sorted.at(k).isCompatible(tmp.at(tmp.size() - 1)) && (courses.at(sorted.at(k).getId()).getNumVehicule() == -1)) {
				std::cout<< "Loop "<< tmp.at(tmp.size() - 1).getId() << ", " << sorted.at(k).getId() <<": "<<sorted.at(k).isCompatible(tmp.at(tmp.size() - 1))<<endl;
				courses.at(sorted.at(k).getId()).setNumVehicule(numV);
				courses.at(sorted.at(k).getId() + numberCourses).setNumVehicule(numV);
				tmp.push_back(courses.at(sorted.at(k).getId()));
				tmp.push_back(courses.at(sorted.at(k).getId() + numberCourses));
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
    cout << "#Validité du Chromosome : " <<isValideChromosome(chromosome1)<<endl;
	return chromosome1;
	//return std::vector<std::vector<Course>>();
}
