//GA.h
//Genetic Algorithm Class
#ifndef GA
#define GA

#include "SchedCSP.h"
#include <set>

class GeneticAlgorithm{
  public:
    const static int POPULATION = 100;
    const static int GENERATION = 1000;
    const static int ELITE_POPULATION = POPULATION/5;
    const static int EXTRA_POPULATION = POPULATION;
    constexpr const static double MUTATION_PROBABILITY = 0.05;
    constexpr const static double CROSSOVER_RATIO = 0.5;



    GeneticAlgorithm(SchedCSP csp);
    SchedCSP* getCSPSolution();
    
  private:
    SchedCSP csp;
    vector<vector<int>> population;
    set<pair<int, int>> rank;
    vector<int> conflictCache;

    void initializePopulation();
    void applyBestCandidate();
    void printRank();
    void updatePopulationConflict(int);
    int getLeastConflicts();
    pair<int, int> selectChromosomePair();
    void crossover(pair<int,int>);
    void mutate(int);
    void cullPopulation();
    void rerankPopulation();
};
#endif