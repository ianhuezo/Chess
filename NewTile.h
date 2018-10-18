#pragma once
#include <SFML/Graphics.hpp>
class NewTile
{
public:
	void initTile(sf::RenderWindow* window, float tileDimension, bool selectTileColor);
	void setTileIndex(int index);
	void drawTile(float xPosition, float yPosition);
	void isTileSelected(bool tileSelected);

	//Getters
	inline const auto getWindow() { return &m_window; };
	inline const auto getTileDimension() { return m_tileDimension; }
	inline const auto getPositionX() { return m_xPosition; }
	inline const auto getPositionY() { return m_yPosition; }

private:
	void setTileColor(bool selectTileColor);//bool tileSelected

	sf::RectangleShape m_shape;
	sf::RenderWindow* m_window;
	bool m_tileSelected;

	unsigned int m_index;//index of the array element
	float m_xPosition;
	float m_yPosition;
	float m_tileDimension;
};

