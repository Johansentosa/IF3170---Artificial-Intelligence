//GA.h
//Genetic Algorithm Class
#include "GA.h"

GeneticAlgorithm::GeneticAlgorithm(SchedCSP csp):csp(csp) {
}

void GeneticAlgorithm::initializePopulation(){
	for (int i = 0; i < GeneticAlgorithm::POPULATION; ++i)
	{
		vector<int> tmp = csp.getRandomIndex();
		population.push_back(tmp);
		int conflict = csp.countConflicts();
		conflictCache.push_back(conflict);
		rank.insert(make_pair(conflict, i));
	}
}

void GeneticAlgorithm::applyBestCandidate() {
	set<pair<int, int>>::iterator it = rank.begin();
	csp.applyIndex(population[it->second]);
}

void GeneticAlgorithm::printRank() {
	for (std::set<pair<int,int>>::iterator i = rank.begin(); i != rank.end(); ++i)
	{
		pair<int, int> element = *i;
		printf("%d", element.first);
	}
	printf("\n");
}

int GeneticAlgorithm::getLeastConflicts() {
	set<pair<int, int>>::iterator it = rank.begin();
	return it->first;
}

void GeneticAlgorithm::updatePopulationConflict(int i) {
	int newConflict = csp.countConflicts();
	rank.erase(make_pair(conflictCache[i], i));
	rank.insert(make_pair(newConflict, i));
	conflictCache[i] = newConflict;
}

pair<int, int> GeneticAlgorithm::selectChromosomePair() {
	//
	int courseSize = csp.getCourseSize();
	int a = rand() % (courseSize);
	int b = rand() % (courseSize - a + 1);
	a += GeneticAlgorithm::ELITE_POPULATION;
	b += GeneticAlgorithm::ELITE_POPULATION;
	return make_pair(a, b);
}

void GeneticAlgorithm::crossover(pair<int,int> p) {
	//Uniform crossover
	int courseSize = csp.getCourseSize();
	int popA = p.first;
	int popB = p.second;
	for (int i = 0; i < courseSize; ++i)
	{
		double r;
		r = (double)rand() / RAND_MAX; // probability type random, 0 sampe 1
		if (r < GeneticAlgorithm::CROSSOVER_RATIO) {
			swap(population[popA][i], population[popB][i]);
		}
	}
	csp.applyIndex(population[popA]);
	updatePopulationConflict(popA);
	csp.applyIndex(population[popB]);
	updatePopulationConflict(popB);
}

void GeneticAlgorithm::mutate(int i) {
	//mutate one of the course
	csp.applyIndex(population[i]);
	int courseSize = csp.getCourseSize();
	csp.initSingleVar(rand() % courseSize);
	updatePopulationConflict(i);
}

SchedCSP* GeneticAlgorithm::getCSPSolution() {
	initializePopulation();
	for (int i = 0; i < GeneticAlgorithm::GENERATION; ++i)
	{
		// if (getLeastConflicts() == 0)
		// {
		// 	break;
		// }
		printRank();
		pair<int, int> p = selectChromosomePair();
		crossover(p);
		double r;
		r = (double)rand() / RAND_MAX; // probability type random, 0 sampe 1
		if (r < GeneticAlgorithm::MUTATION_PROBABILITY) {
			mutate(p.first);
		}
		r = (double)rand() / RAND_MAX; // probability type random, 0 sampe 1
		if (r < GeneticAlgorithm::MUTATION_PROBABILITY) {
			mutate(p.second);
		}
	}
	applyBestCandidate();
	return &csp;
}