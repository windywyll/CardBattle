#include "stdafx.h"
#include "TurnByTurnPlugin.h"

void Stormancer::TurnByTurnPlugin::sceneCreated(Stormancer::ScenePtr scenePtr)
{
	auto scene = scenePtr.lock();
	if (scene)
	{
		auto name = scene->getHostMetadata("stormancer.turnByTurn");

		if (name.length() > 0)
		{
			auto service = std::make_shared<TurnByTurnService>(scene);
			scene->dependencyResolver()->registerDependency<TurnByTurnService>(service);
		}
	}

}

void Stormancer::TurnByTurnPlugin::destroy()
{
	delete this;
}

Stormancer::TurnByTurnService::TurnByTurnService(std::shared_ptr<Scene> scene)
{
	_scene = scene;
}
