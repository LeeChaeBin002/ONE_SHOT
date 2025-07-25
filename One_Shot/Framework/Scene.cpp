#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id)
	: id(id)
{
	auto size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);
}

void Scene::Init()
{
	for (auto obj : gameObjects)
	{
		obj->Init();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	ApplyPendingChanges();
	
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);
	SOUNDBUFFER_MGR.Load(soundIds);
	
	ApplyPendingChanges();

	for (auto obj : gameObjects)
	{
		obj->Reset();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Reset();
	}

}

void Scene::Exit()
{
	ApplyPendingChanges();
	
	TEXTURE_MGR.Unload(texIds);
	FONT_MGR.Unload(fontIds);
	SOUNDBUFFER_MGR.Unload(soundIds);
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}



void Scene::Draw(sf::RenderWindow& window)
{
	std::list<GameObject*> sortedObjects(gameObjects);
	sortedObjects.sort(DrawOrderComparer());

	window.setView(worldView);
	bool isUiView = false;

	for (auto obj : sortedObjects)
	{
		if (obj->sortingLayer >= SortingLayers::UI && !isUiView)
		{
			window.setView(uiView);
			isUiView = true;
		}

		if (obj->GetActive())
		{
			if (obj == nullptr) continue;
			obj->Draw(window);
		}
	}
	ApplyPendingChanges();
}

void Scene::ApplyPendingChanges()
{
	for (GameObject* go : objectsToAdd)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	objectsToAdd.clear();

	for (auto it = gameObjects.begin(); it != gameObjects.end(); )
	{
		GameObject* go = *it;
		if (std::find(objectsToRemove.begin(), objectsToRemove.end(), go) != objectsToRemove.end())
		{
			go->Release();
			delete go;
			it = gameObjects.erase(it); // 안전하게 삭제 후 다음
		}
		else
		{
			++it;
		}
	}

}

GameObject* Scene::AddGameObject(GameObject* go)
{
	objectsToAdd.push_back(go);
	return go;
}

void Scene::RemoveGameObject(GameObject* go)
{
	go->SetActive(false);
	objectsToRemove.push_back(go);
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	
	return nullptr;
}

std::vector<GameObject*> Scene::FindGameObjects(const std::string& name)
{
	std::vector<GameObject*> results;
	
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	return results;
}

void Scene::FindGameObjects(const std::string& name, std::vector<GameObject*>& results)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
}

void Scene::PlayBGMIfAllowed()
{
	if (GameState::playerState != PlayerState::HoldingBulb)
	{
		MUSIC_MGR.PlayBGM("Audio/BGM/SomeplaceIKnow.ogg");
	}
	else
	{
		MUSIC_MGR.StopBGM();
	}
}


sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, worldView);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, worldView);
}

sf::Vector2f Scene::ScreenToUi(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, uiView);
}

sf::Vector2i Scene::UiToScreen(sf::Vector2f uiPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(uiPos, uiView);
}

sf::Vector2f Scene::GetOutsidePosition(const std::string& direction, float offset) const
{
	sf::Vector2f center = worldView.getCenter();
	sf::Vector2f size = worldView.getSize();

	if (direction == "left")
	{
		return { center.x - size.x / 2 - offset, center.y };
	}
	else if (direction == "right")
	{
		return { center.x + size.x / 2 + offset, center.y };
	}
	else if (direction == "top")
	{
		return { center.x, center.y - size.y / 2 - offset };
	}
	else if (direction == "bottom")
	{
		return { center.x, center.y + size.y / 2 + offset };
	}

	return center;
}

