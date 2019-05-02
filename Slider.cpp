#include "Slider.h"

Slider::Slider(sf::Vector2f t_initposition, float t_width, float t_minvalue, float t_maxvalue,sf::Texture &t_texture,sf::Font &t_font,slidertype t_type) :
	m_initposition(t_initposition),
	m_width(t_width),
	m_minvalue(t_minvalue),
	m_maxvalue(t_maxvalue),
	m_text(),
	m_slider(),
	m_type(t_type)
{
	m_value = m_minvalue;
	m_slider.setTexture(t_texture);
	m_slider.setOrigin(14, 9);
	m_slider.setPosition(m_initposition);
	m_text.setFont(t_font);
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color::Black);
	if (m_type == integer) {
		m_text.setString(std::to_string(m_minvalue));
	}
	else if (m_type == percentage) {
		m_text.setString(std::to_string(m_value) + " %");
	}
	else if (m_type == latency) {
		m_text.setString(std::to_string(m_value) + " ms");
	}
	m_text.setOrigin(m_text.getGlobalBounds().width, 0);
	m_text.setPosition(m_initposition.x + m_width, m_initposition.y - 39);
}

Slider::Slider()
{
}

Slider::~Slider()
{
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_slider);
	target.draw(m_text);
}

void Slider::SetValue(int t_position)
{
	if (t_position >= m_initposition.x&&t_position <= m_initposition.x + m_width) {
		float ratio = (t_position - m_initposition.x)/m_width;
		m_value = (m_maxvalue - m_minvalue)*ratio + m_minvalue;
		if (m_type == integer) {
			m_text.setString(std::to_string(m_value));
		}
		else if (m_type == percentage) {
			m_text.setString(std::to_string(m_value) + " %");
		}
		else if (m_type == latency) {
			m_text.setString(std::to_string(m_value)+" ms");
		}
		m_text.setOrigin(m_text.getGlobalBounds().width, 0);
		m_slider.setPosition(t_position, m_initposition.y);
	}
}

bool Slider::isClicked(sf::Vector2f t_position)
{
	float xdiff = t_position.x - m_slider.getPosition().x;
	float ydiff = t_position.y - m_slider.getPosition().y;
	return sqrt(xdiff*xdiff + ydiff * ydiff)<=10;
}

int Slider::GetValue()
{
	return m_value;
}
