#pragma once
#include <SFML/Graphics.hpp>

class Node : public sf::Drawable
{
private:
	short m_id;
	sf::Sprite m_node;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Node(sf::Vector2f t_position,short t_id, sf::Texture &t_texture);
	~Node();
	void setPosition(sf::Vector2f t_position);
	short getID();
	bool isClicked(sf::Vector2f t_position);
	sf::Vector2f getPosition();
};

