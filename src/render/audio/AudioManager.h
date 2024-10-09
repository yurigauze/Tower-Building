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
    void loadMusic(const std::string& fileName);
    void playSoundEffect(const std::string& id);
    void playMusic();
    void cleanUp();

private:
    std::map<std::string, Mix_Chunk*> soundEffects;
    Mix_Music* music;
    
    AudioManager() = default;
    ~AudioManager() = default;
};

#endif
