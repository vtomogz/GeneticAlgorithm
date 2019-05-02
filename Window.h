#pragma once
#include <SFML/Graphics.hpp>
#include "Slider.h"
#include "Graph.h"
#include "GeneticAlgorithm.h"
#include <chrono>
#include <thread>

class Window
{
private:
	sf::Font m_font;
	sf::RenderWindow m_window;
	sf::Texture m_backgroundtexture;
	sf::Texture m_slidertexture;
	sf::Texture m_starttexture;
	sf::Texture m_stoptexture;
	sf::Sprite m_tooglebutton;
	sf::Sprite m_background;
	sf::Text m_generation;
	sf::Text m_shortestdistance;
	sf::Text m_shortestever;
	sf::Text m_shortestevergeneration;
	int m_screenwidth;
	int m_screenheight;
	std::string m_appname;
	Slider m_populationslider;
	Slider m_mutationslider;
	Slider m_stepintervalslider;
	Slider m_crossoverslider;
	sf::FloatRect m_slidersbouns;
	Slider *m_clickedslider;
	Graph m_graph;
	bool m_calculating;
	GeneticAlgorithm m_ga;
	sf::VertexArray m_path;
public:
	Window();
	~Window();
	void Start();
};

