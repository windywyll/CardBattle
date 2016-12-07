#pragma once
#include "stormancer.h"

namespace Stormancer
{
	class TurnByTurnService
	{
	public:
		TurnByTurnService(std::shared_ptr<Scene> scene);
	private:
		std::shared_ptr<Scene> _scene;
	};

	class TurnByTurnPlugin: public IPlugin
	{
	public:
		void sceneCreated(Stormancer::ScenePtr scene);
		void destroy();
	};
}
