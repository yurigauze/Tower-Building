#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <map>
#include <string>
#include <SDL2/SDL_mixer.h>
#include "IAudioManager.h"
#include "../../logger/ILogger.h"

class AudioManager : public IAudioManager {
private:
    std::map<std::string, Mix_Chunk*> soundEffects;
    Mix_Music* music = nullptr;
    ILogger* logger_ = nullptr;

public:
    static AudioManager& getInstance();

    void setLogger(ILogger* logger);
    bool init() override;
    void loadSoundEffect(const std::string& id, const std::string& fileName) override;
    void loadMusic(const std::string& fileName) override;
    void playSoundEffect(const std::string& id) override;
    void playMusic() override;
    void cleanUp() override;
};

#endif // AUDIOMANAGER_H
