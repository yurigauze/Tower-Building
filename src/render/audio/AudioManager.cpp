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

void AudioManager::loadMusic(const std::string& id, const std::string& fileName) {
    Mix_Music* music = Mix_LoadMUS(fileName.c_str());
    if (music == nullptr) {
        std::cerr << "Falha ao carregar música: " << Mix_GetError() << std::endl;
    } else {
        musics[id] = music;
    }
}

void AudioManager::playSoundEffect(const std::string& id) {
    Mix_PlayChannel(-1, soundEffects[id], 0);
}

void AudioManager::playMusic(const std::string& id) {
    auto it = musics.find(id);
    if (it != musics.end()) {
        currentMusic = it->second;
        Mix_PlayMusic(currentMusic, -1);
    } else {
        std::cerr << "Música não encontrada: " << id << std::endl;
    }
}

void AudioManager::pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

void AudioManager::resumeMusic() {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}

void AudioManager::stopMusic() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
}

void AudioManager::cleanUp() {
    for (auto& effect : soundEffects) {
        Mix_FreeChunk(effect.second);
    }
    for (auto& music : musics) {
        Mix_FreeMusic(music.second);
    }
    Mix_CloseAudio();
}
