#pragma once

#include <list>
#include <memory>
#include <SimpleMath.h>
#include <vector>
#include <functional>

class GameObject;

class GameObjectManager final
{
	using GameObjectPtr = std::unique_ptr<GameObject>;
	using GameObjectList = std::list<GameObjectPtr>;

private:
	GameObjectList m_objects;
	GameObjectList m_objectQueue;

public:
	GameObjectManager();

public:
	~GameObjectManager();

public:
	void Update(float elapsedTime);
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix);
	void Add(GameObjectPtr&& object);
	std::vector<GameObject*> Find(const std::string& tag) const;
	std::vector<GameObject*> Find(std::function<bool(GameObject*)> predicate) const;

private:
	void UpdateObjects(float elapsedTime);
	void AcceptObjects();
	void DestroyObjects();
};