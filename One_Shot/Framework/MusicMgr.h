#pragma once

class MusicMgr : public Singleton<MusicMgr>
{

private:
    sf::Music bgm;
    std::string currentMusic;

public:
    void PlayBGM(const std::string& filepath, bool loop = true)
    {
        if (currentMusic == filepath && bgm.getStatus() == sf::Music::Playing)
            return; // �̹� ������̸� �ٽ� ��� ����

        if (!bgm.openFromFile(filepath))
        {
            std::cerr << "Failed to open music: " << filepath << std::endl;
            return;
        }

        currentMusic = filepath;
        bgm.setLoop(loop);
        bgm.play();
    }

    void StopBGM()
    {
        bgm.stop();
    }
};
#define MUSIC_MGR (MusicMgr::Instance())

