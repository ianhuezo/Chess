#pragma once
#include "SFML/Graphics.hpp"
#include <string>

//the class for all units 
class Unit
{
public:

	Unit();
	//setter
	inline const auto getTexture() { return m_texture; }
	void setTexture(sf::Texture texture);
	void loadTexture(std::string& filePath);
	void initUnit(sf::RenderWindow* window ,float xPosition, float yPosition, float tileDimension);
	void drawUnit();
	void moveUnit();//move the unit in some way
	void setPosition(float xPosition, float yPosition);
	void isClicked();//unit is clicked
	void setTilePosition(int xtile, int ytile);
	
	void unitType(std::string& unitName, bool unitTeam);
	inline const auto getPositionX() { return m_xPosition; }
	inline const auto getPositionY() { return m_yPosition; }
	inline const auto getUnitSelected() { return m_unitSelected; }
	inline const auto getClick() { return m_isClicked; }
	inline const auto getName() { return m_unitName; }
	inline const auto getTeam() { return m_unitTeam; }
	inline const auto getIndex() { return m_unitNumber; }
	inline const auto getTileX() { return m_xTile; }
	inline const auto getTileY() { return m_yTile; }


private:
	sf::RenderWindow* m_window;
	sf::Texture m_texture;
	sf::Sprite m_sprite;


	//checking to see if the unit is clicked
	bool m_isClicked = 0;
	bool m_inArea = 0;
	bool m_unitSelected = 0;
	bool m_validMovement = false;



	//used to check if the unit is within the click area
	int m_mouseCoordX;
	int m_mouseCoordY;
	int m_unitNumber;

	//unit specific values
	std::string m_unitName = "";
	bool m_unitTeam = 0;

	//position of the unit on the board
	float m_xPosition;
	float m_yPosition;
	float m_oldPositionX;
	float m_oldPositionY;
	float m_tileDimension;

	//unit relative to tile position, will return the xy index of the current unit's position
	float m_xTile;
	float m_yTile;
};

