#pragma once
#include "stormancer.h"

namespace Stormancer
{

	class PlayerProfile
	{
	public:
		std::string PlayerId;
		int RMMR;
		int HighestRank;
		std::string Division;
		int CurrentRank;

		// number of consecutive ranked game wins
		int ConsecutiveRankedWins;

		// number of forfeits in the last 20 ranked games
		int RecentForfeits;

		std::string Name;
		int GMMR;

		MSGPACK_DEFINE(PlayerId, RMMR, HighestRank, Division, CurrentRank, ConsecutiveRankedWins, RecentForfeits, Name, GMMR)
	};
}