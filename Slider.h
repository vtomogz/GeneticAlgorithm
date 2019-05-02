#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>

enum slidertype {
	integer  = 0,
	percentage = 1,
	latency = 2
};

class Slider : public sf::Drawable
{
private:
	sf::Sprite m_slider;
	sf::Vector2f m_initposition;
	sf::Text m_text;
	slidertype m_type;
	float m_width;
	int m_value;
	int m_minvalue;
	int m_maxvalue;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Slider(sf::Vector2f t_initposition, float t_width, float t_minvalue, float t_maxvalue, sf::Texture &t_texture, sf::Font &t_font, slidertype t_type = integer);
	Slider();
	~Slider();
public:
	void SetValue(int t_position);
	bool isClicked(sf::Vector2f t_mouseposition);
	int GetValue();
};

