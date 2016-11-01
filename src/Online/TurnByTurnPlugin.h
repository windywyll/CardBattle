#pragma once
#include "stormancer.h"

namespace Stormancer
{
	class TransactionCommandDto
	{
	public:
		std::string playerId;
		std::string cmd;
		std::string args;
		MSGPACK_DEFINE(playerId, cmd, args)
	};
	class UpdateDto
	{
	public:
		int finalStepId;
		long long createdOn;
		std::string issuerUserId;
		std::string issuerPlayerId;
		std::string cmd;
		std::string arguments;


		MSGPACK_DEFINE(finalStepId, createdOn, issuerUserId, issuerPlayerId, cmd, arguments)
	};

	class UpdateResponseDto
	{
	public:
		bool success;
		std::string reason;
		int hash;
		MSGPACK_DEFINE(success, reason, hash)
	};

	class TurnByTurnService
	{
	public:
		TurnByTurnService(std::shared_ptr<Scene> scene);
		void registerUpdateGameCallback(std::function<int(UpdateDto)> callback);

		pplx::task<void> submitTransaction(std::string playerId, std::string cmd, web::json::value args);

	private:
		std::shared_ptr<Scene> _scene;
	};

	class TurnByTurnPlugin : public IPlugin
	{
	public:
		void sceneCreated(Stormancer::ScenePtr scene);
		void destroy();
	};
}
