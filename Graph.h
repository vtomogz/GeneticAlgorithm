#pragma once
#include "Node.h"

class Graph
{
private:
	sf::Texture m_nodetexture;
	sf::FloatRect m_graphbounds;
	Node *m_selectednode;
	short getFreeID();
	std::vector<Node> m_nodes;
public:
	Graph();
	~Graph();
	void AddNode(sf::Vector2f t_position);
	void MoveNode(sf::Vector2f t_position);
	void DeleteNode();
	void Draw(sf::RenderWindow &t_window);
	sf::FloatRect getBounds();
	bool isNodeClicked(sf::Vector2f t_position);
	void clearSelectedNode();
	Node *getNode(short t_id);
	size_t getNodesNumber();
	std::string getAllIDs();
};

