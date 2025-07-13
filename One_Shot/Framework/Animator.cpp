#include "stdafx.h"
#include "Animator.h"

const std::string Animator::emptyString = "";

void Animator::AddEvent(const std::string& id, int frame, std::function<void()> action)
{
	auto key = std::pair<std::string, int>(id, frame);
	auto it = events.find(key);
	if (it == events.end())
	{
		events.insert({ key, {id, frame} });

	}
	else
	{
	events[key].actions.push_back(action);
		
	}
}

void Animator::init()
{
	// 예: 텍스처 매니저에 필요한 텍스처 미리 로드
	TEXTURE_MGR.Load("graphics/Characters/niko.png");


}

void Animator::Update(float dt)
{
	if (sprite == nullptr) {
		std::cerr << "Error: sprite is nullptr!" << std::endl;
		return; // 혹은 예외 처리
	}
	
	if (!isPlaying)
		return;

	accumTime += dt * std::fabs(speed);
	if (accumTime < frameDuration)
		return;

	currentFrame += speed > 0.f ? 1 : -1;
	accumTime = 0.f;

	if (currentFrame == checkFrame)
	{
		if (!playQueue.empty())
		{
			std::string clipId = playQueue.front();
			Play(clipId, false);
			playQueue.pop();
			return;
		}

		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = speed > 0.f ? totalFrame - 1 : 0;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = speed > 0.f ? 0 : totalFrame - 1;
			break;
		}
	}

	SetFrame(currentClip->frames[currentFrame]);
	auto find = events.find({ currentClip->id, currentFrame });
	if (find != events.end())
	{
		auto& ev = find->second;
		for (auto& action : ev.actions)
		{
			if (action)
			{
				action();
			}
		}
	}
}

void Animator::Play(const std::string& clipId, bool clearQueue)
{
	//Play(&ANI_CLIP_MGR.Get(clipId), clearQueue);
	AnimationClip& clip = ANI_CLIP_MGR.Get(clipId);
	if (clip.frames.empty())
	{
		std::cerr << "Animator::Play - Clip '" << clipId << "' has no frames or was not loaded." << std::endl;
		return;
	}

	Play(&clip, clearQueue);
}



void Animator::Play(AnimationClip* clip, bool clearQueue)
{
	if (clearQueue)
	{
		while (!playQueue.empty())
		{
			playQueue.pop();
		}
	}

	isPlaying = true;

	currentClip = clip;
	totalFrame = clip->frames.size();
	checkFrame = this->speed > 0.f ? totalFrame-1 : 0;
	checkFrame = speed > 0.f ? totalFrame - 1 : 0;
	currentFrame = speed > 0.f ? 0 : totalFrame - 1;

	frameDuration = 1.f / clip->fps;
	accumTime = 0.f;
	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::PlayQueue(const std::string& clipId)
{
	playQueue.push(clipId);
}

void Animator::Stop()
{
	isPlaying = false;
	currentFrame = 0;  // 첫 프레임으로 초기화
	if (currentClip != nullptr && !currentClip->frames.empty())
	{
		SetFrame(currentClip->frames[currentFrame]);
	}
}


void Animator::SetFrame(const AnimationFrame& frame)
{
	if (!sprite)
	{
		std::cerr << "Error: sprite is nullptr!" << std::endl;
		return;
	}
	try
	{
	sf::Texture& tex = TEXTURE_MGR.Get(frame.texId);
	
	sprite->setTexture(tex);
	
	sprite->setTextureRect(frame.texCoord);

	}
	//sprite->setTexture(TEXTURE_MGR.Get(frame.texId));
	catch (const std::exception& e)
	{
		std::cerr << "Texture load error: " << e.what() << std::endl;
	}

}
