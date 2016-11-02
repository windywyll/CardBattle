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
		TurnByTurnService(Scene* scene);
		void onUpdateGameCallback(std::function<int(UpdateDto)> callback);
		void onDesyncErrorCallback(std::function<void(std::string)> callback);
		pplx::task<void> submitTransaction(std::string playerId, std::string cmd, web::json::value args);

	private:
		Scene* _scene;
		std::function<void(std::string)> _onDesync;
		std::function<int(UpdateDto)> _onUpdateGame;
	};

	class TurnByTurnPlugin : public IPlugin
	{
	public:
		void sceneCreated(Stormancer::Scene* scene) override;
		void destroy();
	};
}
