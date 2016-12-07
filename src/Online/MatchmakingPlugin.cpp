#include "stdafx.h"
#include "MatchmakingPlugin.h"
#include "MatchmakingService.h"
#include "GameSession.h"
#include "BugReportService.h"
namespace Stormancer
{
	void MatchmakingPlugin::sceneCreated(Stormancer::ScenePtr scenePtr)
	{
		auto scene = scenePtr.lock();
		if (scene)
		{
			auto name = scene->getHostMetadata("stormancer.plugins.matchmaking");

			if (name.length() > 0 )
			{
				auto service = std::make_shared<MatchmakingService>(scene);
				scene->dependencyResolver()->registerDependency<MatchmakingService>(service);
			}

			name = scene->getHostMetadata("stormancer.gamesession");
			if (name.length() > 0)
			{
				auto service = std::make_shared<GameSessionService>(scene);
				scene->dependencyResolver()->registerDependency<GameSessionService>(service);
			}
			name = scene->getHostMetadata("stormancer.bugReporting");
			if (name.length() > 0)
			{
				auto service = std::make_shared<BugReportService>(scene);
				scene->dependencyResolver()->registerDependency<BugReportService>(service);
			}
		}
	}

	void MatchmakingPlugin::destroy()
	{
		delete this;
	}
};
