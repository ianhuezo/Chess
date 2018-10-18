#include "NewBoard.h"


void NewBoard::initBoard(sf::RenderWindow * window, float offsetX, float offsetY, float tileSize)
{
	m_window = window;
	m_offsetX = offsetX;
	m_offsetY = offsetY;
	m_tileSize = tileSize;

	bool tileColor = 0;

	for (unsigned int i = 0; i < 8; i++)
	{
		for (unsigned int j = 0; j < 8; j++)
		{
			m_tile[i][j].initTile(m_window, tileSize, tileColor);
			m_occupied[i][j] = false;
			tileColor = !tileColor;
			if (j == 7)
			{
				tileColor = !tileColor;
			}
		}
	}
	initBoardCoords();
}

void NewBoard::tileOccupied(int xOccupied, int yOccupied, bool occupied, bool team)
{
	//sets whether the tile is occupied by unit or not
	m_occupied[xOccupied][yOccupied] = occupied;
	m_team[xOccupied][yOccupied] = team;
}



void NewBoard::initBoardCoords()
{
	float yCount = 0;
	float xCount = 0;

	for (unsigned int i = 0; i < 8; i++)
	{
		m_tileCoordY[i] = m_offsetY + yCount;
		for (unsigned int j = 0; j < 8; j++)
		{
			m_tileCoordX[j] = m_offsetX + xCount;
			m_vecCoordX.push_back(m_tileCoordX[j]);//create 64 spaces for x and y vector coordinates to getter later
			m_vecCoordX.push_back(m_offsetY+ yCount);
			xCount += 50;//spacing between tiles
			if (j == 7)
			{
				xCount = 0;
			}
		}
		yCount += 50;//spacing between tiles
	}
}

void NewBoard::drawBoard()
{
	for (unsigned int i = 0; i < 8; i++)
	{
		for (unsigned int j = 0; j < 8; j++)
		{
			m_tile[i][j].drawTile(m_tileCoordX[j], m_tileCoordY[i]);
		}
	}
}
