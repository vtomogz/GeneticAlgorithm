#include "Node.h"

Node::Node(sf::Vector2f t_position,short t_id, sf::Texture &t_texture) :
	m_id(t_id),
	m_node()
{
	m_node.setTexture(t_texture);
	m_node.setOrigin(14, 9);
	m_node.setPosition(t_position);
}

Node::~Node()
{
}

void Node::setPosition(sf::Vector2f t_position)
{
	m_node.setPosition(t_position);
}

short Node::getID()
{
	return m_id;
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_node);
}

bool Node::isClicked(sf::Vector2f t_position)
{
	float xdiff = t_position.x - m_node.getPosition().x;
	float ydiff = t_position.y - m_node.getPosition().y;
	return sqrt(xdiff * xdiff + ydiff * ydiff) <= 10;
}

sf::Vector2f Node::getPosition()
{
	return m_node.getPosition();
}