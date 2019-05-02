#include "Graph.h"

Graph::Graph() :
	m_selectednode(nullptr),
	m_nodetexture(),
	m_graphbounds(20,20,800,680)
{
	m_nodetexture.loadFromFile("txt/Dot.png");
}


Graph::~Graph()
{
}

void Graph::AddNode(sf::Vector2f t_position)
{
	if (m_nodes.size() < 30) {
		m_nodes.push_back(Node(t_position,getFreeID(), m_nodetexture));
	}
}

void Graph::MoveNode(sf::Vector2f t_position)
{
	if (m_selectednode != nullptr && m_graphbounds.contains(t_position)) {
		m_selectednode->setPosition(t_position);
	}
}

void Graph::DeleteNode()
{
	for (size_t i = 0; i < m_nodes.size(); ++i) {
		if (m_nodes[i].getID() == m_selectednode->getID()) {
			m_nodes.erase(m_nodes.begin() + i);
		}
	}
}

void Graph::Draw(sf::RenderWindow &t_window)
{
	for (size_t i = 0; i < m_nodes.size(); ++i) {
		t_window.draw(m_nodes[i]);
	}
}

bool Graph::isNodeClicked(sf::Vector2f t_position)
{
	for (size_t i = 0; i < m_nodes.size(); ++i) {
		if (m_nodes[i].isClicked(t_position)) {
			m_selectednode = &m_nodes[i];
			return true;
		}
	}
	return false;
}

sf::FloatRect Graph::getBounds()
{
	return m_graphbounds;
}

void Graph::clearSelectedNode()
{
	m_selectednode = nullptr;
}

short Graph::getFreeID() {
	short ID = 'A';
	while (true) {
		bool founded = false;
		for (size_t i = 0; i < m_nodes.size(); ++i) {
			if (m_nodes[i].getID() == ID) {
				founded = true;
				break;
			}
		}
		if (founded) {
			++ID;
		}
		else {
			return ID;
		}
	}
}

Node *Graph::getNode(short t_id)
{
	for (size_t i = 0; i < m_nodes.size(); ++i) {
		if (m_nodes[i].getID() == t_id) {
			return &m_nodes[i];
		}
	}
	return nullptr;
}

size_t Graph::getNodesNumber()
{
	return m_nodes.size();
}

std::string Graph::getAllIDs()
{
	std::string temp;
	for (size_t i = 0; i < m_nodes.size(); ++i) {
		temp += m_nodes[i].getID();
	}
	return temp;
}