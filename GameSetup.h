#pragma once
#include "NewBoard.h"
#include "Unit.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "SpecialUnits.h"

class GameSetup
{
public:
	void init(sf::RenderWindow* window, float xPosition, float yPosition, float tileDimension);
	void initUnits();
	void moveUnits();
	void unitClicked();
	void drawEverything();

	//getters
private:
	void loadUnitTextures(std::string unitsRed[], std::string unitsWhite[], int index);
	void createConstraints(int index);
	void determineCoordinates(float placementX, float placementY, int index);
	Unit m_unit[32];
	NewBoard m_board;

	sf::RenderWindow* m_window;
	
	//mouse position
	float m_xMouse;
	float m_yMouse;
	float test1;

	//position of units
	//where placement is the actual position on the board
	//where Coord is the index at the new placement
	float m_intendedPlacementX;
	float m_intendedPlacementY;

	float m_originalPlacementX;
	float m_originalPlacementY;

	//index of intendedplacement
	int m_xNext;
	int m_yNext;

	//board class references
	float m_xBoard;
	float m_yBoard;
	float m_tileDimension;
	bool m_count;
	int m_moveIndex;

};

