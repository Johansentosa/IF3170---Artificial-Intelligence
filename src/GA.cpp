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
	vector<int> newPopA, newPopB;
	for (int i = 0; i < courseSize; ++i)
	{
		double r;
		r = (double)rand() / RAND_MAX; // probability type random, 0 sampe 1
		if (r < GeneticAlgorithm::CROSSOVER_RATIO) {
			newPopA.push_back(population[popA][3*i+0]);
			newPopA.push_back(population[popA][3*i+1]);
			newPopA.push_back(population[popA][3*i+2]);

			newPopB.push_back(population[popB][3*i+0]);
			newPopB.push_back(population[popB][3*i+1]);
			newPopB.push_back(population[popB][3*i+2]);
		} else {
			newPopA.push_back(population[popB][3*i+0]);
			newPopA.push_back(population[popB][3*i+1]);
			newPopA.push_back(population[popB][3*i+2]);

			newPopB.push_back(population[popA][3*i+0]);
			newPopB.push_back(population[popA][3*i+1]);
			newPopB.push_back(population[popA][3*i+2]);
		}
	}
	int conflict;
	assert(csp.testIndex(newPopA) && csp.testIndex(newPopB));

	//Add crossover population
	csp.applyIndex(newPopA);
	population.push_back(newPopA);
	conflict = csp.countConflicts();
	conflictCache.push_back(conflict);
	rank.insert(make_pair(conflict, population.size() - 1));

	csp.applyIndex(newPopB);
	population.push_back(newPopB);
	conflict = csp.countConflicts();
	conflictCache.push_back(conflict);
	rank.insert(make_pair(conflict, population.size() - 1));
}

void GeneticAlgorithm::mutate(int i) {
	//mutate one of the course
	csp.applyIndex(population[i]);
	int courseSize = csp.getCourseSize();
	csp.initSingleVar(rand() % courseSize);
	updatePopulationConflict(i);
}

void GeneticAlgorithm::cullPopulation() {
	set<pair<int,int>>::iterator it = rank.end();
	vector<int> indexToCull;
	for (int i = 0; i < GeneticAlgorithm::EXTRA_POPULATION; ++i)
	{
		it--;
		int popIndex = it->second;
		indexToCull.push_back(popIndex);
	}
	sort(indexToCull.begin(), indexToCull.end());
	for (int i = 0; i < GeneticAlgorithm::EXTRA_POPULATION; ++i)
	{
		int popIndex = indexToCull[i];
		popIndex -= i;
		population.erase(population.begin() + popIndex);
		conflictCache.erase(conflictCache.begin() + popIndex);
	}
		
}

void GeneticAlgorithm::rerankPopulation() {
	set<pair<int,int>> newRank;
	for (int i = 0; i < GeneticAlgorithm::POPULATION; ++i)
	{
		csp.applyIndex(population[i]);
		int conflict = csp.countConflicts();
		conflictCache[i] = conflict;
		newRank.insert(make_pair(conflict, i));
	}
	rank = newRank;
}

SchedCSP* GeneticAlgorithm::getCSPSolution() {
	initializePopulation();
	for (int i = 0; i < GeneticAlgorithm::GENERATION; ++i)
	{
		printRank();
		// if (getLeastConflicts() == 0)
		// {
		// 	break;
		// }
		for (int i = 0; i < GeneticAlgorithm::EXTRA_POPULATION / 2; ++i)
		{
			pair<int, int> p = selectChromosomePair();
			crossover(p); // every crossover generate 2 pops
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
		cullPopulation();
		rerankPopulation();
	}
	applyBestCandidate();
	return &csp;
}