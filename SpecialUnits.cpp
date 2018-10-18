#include "SpecialUnits.h"
#include <iostream>

SpecialUnits::SpecialUnits(bool unitTeam, std::string unitName)
{
	m_unitTeam = unitTeam;
	m_unitName = unitName;
}

void SpecialUnits::findUnitPositions(float xOriginal, float yOriginal, float xNext, float yNext)
{
	m_xOriginal = xOriginal;
	m_yOriginal = yOriginal;
	m_xNext = xNext;
	m_yNext = yNext;
}

void SpecialUnits::createBoundaries(float xBoardOffset, float yBoardOffset, float tileDimension)
{
	m_xBoardOffset = xBoardOffset;
	m_yBoardOffset = yBoardOffset;
	m_tileDimension = tileDimension;
}

void SpecialUnits::unitIndices(int xIndexOriginal, int yIndexOriginal, int xIndexNext, int yIndexNext)
{
	m_xIndexOriginal = xIndexOriginal;
	m_yIndexOriginal = yIndexOriginal;
	m_xIndexNext = xIndexNext;
	m_yIndexNext = yIndexNext;
}

void SpecialUnits::nextOccupied(bool isOccupied, bool team)
{
	m_isOccupied = isOccupied;
	m_nextTileTeam = team;
}

bool SpecialUnits::pawnMovement(bool movingTeam)
{
	//red is on top 
	//white is on bottom
	int move;
	int firstTurn;
	int pawnIndex;
	if (movingTeam == 0) {
		move = 1;
		firstTurn = 2;
		pawnIndex = 1;
	}
	else {
		move = -1;
		firstTurn = -2;
		pawnIndex = 6;
	}
	bool samePosition = (m_xIndexOriginal == m_xIndexNext) && (m_yIndexOriginal == m_yIndexNext);
	bool pawnMovement = (m_yIndexOriginal + move == m_yIndexNext) && (m_xIndexOriginal == m_xIndexNext);
	bool move2 = (m_yIndexOriginal + firstTurn == m_yIndexNext) && (m_xIndexOriginal == m_xIndexNext) && (m_yIndexOriginal == pawnIndex);
	bool pawnAttack = (m_yIndexOriginal + move == m_yIndexNext) && (m_xIndexOriginal + 1 == m_xIndexNext || m_xIndexOriginal - 1 == m_xIndexNext);
	if (pawnMovement && inBoundary() && !m_isOccupied && movingTeam != m_nextTileTeam) {
		return true;
	}
	else if (inBoundary() && !m_isOccupied && movingTeam != m_nextTileTeam && move2)
	{
		return true;
	}
	else if (inBoundary() && pawnAttack && movingTeam != m_nextTileTeam && m_isOccupied) {
		return true;
	}
	else {
		return false;
	}
}

bool SpecialUnits::bishopMovement(bool team)
{
	bool singleMovement = m_xIndexOriginal + 1 == m_xIndexNext || m_xIndexOriginal - 1 == m_xIndexNext;
	for (int i = 1; i < 8; i++)
	{
		singleMovement = m_xIndexOriginal + i == m_xIndexNext;
	}
	return false;
}


bool SpecialUnits::validMovement()
{
	m_type = convertString(m_unitName);
	switch (m_type) {
		case t_unit::REDPAWN:
			return pawnMovement(0);
			break;
		case t_unit::WHITEPAWN:
			return pawnMovement(1);
			break;
		case t_unit::REDBISHOP:
			return bishopMovement(0);
			break;
		default:
			return false;
			break;
	}
}

bool SpecialUnits::inBoundary()
{
	bool left = m_xNext < m_xBoardOffset - (m_tileDimension/2);
	bool bottom = m_yNext > m_yBoardOffset + (8 * (m_tileDimension + 5)) - 20;
	bool right = m_xNext > m_xBoardOffset + (8 * (m_tileDimension + 5)) - 20;
	bool top = m_yNext < 60 - (m_tileDimension/3);
	
	if (left || bottom || right || top)
	{
		return false;
	}
	else {
		return true;
	}
}

UnitTypes::SpecificUnit SpecialUnits::convertString(std::string unitName)
{
	if (unitName == "redpawn") return t_unit::REDPAWN;
	else if (unitName == "redknight") return t_unit::REDKNIGHT;
	else if (unitName == "redbishop") return t_unit::REDBISHOP;
	else if (unitName == "redrook") return t_unit::REDROOK;
	else if (unitName == "redqueen") return t_unit::REDQUEEN;
	else if (unitName == "redking") return t_unit::REDKING;
	else if (unitName == "whitepawn") return t_unit::WHITEPAWN;
	else if (unitName == "whiteknight") return t_unit::WHITEKNIGHT;
	else if (unitName == "whitebishop") return t_unit::WHITEBISHOP;
	else if (unitName == "whiterook") return t_unit::WHITEROOK;
	else if (unitName == "whitequeen") return t_unit::WHITEQUEEN;
	else if (unitName == "whiteking") return t_unit::WHITEKING;

}



