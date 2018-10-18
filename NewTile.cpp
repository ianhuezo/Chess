#include "NewTile.h"

void NewTile::initTile(sf::RenderWindow * window, float tileDimension, bool selectTileColor)
{
	m_window = window;
	m_tileDimension = tileDimension;

	m_shape.setSize(sf::Vector2f(tileDimension, tileDimension));
	m_shape.setOutlineThickness(2.0f);
	m_shape.setOutlineColor(sf::Color());
	setTileColor(selectTileColor);
}

void NewTile::setTileIndex(int index)
{
	m_index = index;
}

void NewTile::drawTile(float xPosition, float yPosition)
{
	m_xPosition = xPosition;
	m_yPosition = yPosition;

	m_shape.setPosition(sf::Vector2f(xPosition, yPosition));

	m_window->draw(m_shape);
}



void NewTile::setTileColor(bool selectTileColor)
{
	if (selectTileColor == 1)
	{
		m_shape.setFillColor(sf::Color(165, 42, 42));
	}
	else
	{
		m_shape.setFillColor(sf::Color(245, 245, 220));
	}
}

void NewTile::isTileSelected(bool tileSelected)
{
	if (tileSelected == 0)
	{
		m_shape.setOutlineColor(sf::Color());
	}
	else
	{
		m_shape.setOutlineColor(sf::Color::Blue);
	}
}
