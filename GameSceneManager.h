#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "StepTimer.h"

class GameScene;

class GameSceneManager final
{
private:

	using GameScenePtr = std::unique_ptr<GameScene>;
	using GameSceneFactory = std::function<GameScenePtr()>;
	using GameSceneFactoryList = std::unordered_map<std::string, GameSceneFactory>;

private:

	GameSceneFactoryList m_sceneFactories;
	GameScenePtr         m_activeScene;
	std::string          m_nextSceneName;

private:

	template<typename Scene>
	static GameScenePtr CreateScene();

public:

	GameSceneManager();
	~GameSceneManager();

public:

	template<typename Scene>
	void RegisterScene(const std::string& _sceneName);

	void SetStartScene(const std::string& _sceneName);

	void Update(DX::StepTimer const& _timer);
	void Render();

	void RequestScene(const std::string& _ceneName);


private:

	void ChangeScene();
};


template<typename Scene>
GameSceneManager::GameScenePtr GameSceneManager::CreateScene()
{
	return std::make_unique<Scene>();
}


template<typename Scene>
void GameSceneManager::RegisterScene(const std::string& _sceneName)
{
	m_sceneFactories.insert(std::make_pair(_sceneName, CreateScene<Scene>));
}