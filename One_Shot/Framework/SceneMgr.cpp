#include "stdafx.h"
#include "SceneMgr.h"


void SceneMgr::Init()
{
	scenes.push_back(new Title());
	scenes.push_back(new Mode());
	scenes.push_back(new Room());
	scenes.push_back(new Setting());
	scenes.push_back(new Stage1());


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
		if (scene->Id == currentScene)
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
