#pragma once
#include <SFML/Graphics.hpp>
#include "NewTile.h"
#include <iostream>
#include <vector>

class NewBoard
{
public:
	//member that must be called first
	void initBoard(sf::RenderWindow* window, float offsetX, float offsetY, float tileSize);
	void tileOccupied(int xOccupied, int yOccupied, bool occupied, bool team);

	void drawBoard();

	//setters
	inline const float setCoordX(int index) { return m_tileCoordX[index]; }
	inline const float setCoordY(int index) { return m_tileCoordY[index]; }
	inline auto getOccupied(int xIndex, int yIndex) { return m_occupied[xIndex][yIndex]; }
	inline auto getTeam(int xIndex, int yIndex) { return m_team[xIndex][yIndex]; }

private:
	sf::RenderWindow* m_window;
	NewTile m_tile[8][8];

	//private functions exclusive to board :3
	void initBoardCoords();

	//parameters that the user can change
	float m_offsetX;
	float m_offsetY;
	float m_tileSize;

	//parameters that can't change :)
	std::vector <float> m_vecCoordY;//stores the x values 
	std::vector <float> m_vecCoordX;//stores the coordinates in a matrix making the 'y' portion
	bool m_occupied[8][8];
	float m_tileCoordY[8];
	float m_tileCoordX[8];
	bool m_tileSelected[8][8];
	//tile index for tile selected
	int m_ySelIndex = 0;
	int m_xSelIndex = 0;

	//so the board knows which team occupies it where
	bool m_team[8][8];
};

