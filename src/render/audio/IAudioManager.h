#ifndef IAUDIOMANAGER_H
#define IAUDIOMANAGER_H

#include <string>

class IAudioManager {
public:
    virtual bool init() = 0;
    virtual void loadSoundEffect(const std::string& id, const std::string& fileName) = 0;
    virtual void loadMusic(const std::string& fileName) = 0;
    virtual void playSoundEffect(const std::string& id) = 0;
    virtual void playMusic() = 0;
    virtual void cleanUp() = 0;
    virtual ~IAudioManager() = default;
};

#endif
