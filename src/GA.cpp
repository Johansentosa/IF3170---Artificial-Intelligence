//GA.h
//Genetic Algorithm Class
#include "GA.h"

GeneticAlgorithm::GeneticAlgorithm(SchedCSP csp):csp(csp) {
}

void GeneticAlgorithm::initializePopulation(){
	for (int i = 0; i < GeneticAlgorithm::POPULATION; ++i)
	{
		vector<int> tmp = csp.getRandomIndex();
		indexPool.push_back(tmp);
		rank.insert(make_pair(csp.countConflicts(), i));
	}
}

void GeneticAlgorithm::applyBestCandidate() {
	set<pair<int, int>>::iterator it = rank.begin();
	csp.applyIndex(indexPool[it->second]);
}

void GeneticAlgorithm::printRank() {
	for (std::set<pair<int,int>>::iterator i = rank.begin(); i != rank.end(); ++i)
	{
		pair<int, int> element = *i;
		printf("%d ", element.first);
	}
	printf("\n");
}

int GeneticAlgorithm::getLeastConflicts() {
	set<pair<int, int>>::iterator it = rank.begin();
	return it->first;
}

pair<int, int> GeneticAlgorithm::selectChromosomePair() {
	//
}

void GeneticAlgorithm::crossover(pair<int,int> p) {
	//
}

void GeneticAlgorithm::mutate(int i) {
	//
}

SchedCSP* GeneticAlgorithm::getCSPSolution() {
	initializePopulation();
	printRank();
	for (int i = 0; i < GeneticAlgorithm::GENERATION; ++i)
	{
		if (getLeastConflicts() == 0)
		{
			break;
		}
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