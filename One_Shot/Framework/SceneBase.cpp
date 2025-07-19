#include "stdafx.h"
#include "SceneBase.h"
#include "Framework.h"

#include "Storage.h"

SceneBase::SceneBase(SceneIds id):Scene(id)
{
}

void SceneBase::HandleItemSelected(int index)
{
    RemoveSelectedIcon();

    std::string iconPath = "graphics/Icons/item_start_remote.png";
    if (!TEXTURE_MGR.Exists(iconPath))
        TEXTURE_MGR.Load(iconPath);

    SpriteGo* icon = new SpriteGo(iconPath, "RemoteIcon");
    icon->GetSprite().setTexture(TEXTURE_MGR.Get(iconPath));
    icon->SetPosition({ FRAMEWORK.GetWindowSizeF().x - 50.f, FRAMEWORK.GetWindowSizeF().y - 50.f });
    icon->SetScale({ 1.5f, 1.5f });
    icon->SetOrigin(Origins::MC);
    icon->SetActive(true);
    AddGameObject(icon);

    selectedIcon = icon;
}
void SceneBase::RemoveSelectedIcon()
{

    if (selectedIcon)
    {
        selectedIcon->SetActive(false);
        for (auto it = gameObjects.begin(); it != gameObjects.end();)
        {
            if (*it == selectedIcon)
            {
                delete* it;
                it = gameObjects.erase(it);
            }
            else ++it;
        }
        selectedIcon = nullptr;
    }
}
void SceneBase::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);

    if (selectedIcon && selectedIcon->GetActive())
    {
        selectedIcon->Draw(window);
    }
}
