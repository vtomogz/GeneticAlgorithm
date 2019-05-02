#pragma once
#include <iostream>
#include "Graph.h"

struct route
{
	std::string DNA;
	float routelength;
};

class GeneticAlgorithm
{
private:
	int m_populationsize;
	int m_mutationrate;
	int m_crossoverchance;
	int m_currentgeneration;
	route m_bestincurrentgeneration;
	route m_bestever;
	int m_bestevergeneration;
	Graph m_graph;
	std::vector<route> m_population;
	void initpopulation();
	void calculateroutelength();
	std::vector<int> m_roulette;
	int pickparent();
	void crossover(route p1,route p2);
public:
	GeneticAlgorithm();
	GeneticAlgorithm(int t_populationsize,int t_mutationrate,int t_crossoverchance,Graph &t_graph);
	~GeneticAlgorithm();
	void newgeneration();
	int getCurrentGeneration();
	route getBestInCurrentGeneration();
	route getBestEver();
	int getBestEverGeneration();
};

