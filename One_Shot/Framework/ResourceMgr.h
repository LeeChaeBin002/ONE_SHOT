#pragma once
#include "Singleton.h"

template <typename T>

class ResourceMgr : public Singleton<ResourceMgr<T>>
{
	friend Singleton<ResourceMgr<T>>;

protected:
	ResourceMgr() = default;
	virtual ~ResourceMgr()
	{
		for (auto pair : resources)
		{
			delete pair.second;
		}
		resources.clear();
	}

	ResourceMgr(const ResourceMgr&) = delete;
	ResourceMgr* operator=(const ResourceMgr&) = delete;

	std::unordered_map<std::string, T*> resources;



public:

	static T Empty;
	bool IsEmpty(const T& res)const
	{
		return &res == &Empty;
	}


	bool Load(const std::string& id)
	{

		auto it = resources.find(id);
		if (it != resources.end())
		{
			return false;
		}

		T* res = new T();
		bool success = res->loadFromFile(id);
		if (!success)
		{
			std::cerr << "Failed to load resource: " << id << std::endl;
			if constexpr (std::is_same_v<T, sf::Font>)
			{
				std::cerr << "폰트 로드 실패: " << id << std::endl;
			}
			delete res;
			return false;
		}

		resources.insert({id, res});
		return true;
	}

	bool Unload(const std::string& id)
	{
		auto it = resources.find(id);
		if (it == resources.end())
		{
			return false;
		}

		delete it->second;
		resources.erase(it);
		return true;
	}

	void Load(const std::vector<std::string>& ids)
	{
		for (const auto& id : ids)
		{
			if (!Load(id))
			{
				std::cerr << "1Failed to load resource: " << id << std::endl;
			}
		}
		
		// for (auto id : ids)
		// {
		// Load(id);
		//}
	}

	void Unload(const std::vector<std::string>& ids)
	{
		for (auto id : ids)
		{
			Unload(id);
		}
	}

	T& Get(const std::string& id) 
	{
		auto it = resources.find(id);
		/*if (it == resources.end())
		{
			throw std::runtime_error("Resource not found: " + id);
		}*/
		return *(it->second);
	}
	
	bool Exists(const std::string& id) const
	{
		return resources.find(id) != resources.end();
	}
};

template<typename T>
T ResourceMgr<T>::Empty;

#define TEXTURE_MGR (ResourceMgr<sf::Texture>::Instance())
#define FONT_MGR (ResourceMgr<sf::Font>::Instance())
#define SOUNDBUFFER_MGR (ResourceMgr<sf::SoundBuffer>::Instance())
#define ANI_CLIP_MGR (ResourceMgr<AnimationClip>::Instance())