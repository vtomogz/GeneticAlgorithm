#include "Window.h"



Window::Window() :
	m_screenheight(720),
	m_screenwidth(1280),
	m_background(),
	m_backgroundtexture(),
	m_slidertexture(),
	m_appname("Shortest Path Finding with Genetic Algorithm!"),
	m_window(sf::VideoMode(1280, 720), "Shortest Path Finding with Genetic Algorithm!", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(0, 0, 8)),
	m_slidersbouns(840,153,420,180),
	m_clickedslider(nullptr),
	m_populationslider(),
	m_mutationslider(),
	m_stepintervalslider(),
	m_crossoverslider(),
	m_starttexture(),
	m_stoptexture(),
	m_tooglebutton(),
	m_graph(),
	m_font(),
	m_calculating(false)
{
	m_backgroundtexture.loadFromFile("txt/Background.png");
	m_slidertexture.loadFromFile("txt/Dot.png");
	m_background.setTexture(m_backgroundtexture);
	m_font.loadFromFile("txt/abel.ttf");
	m_populationslider = Slider(sf::Vector2f(850, 163), 400, 10, 100, m_slidertexture, m_font);
	m_mutationslider = Slider(sf::Vector2f(850, 215), 400, 1, 90, m_slidertexture, m_font, percentage);
	m_stepintervalslider = Slider(sf::Vector2f(850, 267), 400, 0, 1000, m_slidertexture, m_font, latency);
	m_crossoverslider = Slider(sf::Vector2f(850, 319), 400, 1, 99, m_slidertexture, m_font, percentage);
	m_starttexture.loadFromFile("txt/Start.png");
	m_stoptexture.loadFromFile("txt/Stop.png");
	m_tooglebutton.setTexture(m_starttexture);
	m_tooglebutton.setPosition(954, 383);
	m_generation.setFont(m_font);
	m_generation.setCharacterSize(24);
	m_generation.setFillColor(sf::Color::Black);
	m_shortestdistance.setFont(m_font);
	m_shortestdistance.setCharacterSize(24);
	m_shortestdistance.setFillColor(sf::Color::Black);
	m_shortestever.setFont(m_font);
	m_shortestever.setCharacterSize(24);
	m_shortestever.setFillColor(sf::Color::Black);
	m_shortestevergeneration.setFont(m_font);
	m_shortestevergeneration.setCharacterSize(24);
	m_shortestevergeneration.setFillColor(sf::Color::Black);
}


Window::~Window()
{
}

