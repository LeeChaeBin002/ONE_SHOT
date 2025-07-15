#include "stdafx.h"
#include "SceneMgr.h"
#include "Room.h"
#include "Computer.h"
#include "Scene.h"
#include "LivingRoom.h"
#include "cellar.h"


const sf::View& SceneMgr::GetCurrentWorldView() const
{
	return scenes[(int)currentScene]->GetWorldView();
}

void SceneMgr::Init()
{
	scenes.push_back(new Title());
	scenes.push_back(new Mode());
	scenes.push_back(new Room());
	scenes.push_back(new Computer());
	scenes.push_back(new LivingRoom());
	scenes.push_back(new cellar());
	scenes.push_back(new Setting());
	scenes.push_back(new Stage1());
	
	//ChangeScene(SceneIds::Room);

	for (auto scene : scenes)
	{
		scene->Init();
	}
	std::cout << "startScene: " << (int)startScene << std::endl;
	currentScene = startScene;
	if ((int)currentScene >= 0 && (int)currentScene < scenes.size())
	{
		scenes[(int)currentScene]->Enter();
	}
	else
	{
		std::cerr << "[Error] currentScene ÀÎµ¦½º ¿À·ù: " << (int)currentScene
			<< " / º¤ÅÍ Å©±â: " << scenes.size() << std::endl;
	}
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		if (scene->GetId() == currentScene)
		{
			scene->Exit();
		}
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	previousScene = currentScene;
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	if (nextScene != SceneIds::None)
	{
		scenes[(int)currentScene]->Exit();
		currentScene = nextScene;
		nextScene = SceneIds::None;
		scenes[(int)currentScene]->Enter();
	}

	scenes[(int)currentScene]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}

Scene* SceneMgr::GetScene(SceneIds id)
{
	for (auto scene : scenes)
	{
		if (scene->GetId() == id)
		{
			return scene;
		}
	}
	return nullptr;
}
