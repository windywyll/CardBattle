#include "stdafx.h"
#include "GameSession.h"


namespace Stormancer
{
	GameSessionService::GameSessionService(ScenePtr scene)
	{
		_scene = scene;
		auto s = scene.lock();
		s->addRoute("server.started", [this](Packetisp_ptr packet) {
			auto serverInfos = packet->readObject<GameServerInformations>();
			this->_waitServerTce.set(serverInfos);
		});
		s->addRoute("player.update", [this](Packetisp_ptr packet) {
			auto update = packet->readObject<Stormancer::PlayerUpdate>();
			SessionPlayer player(update.UserId, (PlayerStatus)update.Status);

			auto end = this->_users.end();
			auto it = std::find_if(this->_users.begin(), end, [player](SessionPlayer p) { return p.PlayerId == player.PlayerId; });
			if (it == end)
			{
				this->_users.push_back(player);
			}
			else
			{
				*it = player;
			}
			this->_onConnectedPlayersChanged(player);
		});

	}

	pplx::task<std::shared_ptr<Result<GameServerInformations>>> GameSessionService::waitServerReady(pplx::cancellation_token token)
	{
		return pplx::create_task(_waitServerTce, pplx::task_options(token)).then([](pplx::task<GameServerInformations> t) {

			std::shared_ptr<Stormancer::Result<GameServerInformations>> result(new Stormancer::Result<GameServerInformations>());
			try
			{
				result->set(t.get());
			}
			catch (const std::exception& ex)
			{
				result->setError(1, ex.what());

			}
			return result;

		});
	}

	std::vector<SessionPlayer> GameSessionService::getConnectedPlayers()
	{
		return this->_users;
	}

	void GameSessionService::unsubscribeConnectedPlayersChanged(Action<SessionPlayer>::TIterator handle)
	{
		this->_onConnectedPlayersChanged.erase(handle);
	}
	std::function<void()> Stormancer::GameSessionService::onConnectedPlayerChanged(std::function<void(SessionPlayer)> callback)
	{
		auto iterator = this->_onConnectedPlayersChanged.push_back(callback);
		return [iterator, this]() {
			unsubscribeConnectedPlayersChanged(iterator);
		};
	}



	pplx::task<void> GameSessionService::connect()
	{
		return _scene.lock()->connect();
	}

	void GameSessionService::ready()
	{
		_scene.lock()->sendPacket("player.ready", [](Stormancer::bytestream* stream) {});
	}

}
