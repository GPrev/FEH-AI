#include "AutoPlayer.h"


AutoPlayer::AutoPlayer(FehAI* ai1, FehAI* ai2)
{
	m_ai.push_back(ai1);
	m_ai.push_back(ai2);
}


AutoPlayer::~AutoPlayer()
{
}

bool AutoPlayer::playMove(Map& map)
{
	return m_ai[map.getTurnPlayerID()]->makeMove(map, map.getTurnPlayerColor());
}

void AutoPlayer::playTurn(Map& map)
{
	// Play until you can't
	while (playMove(map)) {}

	map.newTurn();
}

void AutoPlayer::playToTheEnd(Map& map)
{
	while (map.isGameOver())
	{
		playTurn(map);
	}
}

bool AutoPlayer::playToTheEnd(MapData& mapdata, Team* allies, Team* foes)
{
	Map map(mapdata);
	map.init(allies, foes);
	playToTheEnd(map);
	return map.getWinnerColor() == BLUE;
}
