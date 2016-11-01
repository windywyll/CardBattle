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

void Stormancer::TurnByTurnService::registerUpdateGameCallback(std::function<int(UpdateDto)> callback)
{

	_scene->dependencyResolver()->resolve<IRpcService>()->addProcedure("transaction.execute", [callback](RpcRequestContext_ptr ctx)
	{
		UpdateDto input;
		UpdateResponseDto parameter;
		try
		{
			int value = callback(input);
			parameter = UpdateResponseDto{ true, "", value };
		}
		catch (std::exception& ex)
		{
			parameter = UpdateResponseDto{ false, ex.what(),0 };
		}
		ctx->sendValue([parameter](bytestream* stream)
		{
			msgpack::pack(stream, parameter);
		}, PacketPriority::MEDIUM_PRIORITY);
		return pplx::task_from_result();
	}, true);
}


pplx::task<void> Stormancer::TurnByTurnService::submitTransaction(std::string playerId, std::string cmd, web::json::value args)
{
	auto json = *args.serialize();
	TransactionCommandDto dto{ playerId,cmd,std::string(json.begin(),json.end()) };
	return _scene->dependencyResolver()->resolve<IRpcService>()->rpcVoid("transaction.submit", dto);
}