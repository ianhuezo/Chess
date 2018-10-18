#include "GameSetup.h"

void GameSetup::init(sf::RenderWindow * window, float xPosition, float yPosition, float tileDimension)
{
	m_xBoard = xPosition;
	m_yBoard = yPosition;
	m_tileDimension = tileDimension;
	m_window = window;
	m_board.initBoard(window, xPosition, yPosition, tileDimension);
	m_count = 0;
	m_moveIndex = 0;
}

void GameSetup::initUnits()
{
	std::string unitsRed[6] = { "redrook", "redknight", "redbishop", "redqueen", "redking", "redpawn" };
	std::string unitsWhite[6] = { "whiterook", "whiteknight", "whitebishop", "whiteking","whitequeen", "whitepawn" };
	for (int i = 0; i < 32; i++)
	{
		loadUnitTextures(unitsRed, unitsWhite, i);
	}
}

void GameSetup::loadUnitTextures(std::string unitsRed[], std::string unitsWhite[], int index)
{
	//class for setting up the units position on the board
	if (index < 5)
	{
		m_unit[index].loadTexture("..\\images\\" + unitsRed[index] + ".png");
		m_unit[index].unitType(unitsRed[index], 0);
		m_unit[index].initUnit(m_window, m_board.setCoordX(index), m_board.setCoordY(0), m_tileDimension);
		m_unit[index].setTilePosition(index, 0);
		m_board.tileOccupied(index, 0, true, 0);
	}
	else if (index >= 5 && index < 8)
	{
		m_unit[index].loadTexture("..\\images\\" + unitsRed[7 - index] + ".png");
		m_unit[index].unitType(unitsRed[7 - index], 0);
		m_unit[index].initUnit(m_window, m_board.setCoordX(index), m_board.setCoordY(0), m_tileDimension);
		m_unit[index].setTilePosition(index, 0);
		m_board.tileOccupied(index, 0, true, 0);
	}
	else if (index >= 8 && index < 16)
	{
		m_unit[index].loadTexture("..\\images\\" + unitsRed[5] + ".png");
		m_unit[index].unitType(unitsRed[5], 0);
		m_unit[index].initUnit(m_window, m_board.setCoordX(index - 8), m_board.setCoordY(1), m_tileDimension);
		m_unit[index].setTilePosition(index - 8, 1);
		m_board.tileOccupied(index - 8, 1, true, 0);
	}
	else if (index >= 16 && index < 21)//start of the white
	{
		m_unit[index].loadTexture("..\\images\\" + unitsWhite[index - 16] + ".png");
		m_unit[index].unitType(unitsWhite[index - 16], 1);
		m_unit[index].initUnit(m_window, m_board.setCoordX(index - 16), m_board.setCoordY(7), m_tileDimension);
		m_unit[index].setTilePosition(index - 16, 7);
		m_board.tileOccupied(index - 16, 7, true, 1);
	}
	else if (index >= 21 && index < 24)
	{
		m_unit[index].loadTexture("..\\images\\" + unitsWhite[23 - index] + ".png");
		m_unit[index].unitType(unitsWhite[23 - index], 1);
		m_unit[index].initUnit(m_window, m_board.setCoordX(index - 21 + 5), m_board.setCoordY(7), m_tileDimension);
		m_unit[index].setTilePosition(index - 21 + 5, 7);
		m_board.tileOccupied(index - 21 + 5, 7, true, 1);
	}
	else if (index >= 24 && index < 32)
	{
		m_unit[index].loadTexture("..\\images\\" + unitsWhite[5] + ".png");
		m_unit[index].unitType(unitsWhite[5], 1);
		m_unit[index].initUnit(m_window, m_board.setCoordX(31 - index), m_board.setCoordY(6), m_tileDimension);
		m_unit[index].setTilePosition(31 - index, 6);
		m_board.tileOccupied(31 - index, 6, true, 1);
	}
}

void GameSetup::moveUnits()
{
	if (m_moveIndex >= 0)
	{
		m_unit[m_moveIndex].moveUnit();

	}
}

