#include "AudioManager.h"
#include <iostream>

AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

bool AudioManager::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Erro ao inicializar SDL_mixer: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void AudioManager::loadSoundEffect(const std::string& id, const std::string& fileName) {
    Mix_Chunk* effect = Mix_LoadWAV(fileName.c_str());
    if (effect == nullptr) {
        std::cerr << "Falha ao carregar efeito sonoro: " << Mix_GetError() << std::endl;
    } else {
        soundEffects[id] = effect;
    }
}

void AudioManager::loadMusic(const std::string& fileName) {
    music = Mix_LoadMUS(fileName.c_str());
    if (music == nullptr) {
        std::cerr << "Falha ao carregar música: " << Mix_GetError() << std::endl;
    }
}

void AudioManager::playSoundEffect(const std::string& id) {
    Mix_PlayChannel(-1, soundEffects[id], 0);
}

void AudioManager::playMusic() {
    if (music != nullptr) {
        Mix_PlayMusic(music, -1);
    }
}

void AudioManager::cleanUp() {
    for (auto& effect : soundEffects) {
        Mix_FreeChunk(effect.second);
    }
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
    Mix_CloseAudio();
}
