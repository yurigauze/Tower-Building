#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

class AudioManager {
public:
    static AudioManager& getInstance();

    bool init();
    void loadSoundEffect(const std::string& id, const std::string& fileName);
    void loadMusic(const std::string& id, const std::string& fileName);
    void playSoundEffect(const std::string& id);
    void playMusic(const std::string& id);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void cleanUp();

private:
    std::map<std::string, Mix_Chunk*> soundEffects;
    std::map<std::string, Mix_Music*> musics;  
    Mix_Music* currentMusic = nullptr;

    AudioManager() = default;
    ~AudioManager() = default;

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
};

#endif
