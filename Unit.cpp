#include "Unit.h"
#include <iostream>

//constructor for class
Unit::Unit()
{
	m_validMovement = 1;
	m_unitSelected = 0;
}

//loads the texture via a filepath
void Unit::loadTexture(std::string& filePath)
{
	m_texture.loadFromFile(filePath);
	m_sprite.setTexture(m_texture);
}

//initializes the array to place units in a certain place
void Unit::initUnit(sf::RenderWindow* window, float xPosition, float yPosition, float tileDimension)
{
	m_xPosition = xPosition;
	m_yPosition = yPosition;
	m_window = window;
	m_tileDimension = tileDimension;
	m_sprite.setPosition(m_xPosition, m_yPosition);
}


//set the loaded texture to a sprite this works well if you want to reuse textures from loadtexture, just use the Getter!
void Unit::setTexture(sf::Texture texture)
{
	m_texture = texture;
	m_sprite.setTexture(m_texture);
}

//draw unit onto the screen
void Unit::drawUnit()
{
	m_window->draw(m_sprite);
}

//move the unit from a mouse click, the next members will check if this movement is valid
void Unit::moveUnit()
{
	m_mouseCoordX = sf::Mouse::getPosition(*m_window).x;
	m_mouseCoordY = sf::Mouse::getPosition(*m_window).y;
	m_inArea = m_mouseCoordX >= m_xPosition  && m_mouseCoordX <= m_xPosition + m_tileDimension && m_mouseCoordY >= m_yPosition  && m_mouseCoordY <= m_yPosition + m_tileDimension;
	if (m_inArea && m_isClicked && (m_unitSelected != 1))
	{
		m_unitSelected = 1;
		m_oldPositionX = m_xPosition;
		m_oldPositionY = m_yPosition;
		m_sprite.setPosition(m_mouseCoordX - 22.5, m_mouseCoordY - 22.5);

	}
	else if (m_unitSelected && m_isClicked && (!m_inArea || m_unitSelected))//could be outside of area
	{
		m_sprite.setPosition(m_mouseCoordX - 22.5, m_mouseCoordY - 22.5);

		m_xPosition = m_mouseCoordX - 22.5;
		m_yPosition = m_mouseCoordY - 22.5;
		//movement that is for the tile coordinates
	}

}

void Unit::setPosition(float xPosition, float yPosition)
{
	m_xPosition = xPosition;
	m_yPosition = yPosition;
	m_sprite.setPosition(m_xPosition, m_yPosition);
}

//is the unit clicked? if so check the position and set the position if it is valid
void Unit::isClicked()
{
	m_isClicked = !m_isClicked;
	if (m_isClicked == 0)
	{
		m_unitSelected = 0;
	}
}

void Unit::setTilePosition(int xTile, int yTile)
{
	m_xTile = xTile;
	m_yTile = yTile;
}

void Unit::unitType(std::string & unitName, bool unitTeam)
{
	m_unitName = unitName;
	m_unitTeam = unitTeam;
}
