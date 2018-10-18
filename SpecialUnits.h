#pragma once
#include <string>
#include <SFML/Graphics.hpp>

struct UnitTypes {
	enum SpecificUnit {
		REDPAWN,
		REDROOK,
		REDKNIGHT,
		REDKING,
		REDQUEEN,
		REDBISHOP,
		WHITEPAWN,
		WHITEROOK,
		WHITEKNIGHT,
		WHITEKING,
		WHITEQUEEN,
		WHITEBISHOP
	};
};

class SpecialUnits
{
public:
	SpecialUnits(bool unitTeam, std::string unitName);
	void findUnitPositions(float xOriginal, float yOriginal, float xNext, float yNext);
	void createBoundaries(float xBoardOffest, float yBoardOffset, float tileDimension);
	void unitIndices(int xIndexOriginal, int yIndexOriginal, int xIndexNext, int yIndexNext);
	void nextOccupied(bool isOccupied, bool nextTileTeam);
	bool pawnMovement(bool team);//0 is red, 1 is white
	bool bishopMovement(bool team);
	bool inBoundary();
	bool validMovement();
	//enums for the units
private:
	//some identifiers for the units
	bool m_unitTeam;
	std::string m_unitName;
	UnitTypes::SpecificUnit m_type;

	//indices of the pieces
	int m_xIndexOriginal;
	int m_yIndexOriginal;
	int m_xIndexNext;
	int m_yIndexNext;

	//converter for enums
	typedef UnitTypes::SpecificUnit t_unit;//type of unit
	UnitTypes::SpecificUnit convertString(std::string unitName);

	//multiplier for determining team movement
	
	//boundary conditions for units
	float m_xBoardOffset;
	float m_yBoardOffset;
	float m_tileDimension;

	//positions for the units
	float m_xOriginal;
	float m_yOriginal;
	float m_xNext;
	float m_yNext;

	//is board filled at the units next position
	bool m_isOccupied;
	bool m_nextTileTeam;
};

