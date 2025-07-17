#pragma once
#include "Scene.h"

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	SceneMgr() = default;
	~SceneMgr() = default;

	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::Room;
	SceneIds currentScene = SceneIds::None;
	SceneIds nextScene = SceneIds::None;
	SceneIds previousScene = SceneIds::None;

public:
	const sf::View& GetCurrentWorldView() const;
	void Init();
	void Release();
	
	void ChangeScene(SceneIds id);
	SceneIds GetPreviousScene() const { return previousScene; }

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	Scene* GetScene(SceneIds id);
};

#define SCENE_MGR (SceneMgr::Instance())

