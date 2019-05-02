#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm() 
{
}

GeneticAlgorithm::GeneticAlgorithm(int t_populationsize, int t_mutationrate, int t_crossoverchance, Graph &t_graph) :
	m_populationsize(t_populationsize),
	m_mutationrate(t_mutationrate),
	m_crossoverchance(t_crossoverchance),
	m_graph(t_graph),
	m_currentgeneration(0),
	m_bestevergeneration(0)
{
	initpopulation();
	calculateroutelength();
	m_bestincurrentgeneration = m_population[0];
	m_bestever = m_population[0];
	for (int i = 0; i < t_populationsize; ++i) {
		for (int j = i; j < t_populationsize; ++j) {
			m_roulette.push_back(i);
		}
	}
}


GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::initpopulation()
{
	route temp;
	temp.DNA = m_graph.getAllIDs();
	for (int i = 0; i < m_populationsize; ++i) {
		m_population.push_back(temp);
		std::random_shuffle(m_population.back().DNA.begin(), m_population.back().DNA.end());
	}
}

void GeneticAlgorithm::calculateroutelength()
{
	for (size_t i = 0; i < m_population.size(); ++i) {
		float routelength = 0;
		for (size_t j = 0; j < m_population[0].DNA.length(); ++j) {
			int next = (j + 1) % m_population[0].DNA.length();
			float xdiff = m_graph.getNode(m_population[i].DNA[j])->getPosition().x - m_graph.getNode(m_population[i].DNA[next])->getPosition().x;
			float ydiff = m_graph.getNode(m_population[i].DNA[j])->getPosition().y - m_graph.getNode(m_population[i].DNA[next])->getPosition().y;
			routelength += sqrt(xdiff*xdiff + ydiff * ydiff);
		}
		m_population[i].routelength = routelength;
	}
	std::sort(m_population.begin(), m_population.end(), [](route x, route y) {return x.routelength < y.routelength; });
}

void GeneticAlgorithm::newgeneration()
{
	std::vector<route> oldpopulation = m_population;
	m_population.clear();
	m_population.push_back(oldpopulation[0]);
	while (m_population.size() < m_populationsize) {
		crossover(oldpopulation[pickparent()], oldpopulation[pickparent()]);
	}
	calculateroutelength();
	m_bestincurrentgeneration = m_population[1];
	if (m_population[0].routelength < m_bestever.routelength) {
		m_bestever = m_population[0];
		m_bestevergeneration = m_currentgeneration;
	}
	m_population.resize(m_populationsize);
	++m_currentgeneration;
	
}

int GeneticAlgorithm::getCurrentGeneration()
{
	return m_currentgeneration;
}

route GeneticAlgorithm::getBestInCurrentGeneration()
{
	return m_bestincurrentgeneration;
}

route GeneticAlgorithm::getBestEver()
{
	return m_bestever;
}

int GeneticAlgorithm::getBestEverGeneration()
{
	return m_bestevergeneration;
}

int GeneticAlgorithm::pickparent()
{
	int random = rand() % m_roulette.size();
	return m_roulette[random];
}

void GeneticAlgorithm::crossover(route p1, route p2)
{
	auto constains = [](route x, short y) {
		for (int i = 0; i < x.DNA.length(); ++i) {
			if (x.DNA[i] == y)
				return true;
		}
		return false;
	};
	if (m_crossoverchance >= rand() % 100 + 1) {
		route child1;
		child1.DNA = "";
		int pos = rand() % (p1.DNA.length() / 2);
		for (int i = pos; i < pos + p1.DNA.length() / 2; ++i) {
			child1.DNA += p1.DNA[i];
		}
		for (int i = 0; i < p2.DNA.length(); ++i) {
			if (!constains(child1, p2.DNA[i])) {
				child1.DNA += p2.DNA[i];
			}
		}
		route child2;
		child2.DNA = "";
		pos = rand() % (p2.DNA.length() / 2);
		for (int i = pos; i < pos + p2.DNA.length() / 2; ++i) {
			child2.DNA += p2.DNA[i];
		}
		for (int i = 0; i < p1.DNA.length(); ++i) {
			if (!constains(child2, p1.DNA[i])) {
				child2.DNA += p1.DNA[i];
			}
		}
		if (m_mutationrate >= rand() % 100 + 1) {
			pos = rand() % child1.DNA.length();
			int nextpos = (pos + 1) % child1.DNA.length();
			std::swap(child1.DNA[pos], child1.DNA[nextpos]);
			pos = rand() % child1.DNA.length();
			nextpos = (pos + 1) % child1.DNA.length();
			std::swap(child2.DNA[pos], child2.DNA[nextpos]);
		}
		m_population.push_back(child1);
		m_population.push_back(child2);
	}
}