void GameSetup::unitClicked()
{
//take the mouse coordinate
	m_xMouse = sf::Mouse::getPosition(*m_window).x;
	m_yMouse = sf::Mouse::getPosition(*m_window).y;
	m_count = !m_count;
	if (m_count == 1)
	{
		for (int i = 0; i < 32; i++)
		{
			//this bool is for determining of the unit with respect to the mouse coordinate and moving it as such
			bool isUnit = (m_xMouse >= m_unit[i].getPositionX() && m_xMouse <= m_unit[i].getPositionX() + m_tileDimension && m_yMouse >= m_unit[i].getPositionY() && m_yMouse <= m_unit[i].getPositionY() + m_tileDimension);
			if (isUnit)
			{
				if (m_count < 2)
				{
					m_unit[i].isClicked();
				}
				if (m_unit[i].getClick() == true)//when its clicked collect the original placement
				{
					m_moveIndex = i;
					m_originalPlacementX = m_unit[m_moveIndex].getPositionX();
					m_originalPlacementY = m_unit[m_moveIndex].getPositionY();
					std::cout << m_originalPlacementX << " : " << m_originalPlacementY << std::endl;
				}
				else if (m_unit[i].getClick() == false)//when its unclicked collect the new placement
				{
					m_intendedPlacementX = m_unit[m_moveIndex].getPositionX();//where the user intends to place the units
					m_intendedPlacementY = m_unit[m_moveIndex].getPositionY();

					//red is for bool 0, white is for bool 1

					createConstraints(i);
				}
			}
		}
	}
}

void GameSetup::createConstraints(int index)
{
	//get the units indices for next placement
	determineCoordinates(m_intendedPlacementX, m_intendedPlacementY, index);
	//input into the class to figure out if the movement is valid and then carry out what needs to be done
	SpecialUnits specialUnit(m_unit[index].getTeam(), m_unit[index].getName());//class to determine the team
	//need to find the real positions in order to set a boundary for the board
	specialUnit.findUnitPositions(m_originalPlacementX, m_originalPlacementY, m_intendedPlacementX, m_intendedPlacementY);
	specialUnit.createBoundaries(m_xBoard, m_yBoard, m_tileDimension);
	specialUnit.unitIndices(m_unit[index].getTileX(), m_unit[index].getTileY(), m_xNext, m_yNext);
	specialUnit.nextOccupied(m_board.getOccupied(m_xNext, m_yNext), m_board.getTeam(m_xNext, m_yNext));
	//where inboundary is the boundary of the board
	if (!specialUnit.validMovement()) {
		m_unit[index].setPosition(m_board.setCoordX(m_unit[index].getTileX()), m_board.setCoordY(m_unit[index].getTileY()));
		m_unit[index].setTilePosition(m_unit[index].getTileX(), m_unit[index].getTileY());
	}
	else {
		m_board.tileOccupied(m_unit[index].getTileX(), m_unit[index].getTileY(), 0, m_unit[index].getTeam());
		//set the position
		m_unit[index].setPosition(m_board.setCoordX(m_xNext), m_board.setCoordY(m_yNext));
		//set the index
		m_unit[index].setTilePosition(m_xNext, m_yNext);
		m_board.tileOccupied(m_xNext, m_yNext, 1, m_unit[index].getTeam());
	}
}

void GameSetup::determineCoordinates(float placementX, float placementY, int index)
{
	//determine the placement of the next coordinates for the intended placement
	for (unsigned int i = 0; i < 8; i++)
	{
		if (placementX - 22.5 - m_tileDimension < m_board.setCoordX(i) && placementX + 22.5 - m_tileDimension < m_board.setCoordX(i))
		{
			m_xNext = i;

			for (unsigned int j = 0; j < 9; j++)
			{
				if (placementY - 22.5 - m_tileDimension < m_board.setCoordY(j) && placementY + 22.5 - m_tileDimension < m_board.setCoordY(j))
				{
					m_yNext = j;
					break;
				}
			}
			break;
		}
	}
}

void GameSetup::drawEverything()
{
	m_board.drawBoard();
	for (int i = 0; i < 32; i++)
	{
		m_unit[i].drawUnit();
	}
}


