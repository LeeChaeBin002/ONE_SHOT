#pragma once
#include "Scene.h"

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	SceneMgr() = default;
	~SceneMgr() = default;

	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::LivingRoom;
	SceneIds currentScene = SceneIds::None;
	SceneIds nextScene = SceneIds::None;

public:
	void Init();
	void Release();
	
	void ChangeScene(SceneIds id);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	Scene* GetScene(SceneIds id);
};

#define SCENE_MGR (SceneMgr::Instance())

