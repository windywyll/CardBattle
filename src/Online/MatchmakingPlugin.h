#pragma once
#include "stormancer.h"

namespace Stormancer
{
	class MatchmakingPlugin : public Stormancer::IPlugin
	{
	public:
		void sceneCreated(Stormancer::ScenePtr scene);
		void destroy();
	};
};