void Window::Start() {
	bool isLeftMouseButtonHeld = false;
	while (m_window.isOpen()) {
		auto start = std::chrono::steady_clock::now();
		sf::Event event;
		while (m_window.pollEvent(event)) {
			sf::Vector2f mouseposition = sf::Vector2f(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
			if (event.type == sf::Event::Closed) {
				m_window.close();
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					isLeftMouseButtonHeld = false;
					m_clickedslider = nullptr;
					m_graph.clearSelectedNode();
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (m_calculating) {
						if (m_tooglebutton.getGlobalBounds().contains(mouseposition)) {
							m_calculating = false;
							m_tooglebutton.setTexture(m_starttexture);
							m_path = sf::VertexArray(sf::Lines, m_graph.getNodesNumber() * 2);
							for (size_t i = 0; i < m_ga.getBestEver().DNA.length(); ++i) {
								int next = (i + 1) % m_ga.getBestEver().DNA.length();
								m_path[i * 2].position = m_graph.getNode(m_ga.getBestEver().DNA[i])->getPosition();
								m_path[i * 2].color = sf::Color::Red;
								m_path[i * 2 + 1].position = m_graph.getNode(m_ga.getBestEver().DNA[next])->getPosition();
								m_path[i * 2 + 1].color = sf::Color::Red;
							}
						}
					}
					else if (m_slidersbouns.contains(mouseposition)) {
						if (m_populationslider.isClicked(mouseposition)) {
							isLeftMouseButtonHeld = true;
							m_clickedslider = &m_populationslider;
						}
						else if (m_mutationslider.isClicked(mouseposition)) {
							isLeftMouseButtonHeld = true;
							m_clickedslider = &m_mutationslider;
						}
						else if (m_stepintervalslider.isClicked(mouseposition)) {
							isLeftMouseButtonHeld = true;
							m_clickedslider = &m_stepintervalslider;
						}
						else if (m_crossoverslider.isClicked(mouseposition)) {
							isLeftMouseButtonHeld = true;
							m_clickedslider = &m_crossoverslider;
						}
					}
					else if (m_graph.getBounds().contains(mouseposition)) {
						if (m_graph.isNodeClicked(mouseposition)) {
							isLeftMouseButtonHeld = true;
						}
						else {
							m_graph.AddNode(mouseposition);
							m_path = sf::VertexArray();
						}
					}
					else if (m_tooglebutton.getGlobalBounds().contains(mouseposition)) {
						if (m_graph.getAllIDs().length() > 3) {
							m_calculating = true;
							m_ga = GeneticAlgorithm(m_populationslider.GetValue(), m_mutationslider.GetValue(), m_crossoverslider.GetValue(), m_graph);
							m_tooglebutton.setTexture(m_stoptexture);
						}
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					if (m_graph.getBounds().contains(mouseposition)) {
						if (!m_calculating) {
							if (m_graph.isNodeClicked(mouseposition)) {
								m_graph.DeleteNode();
								m_path = sf::VertexArray();
							}
						}
					}
				}
			}
			if (isLeftMouseButtonHeld) {
				if (m_clickedslider != nullptr) {
					m_clickedslider->SetValue(mouseposition.x);
				}
				m_graph.MoveNode(mouseposition);
				m_path = sf::VertexArray();
			}
		}
		if (m_calculating) {
			m_generation.setString(std::to_string(m_ga.getCurrentGeneration()));
			m_generation.setOrigin(m_generation.getGlobalBounds().width, 0);
			m_generation.setPosition(1250, 495);
			m_shortestdistance.setString(std::to_string((int)m_ga.getBestInCurrentGeneration().routelength));
			m_shortestdistance.setOrigin(m_shortestdistance.getGlobalBounds().width, 0);
			m_shortestdistance.setPosition(1250, 542);
			m_shortestever.setString(std::to_string((int)m_ga.getBestEver().routelength));
			m_shortestever.setOrigin(m_shortestever.getGlobalBounds().width, 0);
			m_shortestever.setPosition(1250, 589);
			m_shortestevergeneration.setString(std::to_string(m_ga.getBestEverGeneration()));
			m_shortestevergeneration.setOrigin(m_shortestevergeneration.getGlobalBounds().width, 0);
			m_shortestevergeneration.setPosition(1250, 636);
			m_path = sf::VertexArray(sf::Lines, m_graph.getNodesNumber() * 2);
			for (size_t i = 0; i < m_ga.getBestInCurrentGeneration().DNA.length(); ++i) {
				int next = (i + 1) % m_ga.getBestInCurrentGeneration().DNA.length();
				m_path[i * 2].position = m_graph.getNode(m_ga.getBestInCurrentGeneration().DNA[i])->getPosition();
				m_path[i * 2].color = sf::Color::Red;
				m_path[i * 2 + 1].position = m_graph.getNode(m_ga.getBestInCurrentGeneration().DNA[next])->getPosition();
				m_path[i * 2 + 1].color = sf::Color::Red;
			}
			m_ga.newgeneration();
		}
		m_window.draw(m_background);
		m_window.draw(m_path);
		m_graph.Draw(m_window);
		m_window.draw(m_populationslider);
		m_window.draw(m_mutationslider);
		m_window.draw(m_stepintervalslider);
		m_window.draw(m_crossoverslider);
		m_window.draw(m_tooglebutton);
		m_window.draw(m_generation);
		m_window.draw(m_shortestdistance);
		m_window.draw(m_shortestever);
		m_window.draw(m_shortestevergeneration);
		m_window.display();
		if(m_calculating)
			std::this_thread::sleep_until(start + std::chrono::milliseconds(m_stepintervalslider.GetValue()));
	}
}
