//GA.h
//Genetic Algorithm Class
#ifndef GA
#define GA

#include "SchedCSP.h"
#include <set>

class GeneticAlgorithm{
  public:
    const static int POPULATION = 100;
    const static int GENERATION = 100;
    const static int ELITE_POPULATION = POPULATION/20;
    constexpr const static double MUTATION_PROBABILITY = 0.05;


    GeneticAlgorithm(SchedCSP csp);
    SchedCSP* getCSPSolution();
    
  private:
    SchedCSP csp;
    vector<vector<int>> indexPool;
    set<pair<int, int>> rank;

    void initializePopulation();
    void applyBestCandidate();
    void printRank();
    int getLeastConflicts();
    pair<int, int> selectChromosomePair();
    void crossover(pair<int,int>);
    void mutate(int);
};
#endif