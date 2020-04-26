#pragma once

#include "AI.h"

class FEHAI_API AutoPlayer
{
private:
	std::vector<FehAI*> m_ai;

public:
	AutoPlayer() {}
	AutoPlayer(FehAI* ai1, FehAI* ai2);
	~AutoPlayer();

	bool playMove(Map& map);
	void playTurn(Map& map);
	void playToTheEnd(Map& map);
	bool playToTheEnd(MapData& map, Team* allies, Team* foes = nullptr);
};

